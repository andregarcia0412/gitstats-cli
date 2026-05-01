#include "languages_list_command.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

LanguagesListCommand::LanguagesListCommand(GithubService &githubService) : githubService(githubService) {}

void LanguagesListCommand::execute(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage: gitstats languages <user>" << endl;
        return;
    }

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
}