#include <iostream>
#include "Soduku_Util.h"
std::string get_raw_filename(std::string filename)
{
	std::string raw_name = filename.substr(0, filename.find_last_of("."));
    raw_name = raw_name.substr(raw_name.find_last_of("/\\") + 1);
    return raw_name;
}