#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H
#include <string>

class ConfigService
{
public:
    void createConfigFile(std::string token);
    std::string getTokenFromConfigFile();
};

#endif