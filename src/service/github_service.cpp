#include "github_service.hpp"
#include <map>
#include <algorithm>
#include <curl/curl.h>
#include "json.hpp"
#include <iostream>
#include "utils/format_date.hpp"

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
    query($login: String!, $cursor: String) {
        user(login: $login) {
            repositories(first: 100, after: $cursor, ownerAffiliations: OWNER) {
                pageInfo {
                    hasNextPage
                    endCursor
                }
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

    string cursor;
    bool hasNext = true;

    while (hasNext)
    {
        json variables = {{"login", login}};
        if (!cursor.empty())
        {
            variables["cursor"] = cursor;
        }
        else
        {
            variables["cursor"] = nullptr;
        }

        json body = {
            {"query", query},
            {"variables", variables}};

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

        auto pageInfo = data["data"]["user"]["repositories"]["pageInfo"];
        hasNext = pageInfo["hasNextPage"].get<bool>();
        cursor = pageInfo["endCursor"].is_null() ? "" : pageInfo["endCursor"].get<string>();
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

    if (!data.contains("data") || data["data"]["user"].is_null())
    {
        throw runtime_error("Error: User Not Found");
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

vector<pair<string, string>> GithubService::getRepoInfo(string owner, string name)
{
    string query = R"(
    query($owner: String!, $name: String!) {
        repository(owner: $owner, name: $name) {
            name
            description
            stargazerCount
            forkCount
            url
            createdAt
            pushedAt
            homepageUrl
            pullRequests(states: OPEN) {
                totalCount
            }
            primaryLanguage {
                name
            }
            defaultBranchRef {
                target {
                    ... on Commit {
                        history {
                            totalCount
                        }
                    }
                }
            }
        }
    }
    )";

    json body = {
        {"query", query},
        {"variables", {{"owner", owner}, {"name", name}}}};

    auto data = json::parse(makeGraphQLApiCall(body));

    if (data["status"] == 401)
    {
        throw runtime_error("Error: Bad Credentials");
    }

    if (data["data"]["repository"].is_null())
    {
        throw runtime_error("Error: Repository Not Found");
    }

    auto repo = data["data"]["repository"];
    vector<pair<string, string>> result;

    result.push_back({"Name", repo["name"]});
    if (!repo["description"].is_null())
    {
        result.push_back({"Description", repo["description"]});
    }
    result.push_back({"Stars", to_string(repo["stargazerCount"])});
    result.push_back({"Forks", to_string(repo["forkCount"])});
    result.push_back({"Primary Language", repo["primaryLanguage"]["name"]});
    result.push_back({"Pull Requests", to_string(repo["pullRequests"]["totalCount"])});
    result.push_back({"Commits", to_string(repo["defaultBranchRef"]["target"]["history"]["totalCount"])});
    result.push_back({"Created At", formatDate(repo["createdAt"])});
    if (!repo["pushedAt"].is_null())
    {
        result.push_back({"Last Pushed At", formatDate(repo["pushedAt"])});
    }
    if (!repo["homepageUrl"].is_null())
    {
        result.push_back({"Homepage URL", repo["homepageUrl"]});
    }
    result.push_back({"URL", repo["url"]});
    return result;
}