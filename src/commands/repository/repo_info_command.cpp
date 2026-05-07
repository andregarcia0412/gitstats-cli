#include "repo_info_command.hpp"
#include <iostream>
using namespace std;

RepoInfoCommand::RepoInfoCommand(GithubService &githubService) : githubService(githubService) {};

void RepoInfoCommand::execute(int argc, char *argv[])
{
    try
    {
        auto result = githubService.getRepoInfo(argv[3], argv[4]);
        for (const auto &item : result)
        {
            cout << item.first << ": " << item.second << endl;
        }
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}