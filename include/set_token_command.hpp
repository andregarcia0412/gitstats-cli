#ifndef SET_TOKEN_COMMAND_H
#define SET_TOKEN_COMMAND_H
#include "icommand.hpp"
#include <string>
#include "config_service.hpp"

class SetTokenCommand : ICommand
{
private:
    ConfigService &configService;

public:
    SetTokenCommand(ConfigService &configService);
    void execute(int argc, char *argv[]) override;
};

#endif