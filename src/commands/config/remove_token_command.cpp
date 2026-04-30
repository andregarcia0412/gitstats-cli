#include "remove_token_command.hpp"

RemoveTokenCommand::RemoveTokenCommand(ConfigService configService)
{
    this->configService = configService;
}

void RemoveTokenCommand::execute(int argc, char *argv[])
{
    configService.setTokenOnConfigFile("");
}