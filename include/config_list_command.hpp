#include "icommand.hpp"
#include "config_service.hpp"

class ConfigListCommand : ICommand
{
private:
    ConfigService configService;

public:
    ConfigListCommand(ConfigService configService);
    void execute(int argc, char *argv[]) override;
};