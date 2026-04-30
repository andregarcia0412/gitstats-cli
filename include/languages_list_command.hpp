#ifndef LANGUAGES_LIST_COMMAND_H
#define LANGUAGES_LIST_COMMAND_H
#include "icommand.hpp"
#include "github_service.hpp"
#include "config_service.hpp"

class LanguagesListCommand : ICommand
{
private:
    GithubService &githubService;

public:
    LanguagesListCommand(GithubService &githubService);
    void execute(int argc, char *argv[]) override;
};

#endif