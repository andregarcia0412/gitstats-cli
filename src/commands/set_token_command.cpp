#include "icommand.hpp"
#include "config_service.hpp"
#include "set_token_command.hpp"
#include <iostream>
using namespace std;

SetTokenCommand::SetTokenCommand(ConfigService configService)
{
    this->configService = configService;
}

void SetTokenCommand::execute(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Nothing specified, nothing added\nTry gitstats config --set-token <value>" << endl;
        return;
    }
    string token = argv[3];
    configService.setTokenOnConfigFile(token);
}