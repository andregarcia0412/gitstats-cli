#include "config_help_command.hpp"
#include <iostream>
using namespace std;

void ConfigHelpCommand::execute(int argc, char *argv[])
{
    cout << "use: gitstats config <option>" << endl
         << endl;
    cout << "Action\n   --set-token         set token on config file" << endl;
    cout << "   --remove-token      removes token from config file" << endl;
    cout << "   --list              get all values on config file" << endl;
}