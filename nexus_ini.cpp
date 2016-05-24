#include "nexus_ini.h"
#include "nexus_string.h"

/** @brief Write ini file map representation to specified output stream
 * @param ini ini file representation
 * @param out output stream
 */
void write_config(const ini_t& ini, std::ostream& out)
{
    for (auto sect = ini.begin(); sect != ini.end(); sect++)
    {
        if (sect != ini.begin()) out<<std::endl;
        out<<"["<<sect->first<<"]"<<std::endl;
        for (auto parm = sect->second.begin(); parm != sect->second.end(); parm++)
        {
            out<<parm->first<<"="<<parm->second<<std::endl;
        }
    }
}

/** @brief Read ini file from specified input stream
 * @param in input stream
 * @return ini file map representation
 */
ini_t read_config(std::istream& in)
{
    ini_t ret;
    std::string section_name = "";
    for (std::string line; getline(in, line);)
    {
        /* Remove comment */
        size_t comment_pos = line.find("//");
        if (comment_pos != std::string::npos) line = line.substr(0, comment_pos);
        /* Trim line */
        line = trim(line);
        /* Check empty line */
        if (line.empty()) continue;
        /* Check section brackets */
        if (*line.begin() == '[' && *--line.end() == ']')
        {
            section_name = line.substr(1, line.length()-2);
            ret.insert(std::pair<std::string,section_t>(section_name, section_t()));
            continue;
        }
        /* Check parameter equal character */
        size_t equ_pos = line.find("=");
        if (equ_pos != std::string::npos)
        {
            std::string param_name = trim(line.substr(0, equ_pos));
            std::string param_val = trim(line.substr(equ_pos+1, line.length()-equ_pos));
            ret.at(section_name).insert(std::pair<std::string,std::string>(param_name, param_val));
        }
    }
    return ret;
}
