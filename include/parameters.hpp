#ifndef HH_PARAMETER_STRUCT_HH
#define HH_PARAMETER_STRUCT_HH

#include "math_vector.hpp"

struct params {
	
	//! Starting Point
	math::vector x0 = { 0., 0. };
	
	//! Tolerance on step length
	double step_tol = 1e-6;

	//! Tolerance on gradient norm
	double res_tol = 1e-6;

	//! Step
	double step = 0.2;

	//! Parameter for Armijio Rule / Exponential Decay of the step / Inverse Decay of the step
	double step_decay = 0.25;

	//! Maximum number of iterations
	unsigned max_iter = 5000;

	//! Algorithm for minimization (1: ADAM, Anything else: Gradient Descent)
	unsigned algorithm = 0;

	//! Strategy for step (1: Exponential Decay, 2: Inverse Decay, Anything Else: Line Search)
	unsigned strategy = 0;

	//! Step for numerical approximation of gradient
	double h = -1.;

};

std::ostream& operator<<(std::ostream& os, const params& p);	// printing the parameters

#endif //HH_PARAMETER_STRUCT_HH