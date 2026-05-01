#include "user_info_command.hpp"
#include <iostream>
using namespace std;

UserInfoCommand::UserInfoCommand(GithubService &githubService) : githubService(githubService) {}

void UserInfoCommand::execute(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Usage: gitstats user --info <user>" << endl;
        return;
    }

    try
    {
        auto result = githubService.getUserInfo(argv[3]);
        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i].first << ": " << result[i].second << endl;
        }
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
}