#include "parser.hpp"
#include <fstream>

namespace cstmparser {

	void parser::set_variables() {	// helper for constructors and assignment

		if (x.size() != variables.length())
			x = math::vector(variables.length(), 0.);

		std::size_t i = 0;	// counter

		for (char& c : variables) {
			pars.DefineVar(std::string(1, c), &x[i]);	// add variable to the parser
			++i;
		}

	}

	parser::parser(const std::string& expr) {

		if (expr[0] != '$')		// '$' indicates a the following character is a variable and should be excluded from the real expression
			expression += expr[0];	

		for (std::size_t i = 1; i < expr.length(); ++i) {

			if (expr[i] == '$')
				continue;

			if (expr[i - 1] == '$' && variables.find(expr[i]) == std::string::npos)	// only add a char to the variable string if it is preceded by '$' and isn't in it already
				variables += expr[i];

			expression += expr[i];

		}

		set_variables();

		pars.SetExpr(expression);	// set parser expression

	}

	parser::parser(const parser& p) : x(p.x), pars(), variables(p.variables), expression(p.expression) {	// copy constructor
		
		pars.SetExpr(expression);
			
		set_variables();

	}
	
	parser& parser::operator=(const parser& p) { // assignement
		
		if (this != &p) {

			pars.ClearVar();
			x = p.x;
			variables = p.variables;
			expression = p.expression;
			pars.SetExpr(expression);

			set_variables();

		}

		return *this;

	}

	double parser::operator() (const math::vector& input) const {
		x = input;	// copy input vector into the variable vector before evaluating
		return pars.Eval();
	}

	parser create_from_file(const std::string& filename) {

		std::ifstream infile(filename);
		// check if file exists
		if (!infile) {
			std::cerr << "\nERROR: Function file " << filename << " does not exist" << std::endl;
			std::cerr << "Reverting to default function." << std::endl;
			infile.close();
			return parser("$x*$y + 4*$x^2 + $y^2 + 3*$x");
		}

		std::string line;
		std::getline(infile, line);
		infile.close();
		return parser(line);

	}

}