#ifndef ICOMMAND_H
#define ICOMMAND_H
#include <string>
class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void execute(int argc, char *argv[]) {}
};

#endif