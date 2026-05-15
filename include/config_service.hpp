#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H
#include <string>
#include <filesystem>
class ConfigService
{
public:
    void createConfigFile();
    std::string getTokenFromConfigFile();
    void setTokenOnConfigFile(std::string token);

private:
    std::filesystem::path getConfigFile();
};

#endif