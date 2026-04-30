#ifndef ICOMMAND_H
#define ICOMMAND_H
#include <string>
class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void execute(int argc, char *argv[]) = 0;
};

#endif