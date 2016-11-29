#ifndef SODUKU_PARSER_H
#define SODUKU_PARSER_H
class Soduku_Parser {
	public:
		Soduku_Parser(int, char **);
		static void help_message();
		std::string input_path;
		std::string output_path;
		bool solve_one; 
		bool solve_all;
		bool check_one;
		bool check_all;
		bool write;
		bool print;
	private:
		void parse_first_argument(std::string);
		void parse_optional_arguments(int , char **);

};
#endif