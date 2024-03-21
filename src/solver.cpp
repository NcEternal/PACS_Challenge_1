#include "solver.hpp"
#include <iostream>

math::vector minimize(const utils::func& f, const utils::grad& df, const math::vector& x0,
	const double step, const double step_decay, const double step_tol, const double res_tol,
	const unsigned max_iter, unsigned algorithm, unsigned strategy, bool verbose) {

	if (algorithm == 1) 
		return Adam(f, df, x0, step, step_tol, res_tol, max_iter, verbose);

	switch (strategy) {
	case 1:
		return gradient_descent<ExponentialDecay>(f, df, x0, step, step_decay, step_tol, res_tol, max_iter, verbose);
	case 2:
		return gradient_descent<InverseDecay>(f, df, x0, step, step_decay, step_tol, res_tol, max_iter, verbose);
	default:
		return gradient_descent<LineSearch>(f, df, x0, step, step_decay, step_tol, res_tol, max_iter, verbose);
	}
}

math::vector Adam(const utils::func& f, const utils::grad& df, const math::vector& x0,
	const double step, const double step_tol, const double res_tol,
	const unsigned max_iter, bool verbose) {

	math::vector xk(x0), x_prev(x0), gradk(df(xk));
	math::vector m(x0.size(), 0.), v(x0.size(), 0.), m_hat(x0.size(), 0.), v_hat(x0.size(), 0.);
	const math::vector epsilon(x0.size(), 1e-8);
	const long double beta1 = 0.9, beta2 = 0.999;
	long double b1 = 0.9, b2 = 0.999;
	unsigned k = 0;
	
	for (; k < max_iter; ++k) {

		m = beta1 * m + (1 - beta1) * gradk;			// update first moment
		v = beta2 * v + (1 - beta2) * gradk * gradk;	// update second moment

		m_hat = m / (1 - b1);	// bias-correct first moment
		v_hat = v / (1 - b2);	// bias-correct second moment

		xk -= step * m_hat / (math::sqrt(v_hat) + epsilon); // update xk

		gradk = df(xk);		// get new gradient

		if ((xk - x_prev).norm() < step_tol || std::abs(f(xk) - f(x_prev)) < res_tol)	// convergence check
			break;

		x_prev = xk;	// store value for future convergence check

		b1 *= beta1;	// update for next iteration
		b2 *= beta2;	// update for next iteration

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
