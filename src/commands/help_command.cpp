#include "help_command.hpp"
#include <iostream>
using namespace std;

void HelpCommand::execute(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    cout << "gitstats - GitHub language stats CLI" << endl
         << endl;
    cout << "Usage:" << endl;
    cout << "  gitstats <command> [options]" << endl
         << endl;
    cout << "Commands:" << endl;
    cout << "  help                      Show this help message" << endl;
    cout << "  config <option>           Manage local config" << endl;
    cout << "  languages <user>          Show top languages for a GitHub user" << endl
         << endl;
    cout << "Config options:" << endl;
    cout << "  --set-token <token>       Set GitHub token in config file" << endl;
    cout << "  --remove-token            Remove token from config file" << endl;
    cout << "  --list                    List config values" << endl
         << endl;
    cout << "Examples:" << endl;
    cout << "  gitstats help" << endl;
    cout << "  gitstats config --set-token ghp_xxxxx" << endl;
    cout << "  gitstats config --list" << endl;
    cout << "  gitstats config --remove-token" << endl;
    cout << "  gitstats languages torvalds" << endl
         << endl;
    cout << "Notes:" << endl;
    cout << "  - A GitHub token is required for GraphQL API calls." << endl;
    cout << "  - Config file location: ./.config/config.json" << endl;
    cout << "  - Forked repositories are ignored." << endl;
    cout << "  - \"Jupyter Notebook\" language is excluded." << endl;
    cout << "  - Output is the top 10 languages by percentage." << endl;
    cout << "  - Percentages are printed with 2 decimal places." << endl;
}
