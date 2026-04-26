#include "config_service.hpp"
#include <fstream>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
namespace fs = std::filesystem;

void ConfigService::createConfigFile(string token)
{
    fs::create_directories("./.config");
    ofstream configFile("./.config/config.json");

    if (!configFile.is_open())
    {
        throw runtime_error("Error opening config file");
    }

    configFile << "{\n  \"token\":" << "\"" << token << "\"\n}" << endl;
    configFile.close();
}

string ConfigService::getTokenFromConfigFile()
{
    ifstream configFile("./.config/config.json");

    if (!configFile.is_open())
    {
        throw runtime_error("Error opening config file");
    }

    json data;
    configFile >> data;

    return data["token"];
}