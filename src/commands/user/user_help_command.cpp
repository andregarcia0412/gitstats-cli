#include "user_help_command.hpp"
#include <iostream>
using namespace std;

void UserHelpCommand::execute(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cout << "Usage:" << endl;
    cout << "  gitstats user <option> <user>" << endl;
    cout << "  gitstats languages <user>" << endl
         << endl;
    cout << "Options:" << endl;
    cout << "  --languages, --langs <user>     Show top languages for a GitHub user" << endl;
    cout << "  --info <user>                   Show GitHub user info" << endl
         << endl;
    cout << "Examples:" << endl;
    cout << "  gitstats user --languages torvalds" << endl;
    cout << "  gitstats user --langs torvalds" << endl;
    cout << "  gitstats user --info torvalds" << endl;
    cout << "  gitstats languages torvalds" << endl;
}
