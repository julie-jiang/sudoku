#include <iostream>
#include <sstream>
#include "Soduku_Util.h"
std::string get_raw_name(std::string filename)
{
	std::string raw_name = filename.substr(0, filename.find_last_of("."));
    raw_name = raw_name.substr(raw_name.find_last_of("/\\") + 1);
    return raw_name;
}
/*
 * Convert a string to an int. 
 * Throw runtime error if the string is not numerical.
 */
int string2int(std::string s)
{
    std::stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw std::logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* 
 * Converts an int to string.
 * Parameters: an int that needs to be converted a string.
 * Returns: the string form of the int
 */
std::string int2string(int num)
{
    std::string result;
    std::ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}