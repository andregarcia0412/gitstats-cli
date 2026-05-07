#include "repo_help_command.hpp"
#include <iostream>
using namespace std;

void RepoHelpCommand::execute(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cout << "Usage:" << endl;
    cout << "  gitstats repository <option> <owner> <repo>" << endl
         << endl;
    cout << "Options:" << endl;
    cout << "  --info <owner> <repo>          Show GitHub repository info" << endl
         << endl;
    cout << "Examples:" << endl;
    cout << "  gitstats repository --info torvalds linux" << endl;
}
