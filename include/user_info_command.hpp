#ifndef USER_INFO_COMMAND_H
#define USER_INFO_COMMAND_H
#include "icommand.hpp"
#include "github_service.hpp"

class UserInfoCommand : ICommand
{
private:
    GithubService &githubService;

public:
    UserInfoCommand(GithubService &githubService);
    void execute(int argc, char *argv[]) override;
};

#endif