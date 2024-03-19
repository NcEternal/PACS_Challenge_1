#ifndef HH_STEP_STRATEGIES_HH
#define HH_STEP_STRATEGIES_HH

#include "function_utilities.hpp"
#include <cmath>

/*Exponential Decay strategy*/
class ExponentialDecay {
private:
	const double step;
	const double decay_rate;

public:
	// Constructor. Takes func and grad as inputs to allow for use as a template together with the LineSearch class
	ExponentialDecay(double s, double d, const utils::func& func, const utils::grad& grad) : step(s), decay_rate(d) {}
	
	// Step update. Takes a vector as input to allow for use as a template together with the LineSearch class
	double operator()(unsigned k, const math::vector& xk) const {
		return step * std::exp(-decay_rate * k);
	}
};


/*Inverse Decay strategy*/
class InverseDecay {
private:
	const double step;
	const double decay_rate;

public:
	// Constructor. Takes func and grad as inputs to allow for use as a template together with the LineSearch class
	InverseDecay(double s, double d, const utils::func& func, const utils::grad& grad) : step(s), decay_rate(d) {}

	// Step update. Takes a vector as input to allow for use as a template together with the LineSearch class
	double operator()(unsigned k, const math::vector& xk) const {
		return step / (1 + decay_rate * k);
	}
};


/*Line Search strategy*/
class LineSearch {
private:
	const double step;
	const double sigma;
	const utils::func f;
	const utils::grad df; 

	// Check on decrease condition
	inline bool check(const math::vector& xk, double alpha) const {

		math::vector g = df(xk);
		double n = g.norm();

		return (f(xk) - f(xk - alpha * g)) >= sigma * alpha * n * n;

	}

public:
	// Constructor
	LineSearch(double s, double d, const utils::func& func, const utils::grad& grad) : step(s), sigma(d), f(func), df(grad) {}

	// Step update. Takes an unsigned as input to allow for use as a template together with the ExponentialDecay and InverseDecay classes
	double operator()(unsigned k, const math::vector& xk) const {
		double alpha = step;

		while (!check(xk, alpha))
			alpha /= 2.;

		return alpha;
	}

};

#endif