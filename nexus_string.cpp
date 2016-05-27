#include "nexus_string.h"

using namespace std;

string trim(const string& arg)
{
    if (arg.empty()) return arg;
    size_t b = arg.find_first_not_of(" \t\n\r");
    size_t e = arg.find_last_not_of(" \t\n\r");
    return arg.substr(b, e-b+1);
}

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
