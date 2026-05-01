#include "languages_list_command.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

LanguagesListCommand::LanguagesListCommand(GithubService &githubService) : githubService(githubService) {}

void LanguagesListCommand::execute(int argc, char *argv[])
{
    string user;
    if (argc >= 2 && string(argv[1]) == "languages")
    {
        if (argc < 3)
        {
            cout << "Usage:" << endl;
            cout << "  gitstats languages <user>" << endl;
            cout << "  gitstats user --languages/--langs <user>" << endl;
            return;
        }
        user = argv[2];
    }
    else
    {
        if (argc < 4)
        {
            cout << "Usage:" << endl;
            cout << "  gitstats user --languages/--langs <user>" << endl;
            cout << "  gitstats languages <user>" << endl;
            return;
        }
        user = argv[3];
    }

    try
    {
        auto langs = githubService.getMostUsedLanguages(user);
        for (auto &[lang, percent] : langs)
        {
            cout << fixed << setprecision(2) << lang << ": " << percent << "%" << endl;
        }
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}