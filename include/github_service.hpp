#ifndef GITHUB_SERVICE_H
#define GITHUB_SERVICE_H

#include <string>
#include <vector>

class GithubService
{
private:
    std::string token;

public:
    GithubService(std::string token);
    GithubService();
    std::vector<std::pair<std::string, double>> getMostUsedLanguages(std::string login);
    void setToken(std::string token);
    std::string getToken();
};

#endif