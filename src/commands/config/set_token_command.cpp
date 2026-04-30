#include "set_token_command.hpp"
#include <iostream>
using namespace std;

SetTokenCommand::SetTokenCommand(ConfigService &configService) : configService(configService) {}

void SetTokenCommand::execute(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Missing token.\nUsage: gitstats config --set-token <token>" << endl;
        return;
    }
    string token = argv[3];
    configService.setTokenOnConfigFile(token);
}