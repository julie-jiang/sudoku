#ifndef SODUKU_PARSER_H
#define SODUKU_PARSER_H
class Soduku_Parser {
	public:
		Soduku_Parser(int, char **);
		static void help_message();
		std::string filename;
		bool solve_one; 
		std::string filelist;
		bool solve_all;
		std::string directory;
		bool write;
		bool print;
	private:
		bool arg_solve(std::string);
		bool arg_solve_all(std::string);
		bool arg_write(std::string);
		bool arg_hide(std::string);



};
#endif