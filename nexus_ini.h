#ifndef NEXUS_INI_H_INCLUDED
#define NEXUS_INI_H_INCLUDED

#include <iostream>
#include <string>
#include <map>

/** Type of section map of ini file */
typedef std::map<std::string,std::string> section_t;
/** Type of ini file map representation */
typedef std::map<std::string,section_t> ini_t;

/* Function prototypes */
void write_config(const ini_t& ini, std::ostream& out);
ini_t read_config(std::istream& in);

#endif // NEXUS_INI_H_INCLUDED
