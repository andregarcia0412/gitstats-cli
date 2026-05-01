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
#include "help_command.hpp"
#include "user_info_command.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    ConfigService configService = ConfigService();
    GithubService githubService = GithubService(configService);
    map<string, function<void(int, char **)>> commands;
    commands["help"] = [](int argc, char *argv[])
    {
        HelpCommand().execute(argc, argv);
    };

    commands["config"] = [&configService](int argc, char *argv[])
    {
        if (argc < 3)
        {
            ConfigHelpCommand().execute(argc, argv);
            return;
        }

        string subcmd = string(argv[2]);

        if (subcmd == "--set-token")
        {
            SetTokenCommand(configService).execute(argc, argv);
        }

        if (subcmd == "--remove-token")
        {
            RemoveTokenCommand(configService).execute(argc, argv);
        }

        if (subcmd == "--list")
        {
            ConfigListCommand(configService).execute(argc, argv);
        }
    };

    commands["languages"] = [&githubService](int argc, char *argv[])
    {
        LanguagesListCommand(githubService).execute(argc, argv);
    };

    commands["user"] = [&githubService](int argc, char *argv[])
    {
        UserInfoCommand(githubService).execute(argc, argv);
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