#ifndef HH_FUNCTION_UTILITIES_HH
#define HH_FUNCTION_UTILITIES_HH

#include "math_vector.hpp"
#include <functional>

namespace utils {
	/*Some utilities for the program*/

	/*aliases for function wrappers*/
	using func = std::function<double(const math::vector&)>;
	using grad = std::function<math::vector(const math::vector&)>;

	/*Test function*/
	inline double test_function(const math::vector& x) {
		return x[0] * x[1] + 4 * x[0] * x[0] + x[1] * x[1] + 3 * x[0];
	}

	/*Test gradient*/
	inline math::vector test_gradient(const math::vector& x) {
		math::vector res(x.size(), 0.);

		res[0] = x[1] + 8 * x[0] + 3;
		res[1] = x[0] + 2 * x[1];

		return res;
	}

	/*Numerical gradient*/
	inline auto auto_diff = [](const func& f, const double& h) {
		return [f, h](const math::vector& x) {
			math::vector r;
			math::vector e_h(x.size(), 0.);
			for (size_t i = 0; i < x.size(); ++i) {
				e_h[i] = h;
				r.emplace_back((f(x + e_h) - f(x - e_h)) / (2 * h));
				e_h[i] = 0.;
			}
			return r;
		};
	};
}
#endif