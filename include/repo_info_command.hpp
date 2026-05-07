#ifndef REPO_INFO_COMMAND_H
#define REPO_INFO_COMMAND_H

#include "icommand.hpp"
#include "github_service.hpp"

class RepoInfoCommand : ICommand
{
private:
    GithubService &githubService;

public:
    RepoInfoCommand(GithubService &githubService);
    void execute(int argc, char *argv[]) override;
};

#endif