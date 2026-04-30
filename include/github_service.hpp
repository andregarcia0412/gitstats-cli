#ifndef GITHUB_SERVICE_H
#define GITHUB_SERVICE_H

#include <string>
#include <vector>
#include "config_service.hpp"

class GithubService
{
private:
    ConfigService &configService;

public:
    GithubService(ConfigService &configService);
    std::vector<std::pair<std::string, double>> getMostUsedLanguages(std::string login);
};

#endif