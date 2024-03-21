#ifndef HH_SOLVER_HH
#define HH_SOLVER_HH

#include "step_strategies.hpp"

/*Chooses minimizing algorithm and, in the case of Gradient Descent, the step update rule.

f			function wrapper for the function to minimize;
df			function wrapper for the gradient of f;
x0			starting point;
step		initial step size (or learning rate);
step_decay	either the parameter used to decrease the step size when using Inverse or Exponential Decay or the sigma parameter of the Armijo rule;
step_tol	tolerance on the step size;
res_tol		tolerance on the residual;
max_iter	maximum number of iterations;
algorithm	determines whether to use Adam (algorithm = 1) or Gradient Descent (any other value);
strategy	determines which step update rule to use in Gradient Descent. 1 for Exponential Decay, 2 for Inverse Decay, anything else for Line Search;
verbose		true to print some information on the convergence of the algorithm;
*/
math::vector minimize(const utils::func& f, const utils::grad& df, const math::vector& x0,
	const double step, const double step_decay, const double step_tol, const double res_tol,
	const unsigned max_iter, unsigned algorithm, unsigned strategy, bool verbose);

/*Adam algorithm*/
math::vector Adam(const utils::func& f, const utils::grad& df, const math::vector& x0,
	const double step, const double step_tol, const double res_tol,
	const unsigned max_iter, bool verbose);

/*Gradient Descent algorithm. Uses template to choose the step update rule*/
template <class Strategy>
math::vector gradient_descent(const utils::func& f, const utils::grad& df, const math::vector& x0,
	const double step, const double step_decay, const double step_tol, const double res_tol,
	const unsigned max_iter, bool verbose) {

	math::vector xk(x0), x_prev(x0), gradk(df(xk));
	double alpha = 0.;
	unsigned k = 0;
	Strategy step_rule(step, step_decay, f, df);

	for (; k < max_iter; ++k) {

		alpha = step_rule(k, xk);	// find step
		xk -= alpha * gradk;		// update xk
		gradk = df(xk);				// get new gradient

		if ((xk - x_prev).norm() < step_tol || std::abs(f(xk) - f(x_prev)) < res_tol)	// convergence check
			break;

		x_prev = xk;	// store value for future convergence check
	}

	if (verbose) {
		std::cout << "\nIterations Needed: " << k << "\n";
		if (k != max_iter) {
			std::cout << "Step Residual: " << (xk - x_prev).norm() << "\n";
			std::cout << "Function Residual: " << std::abs(f(xk) - f(x_prev)) << "\n";
		}
		std::cout << "Gradient Residual: " << gradk.norm() << "\n" << std::endl;
	}

	return xk;
}

#endif