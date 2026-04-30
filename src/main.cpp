#include <iostream>
#include <iomanip>
#include <map>
#include <functional>
#include "github_service.hpp"
#include "config_service.hpp"
#include "set_token_command.hpp"
#include "config_help_command.hpp"
#include "remove_token_command.hpp"
#include "config_list_command.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    GithubService githubService = GithubService();
    ConfigService configService = ConfigService();
    map<string, function<void(int, char **)>> commands;
    commands["help"] = [](int argc, char *argv[])
    {
        cout << "this is help" << endl;
    };

    commands["config"] = [&githubService, &configService](int argc, char *argv[])
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

    commands["languages"] = [&githubService, &configService](int argc, char *argv[])
    {
        if (argc < 3)
        {
            cout << "Use: languages <user>" << endl;
            return;
        }

        string token = configService.getTokenFromConfigFile();
        githubService.setToken(token);

        try
        {
            auto langs = githubService.getMostUsedLanguages(argv[2]);
            for (auto &[lang, percent] : langs)
            {
                cout << fixed << setprecision(2) << lang << ": " << percent << "%" << endl;
            }
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
        }
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