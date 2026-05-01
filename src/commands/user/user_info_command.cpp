#include "user_info_command.hpp"
#include <iostream>
using namespace std;

UserInfoCommand::UserInfoCommand(GithubService &githubService) : githubService(githubService) {}

void UserInfoCommand::execute(int argc, char *argv[])
{
    auto result = githubService.getUserInfo(argv[2]);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].first << ": " << result[i].second << endl;
    }
}