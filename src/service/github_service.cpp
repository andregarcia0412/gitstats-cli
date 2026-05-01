#include "github_service.hpp"
#include <map>
#include <algorithm>
#include <curl/curl.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *output)
{
    output->append((char *)contents, size * nmemb);
    return size * nmemb;
}

GithubService::GithubService(ConfigService &configService) : configService(configService)
{
    this->token = configService.getTokenFromConfigFile();
}

string GithubService::makeGraphQLApiCall(json body)
{
    string response;
    CURL *curl = curl_easy_init();
    if (!curl)
        throw runtime_error("Error while initializing CURL");

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "User-Agent: gitstats-cli");

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/graphql");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    string bodyStr = body.dump();
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyStr.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, bodyStr.size());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        throw runtime_error("Error: Request Failed");
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    return response;
}

vector<pair<string, double>> GithubService::getMostUsedLanguages(string login)
{
    map<string, long long> languageBytes;

    string query = R"(
    query($login: String!) {
        user(login: $login) {
            repositories(first: 100, ownerAffiliations: OWNER) {
                nodes {
                    isFork
                    languages(first: 100) {
                        edges {
                            size
                            node { name }
                        }
                    }
                }
            }
        }
    })";

    json body = {
        {"query", query},
        {"variables", {{"login", login}}}};

    auto data = json::parse(makeGraphQLApiCall(body));
    if (data["status"] == "401")
    {
        throw runtime_error("Error: Bad Credentials");
    }

    auto repos = data["data"]["user"]["repositories"]["nodes"];

    for (auto &repo : repos)
    {
        if (repo["isFork"])
            continue;

        for (auto &lang : repo["languages"]["edges"])
        {
            string name = lang["node"]["name"];
            long long size = lang["size"];

            languageBytes[name] += size;
        }
    }

    long long total = 0;
    languageBytes.erase("Jupyter Notebook");
    for (auto &[k, v] : languageBytes)
    {
        total += v;
    }

    vector<pair<string, double>> sorted;

    for (auto &[k, v] : languageBytes)
    {
        if (total == 0)
        {
            return {};
        }
        double percent = (double)v / total * 100.0;
        sorted.push_back({k, percent});
    }

    sort(sorted.begin(), sorted.end(), [](auto &a, auto &b)
         { return a.second > b.second; });

    vector<pair<string, double>> top10;
    for (int i = 0; i < min(10, (int)sorted.size()); i++)
    {
        top10.push_back(sorted[i]);
    }
    return top10;
}

vector<pair<string, double>> GithubService::getUserInfo(string login)
{

    string query = R"(
    query($login: String!) {
    user(login: $login) {
        createdAt

        followers {
        totalCount
        }

        following {
        totalCount
        }

        contributionsCollection {
        totalCommitContributions
        totalPullRequestContributions
        }

        pullRequests {
        totalCount
        }

        mergedPRs: pullRequests(states: MERGED) {
        totalCount
        }
    }
    }
    )";

    json body = {
        {"query", query},
        {"variables", {{"login", login}}}};

    auto data = json::parse(makeGraphQLApiCall(body));
    if (data["status"] == "401")
    {
        throw runtime_error("Error: Bad Credentials");
    }

    auto user = data["data"]["user"];
    vector<pair<string, double>> result;
    result.push_back({"Followers", user["followers"]["totalCount"]});
    result.push_back({"Following", user["following"]["totalCount"]});
    result.push_back({"Commits", user["contributionsCollection"]["totalCommitContributions"]});
    result.push_back({"Pull Requests", user["pullRequests"]["totalCount"]});
    result.push_back({"Merged Pull Requests", user["mergedPRs"]["totalCount"]});

    return result;
}
