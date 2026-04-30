#include "config_help_command.hpp"
#include <iostream>
using namespace std;

void ConfigHelpCommand::execute(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cout << "Usage:" << endl;
    cout << "  gitstats config <option>" << endl
         << endl;
    cout << "Options:" << endl;
    cout << "  --set-token <token>       Set GitHub token in config file" << endl;
    cout << "  --remove-token            Remove token from config file" << endl;
    cout << "  --list                    List config values" << endl
         << endl;
    cout << "Examples:" << endl;
    cout << "  gitstats config --set-token ghp_xxxxx" << endl;
    cout << "  gitstats config --list" << endl;
    cout << "  gitstats config --remove-token" << endl;
}