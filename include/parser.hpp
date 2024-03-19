#ifndef HH_PARSER_CLASS_HH
#define HH_PARSER_CLASS_HH

#include "math_vector.hpp"
#include "muParser.h"

namespace cstmparser {
	/*Class to implement a custom parser. 
	The variables in the function to be parsed must be preceded by $. 
	The order in which they appear is the one in which they are evaluated 
	(eg. $x - $y evaluated in (1, 2) is -1, but so is $y - $x because y appears in the function first and is thus associated to the first coordinate)
	This allows the parser to handle any number of variables.
	*/
	class parser {
	private:
		mutable math::vector x;	
		mu::Parser pars;
		std::string variables;
		std::string expression;

		void set_variables();	// Helper for constructors and assignment

	public:
		parser() = default;
		parser(const std::string& expr);	// Constructor, expr is the string containing the function
		parser(const parser& p);			// Copy constructor
		parser& operator=(const parser& p); // Assignment

		inline std::size_t num_vars() const { return x.size(); }		// Get number of variables
		inline std::string get_expression() const { return expression; } // Get expression

		double operator()(const math::vector& input) const; // Evaluating the parsed function

		~parser() { pars.ClearVar(); } // Destructor
	};

	parser create_from_file(const std::string& filename);	// Helper function to build from file. 
															// The file should contain the function in a single line at the start of the file

}


#endif