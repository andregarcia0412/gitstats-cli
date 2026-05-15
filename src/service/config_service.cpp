#include "config_service.hpp"
#include <fstream>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
namespace fs = std::filesystem;

void ConfigService::createConfigFile()
{
    fs::path configFilePath = getConfigFile();
    fs::create_directories(configFilePath.parent_path());
    ofstream configFile(configFilePath);

    if (!configFile.is_open())
    {
        throw runtime_error("Error opening config file");
    }

    configFile << "{\n}" << endl;
    configFile.close();
}

void ConfigService::setTokenOnConfigFile(string token)
{
    fs::path configFilePath = getConfigFile();
    if (!fs::exists(configFilePath))
        createConfigFile();
    json data;

    ifstream inConfigFile(configFilePath);
    if (inConfigFile)
        inConfigFile >> data;

    data["token"] = token;

    ofstream outConfigFile(configFilePath);
    outConfigFile << data.dump(2);
}

string ConfigService::getTokenFromConfigFile()
{
    fs::path configFilePath = getConfigFile();
    if (!fs::exists(configFilePath))
        return "";

    ifstream configFile(configFilePath);
    if (!configFile.is_open())
    {
        throw runtime_error("Error opening config file");
    }

    json data;
    configFile >> data;

    if (!data.contains("token") || !data["token"].is_string())
        return "";

    return data["token"].get<string>();
}

fs::path ConfigService::getConfigFile()
{
#ifdef _WIN32
    const char *appData = getenv("APPDATA");
    if (!appData)
    {
        throw runtime_error("APPDATA not found");
    }

    return fs::path(appData) / "gitstats" / ".config" / "config.json";

#else
    const char *home = getenv("HOME");
    if (!home)
    {
        throw runtime_error("HOME not found");
    }

    return fs::path(home) / "gitstats" / ".config" / "config.json";
#endif
}