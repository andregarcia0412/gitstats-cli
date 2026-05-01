#ifndef GITHUB_SERVICE_H
#define GITHUB_SERVICE_H

#include <string>
#include <vector>
#include "config_service.hpp"
#include "json.hpp"

using json = nlohmann::json;

class GithubService
{
private:
    ConfigService &configService;
    std::string token;
    std::string makeGraphQLApiCall(json body);

public:
    GithubService(ConfigService &configService);
    std::vector<std::pair<std::string, double>> getMostUsedLanguages(std::string login);
    std::vector<std::pair<std::string, double>> getUserInfo(std::string login);
};

#endif