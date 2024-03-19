#include "function_utilities.hpp"

namespace utils {
	double test_function(const math::vector& x) {
		return x[0] * x[1] + 4 * x[0] * x[0] + x[1] * x[1] + 3 * x[0];
	}

	math::vector test_gradient(const math::vector& x) {
		math::vector res(x.size(), 0.);

		res[0] = x[1] + 8 * x[0] + 3;
		res[1] = x[0] + 2 * x[1];

		return res;
	}
}