#include "nexus_string.h"

std::string trim(const std::string& arg)
{
    if (arg.empty()) return arg;
    size_t b = arg.find_first_not_of(" \t\n\r");
    size_t e = arg.find_last_not_of(" \t\n\r");
    return arg.substr(b, e-b+1);
}
