/* 
   Soduku_Util.h
   Header file for the miscellaneous utility functions that are shared
   across multiple Soduku classes/files.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* To get the filename stripped of its path and extension:
		std::string raw_file_name = get_raw_name(full_file_name);
   For example, the raw name of "some_directory/my_file.txt" will be 
   "my_file".

   To convert any string s to an int:
   		int n = string2int(s);
   Will throw logic error if the string cannot be converted to an integer.

   To convert any int n to a string:
   		std::string s = int2string(n);
 */
#ifndef SODUKU_UTIL_H
#define SODUKU_UTIL_H

std::string get_raw_name(std::string);
int string2int(std::string);
std::string int2string(int);
#endif