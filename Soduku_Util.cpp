#include <iostream>
#include "Soduku_Util.h"
std::string Soduku_Util::get_raw_file_name(std::string filename)
{
	std::string raw_name = filename.substr(0, filename.find_last_of("."));
    raw_name = raw_name.substr(raw_name.find_last_of("/\\") + 1);
    return raw_name;
}