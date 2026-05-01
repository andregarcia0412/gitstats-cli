#include "languages_list_command.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

LanguagesListCommand::LanguagesListCommand(GithubService &githubService) : githubService(githubService) {}

void LanguagesListCommand::execute(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Usage: gitstats user --languages/--langs <user>" << endl;
        return;
    }

    try
    {
        auto langs = githubService.getMostUsedLanguages(argv[3]);
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