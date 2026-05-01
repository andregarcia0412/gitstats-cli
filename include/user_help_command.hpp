#ifndef USER_HELP_COMMAND_H
#define USER_HELP_COMMAND_H
#include "icommand.hpp"

class UserHelpCommand : ICommand
{
public:
    void execute(int argc, char *argv[]) override;
};

#endif
