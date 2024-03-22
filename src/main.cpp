#include "GetPot"			// command line options
#include "read_params.hpp"	// reading parameters form .pot file
#include "solver.hpp"		// minimizing algorithms
#include "parser.hpp"		// custom parser implementation 
#include <iomanip>			// nicer final output



/*helper printer*/
void helper() {
	std::cout << "\nUSAGE: main [-h, --help] [-v, --verbose] [-n, --numerical] [-p, --parameters parameterFile] [-f, --function functionFile]" << std::endl;
	std::cout << "\n-h, --help\t\t\tthis prints help\n" << std::endl;
	std::cout << "-v, --verbose\t\t\tthis prints additional information\n" << std::endl;
	std::cout << "-n, --numerical\t\t\tthis uses numerical gradient\n" << std::endl;
	std::cout << "-p, --parameters parameterFile\tthis specifies a file contained in the \"parameters/\" folder from which to read the parameters (default: parameters.pot)\n" << std::endl;
	std::cout << "-f, --function functionFile\tthis specifies a file contained in the \"functions/\" folder from which to read the function\n"
			  << "\t\t\t\tusing this option forces usage of numerical gradient\n"
			  << "\t\t\t\tvariables in the file must be preceded by $\n\n" << std::endl;    
}



int main(int argc, char** argv) {

	GetPot cl(argc, argv);
	if (cl.search(2, "-h", "--help")) {		// help option
		helper();
		return 0;
	}

	bool verbose = false;

	if (cl.search(2, "-v", "--verbose"))	// verbose option
		verbose = true;

	bool numerical = false;

	if (cl.search(2, "-n", "--numerical"))	// numerical gradient option
		numerical = true;

	cstmparser::parser pars;
	unsigned n_vars = 2;	// number of variables for the default function defined in function_utilities.cpp
	bool using_parser = false;

	if (cl.search(2, "-f", "--function")) {	// parser option
		pars = cstmparser::create_from_file(std::string("functions/") + cl.follow("base_function.txt", 2, "-f", "--function"));
		if (verbose)
			std::cout << "\nUsing function: " << pars.get_expression() << "\n";
		n_vars = pars.num_vars();
		numerical = true;
		using_parser = true;
	}

	std::string filename = std::string("parameters/") + cl.follow("parameters.pot", 2, "-p", "--parameters");	// parameter file option
	params p = read_parameters(filename, n_vars, verbose, numerical);

#if __cplusplus < 201703L
	// unpacking for standards before C++17 
	const math::vector& x0 = p.x0;				// Starting point
	const double& step_tol = p.step_tol;		// Tolerance on step length for stopping criterion
	const double& grad_tol = p.grad_tol;		// Tolerance on gradient norm for stopping criterion
	const double& step = p.step;				// Step
	const double& step_decay = p.step_decay;	// Parameter for Armijio Rule / Exponential Decay of the step / Inverse Decay of the step
	const unsigned& max_iter = p.max_iter;		// Max number of iteration
	const unsigned& algorithm = p.algorithm;	// Algorithm for solution
	const unsigned& strategy = p.strategy;		// Strategy for step
	const double& h = p.h;						// Step for numerical approximation of gradient
#else
	// C++17 onwards unpacking. 
	const auto& [x0, step_tol, grad_tol, step, step_decay, max_iter, algorithm, strategy, h] = p;
#endif

	math::vector res;

	utils::func	f = utils::test_function;		// test function
	utils::grad grad = utils::test_gradient;	// test gradient

	if (using_parser)	// parsed function
		f = pars;

	if (numerical)		// numerical gradient
		grad = utils::auto_diff(f, h);

	res = minimize(f, grad, x0, step, step_decay, step_tol, grad_tol, max_iter, algorithm, strategy, verbose);

	std::cout << "\nSolution:\n";
	std::cout << std::fixed << std::setprecision(4) << res << std::endl;

	return 0;

}