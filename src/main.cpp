#include <iostream>
#include <iomanip>
#include <map>
#include <functional>
#include "github_service.hpp"
#include "config_service.hpp"
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
            // TODO: config help when argc < 3;
        }

        if (string(argv[2]) == "--set-token")
        {
            string token = argv[3];
            configService.createConfigFile(token);
        }

        if (string(argv[2]) == "--list")
        {
            // TODO: add json listing
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