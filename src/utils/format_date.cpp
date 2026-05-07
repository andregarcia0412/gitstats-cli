#include "utils/format_date.hpp"
using namespace std;

string formatDate(string timestamp)
{
    string date;

    for (char c : timestamp)
    {
        if (c == 'T')
            break;

        if (c == '-')
            date += '/';
        else
            date += c;
    }

    return date;
}
