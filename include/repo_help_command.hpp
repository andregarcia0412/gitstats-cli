#ifndef REPO_HELP_COMMAND_H
#define REPO_HELP_COMMAND_H
#include "icommand.hpp"

class RepoHelpCommand : ICommand
{
public:
    void execute(int argc, char *argv[]) override;
};

#endif
