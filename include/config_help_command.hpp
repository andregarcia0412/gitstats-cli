#ifndef CONFIG_HELP_COMMAND_H
#define CONFIG_HELP_COMMAND_H
#include "icommand.hpp"

class ConfigHelpCommand : ICommand
{
public:
    void execute(int argc, char *argv[]) override;
};

#endif