#ifndef REMOVE_TOKEN_COMMAND_H
#define REMOVE_TOKEN_COMMAND_H
#include "icommand.hpp"
#include "config_service.hpp"

class RemoveTokenCommand : ICommand
{
private:
    ConfigService &configService;

public:
    RemoveTokenCommand(ConfigService &configService);
    void execute(int argc, char *argv[]) override;
};

#endif