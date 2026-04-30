#include <iostream>
#include <map>
#include <functional>
#include "github_service.hpp"
#include "config_service.hpp"
#include "set_token_command.hpp"
#include "config_help_command.hpp"
#include "remove_token_command.hpp"
#include "config_list_command.hpp"
#include "languages_list_command.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    ConfigService configService = ConfigService();
    GithubService githubService = GithubService(configService);
    map<string, function<void(int, char **)>> commands;
    commands["help"] = [](int argc, char *argv[])
    {
        cout << "this is help" << endl;
    };

    commands["config"] = [&configService](int argc, char *argv[])
    {
        if (argc < 3)
        {
            ConfigHelpCommand().execute(argc, argv);
            return;
        }

        if (string(argv[2]) == "--set-token")
        {
            SetTokenCommand(configService).execute(argc, argv);
        }

        if (string(argv[2]) == "--remove-token")
        {
            RemoveTokenCommand(configService).execute(argc, argv);
        }

        if (string(argv[2]) == "--list")
        {
            ConfigListCommand(configService).execute(argc, argv);
        }
    };

    commands["languages"] = [&githubService](int argc, char *argv[])
    {
        LanguagesListCommand(githubService).execute(argc, argv);
    };

    if (argc < 2)
    {
        commands["help"](argc, argv);
        return 1;
    }

    string cmd = argv[1];

    if (commands.count(cmd))
    {
        commands[cmd](argc, argv);
    }
    else
    {
        commands["help"](argc, argv);
    }
}