#include <iostream>
#include <iomanip>
#include <map>
#include <functional>
#include "github_service.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    GithubService service = GithubService();
    map<string, function<void(int, char **)>> commands;
    commands["help"] = [](int argc, char *argv[])
    {
        cout << "this is help" << endl;
    };

    commands["config"] = [&service](int argc, char *argv[])
    {
        if (argc < 3)
        {
            // TODO: config help when argc < 3;
        }

        if (string(argv[2]) == "--set-token")
        {
            string token = argv[3];
            service.setToken(token);
            cout << token << endl;

            // TODO: add writing to json file to save password
        }

        if (string(argv[2]) == "--list")
        {
            // TODO: add json listing
        }
    };

    commands["languages"] = [&service](int argc, char *argv[])
    {
        if (argc < 3)
        {
            cout << "Use: languages <user>" << endl;
            return;
        }

        auto langs = service.getMostUsedLanguages(argv[2]);

        for (auto &[lang, percent] : langs)
        {
            cout << fixed << setprecision(2) << lang << ": " << percent << "%" << endl;
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