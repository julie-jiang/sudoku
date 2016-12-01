/* 
   Soduku_Util.cpp
   Implementaions of the miscellaneous utility functions that are shared
   across multiple Soduku classes/files.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
#include <iostream>
#include <sstream>
#include "Soduku_Util.h"
/* Returns the given filename stripped of its path and extension.
   For example, the input "some_directory/my_file.txt" will have "my_file"
   returned. */
std::string get_raw_name(std::string filename) {
	std::string raw_name = filename.substr(0, filename.find_last_of("."));
    raw_name = raw_name.substr(raw_name.find_last_of("/\\") + 1);
    return raw_name;
}
/* Convert a string to an int. Returns the int form of the given string.
   Throw logic error if the string is not numerical. */
int string2int(std::string s) {
    std::stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw std::logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Converts an int to string.
   Returns the string form of the given int */
std::string int2string(int num) {
    std::string result;
    std::ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}