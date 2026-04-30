#include "config_list_command.hpp"
#include <iostream>
using namespace std;

ConfigListCommand::ConfigListCommand(ConfigService &configService) : configService(configService) {}

void ConfigListCommand::execute(int argc, char *argv[])
{
    string token = configService.getTokenFromConfigFile();
    cout << "token=" << token << endl;
}