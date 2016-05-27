#ifndef NEXUS_STRING_H_INCLUDED
#define NEXUS_STRING_H_INCLUDED

#include <string>
#include <vector>

std::string trim(const std::string& arg);
std::vector<std::string> split(const std::string& str, const std::string& delim);

#endif // NEXUS_STRING_H_INCLUDED
