#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H
#include "icommand.hpp"

class HelpCommand : ICommand
{
public:
    void execute(int argc, char *argv[]) override;
};

#endif
