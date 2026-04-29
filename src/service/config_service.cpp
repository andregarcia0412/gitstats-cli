#include "config_service.hpp"
#include <fstream>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
namespace fs = std::filesystem;

void ConfigService::createConfigFile()
{
    fs::create_directories("./.config");
    ofstream configFile("./.config/config.json");

    if (!configFile.is_open())
    {
        throw runtime_error("Error opening config file");
    }

    configFile << "{\n}" << endl;
    configFile.close();
}

void ConfigService::setTokenOnConfigFile(string token)
{

    if (!fs::exists("./.config/config.json"))
        createConfigFile();
    json data;

    ifstream inConfigFile("./.config/config.json");
    if (inConfigFile)
        inConfigFile >> data;

    data["token"] = token;

    ofstream outConfigFile("./.config/config.json");
    outConfigFile << data.dump(2);
}

string ConfigService::getTokenFromConfigFile()
{
    if (!fs::exists("./.config/config.json"))
        return "";

    ifstream configFile("./.config/config.json");
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