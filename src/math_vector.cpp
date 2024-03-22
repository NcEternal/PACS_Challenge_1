#include "math_vector.hpp"
#include <cmath>

namespace math {

	//Square of norm
	double vector::norm_square() const {
		double res = 0.;
		for (const double& a : v_data)
			res += a * a;
		return res;
	}

	//Euclidian norm
	double vector::norm() const {
		return std::sqrt(norm_square());
	}

	//The result has the same size as the original vector. The one on the right gets treated as smaller or bigger (0-padded) if necessary
	vector& vector::operator+=(const vector& b) {
		std::size_t small = std::min(v_data.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			v_data[i] += b[i];
		}

		return *this;

	}

	//The result has the same size as the original vector. The one on the right gets treated as smaller or bigger (0-padded) if necessary
	vector& vector::operator-=(const vector& b) {
		std::size_t small = std::min(v_data.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			v_data[i] -= b[i];
		}

		return *this;
	}

	//Element-wise multiplication. The result has the same size as the original vector. The one on the right gets treated as smaller or bigger (1-padded) if necessary
	vector& vector::operator*=(const vector& b) {
		std::size_t small = std::min(v_data.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			v_data[i] *= b[i];
		}

		return *this;
	}

	//The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (0-padded) if necessary
	vector operator+(const vector& a, const vector& b) {
		vector c(a);

		std::size_t small = std::min(a.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			c[i] += b[i];
		}

		return c;

	}

	//The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (0-padded) if necessary
	vector operator-(const vector& a, const vector& b) {
		vector c(a);

		std::size_t small = std::min(a.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			c[i] -= b[i];
		}

		return c;

	}

	//Product with scalar
	vector operator*(double a, const vector& v) {
		vector res(v);
		for (size_t i = 0; i < v.size(); ++i) {
			res[i] *= a;
		}
		return res;
	}

	//Product with scalar
	vector operator*(const vector& v, double a) {
		return a * v;
	}

	//Element-wise division. The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (1-padded) if necessary
	vector operator*(const vector& a, const vector& b) {
		vector c(a);

		std::size_t small = std::min(a.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			c[i] *= b[i];
		}

		return c;
	}

	//Division with scalar
	vector operator/(const vector& v, double a) {
		return (1. / a) * v;
	}

	//Element-wise division. The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (1-padded) if necessary
	vector operator/(const vector& a, const vector& b) {
		vector c(a);

		std::size_t small = std::min(a.size(), b.size());

		for (size_t i = 0; i < small; ++i) {
			c[i] /= b[i];
		}

		return c;
	}

	//Element-wise power
	vector pow(const vector& v, double a) {	
		vector res(v);
		for (size_t i = 0; i < v.size(); ++i) {
			res[i] = std::pow(res[i], a);
		}
		return res;
	}

	//Optimized Element-wise power for positive integers
	vector pow(const vector& v, unsigned a) {
		vector res(v.size(), 1.);
		vector base(v);
		while (a > 0) {
			if (a & 1)			// if a is odd {
				res *= base;	// multiply final result by base }
			base *= base;		// square base
			a >>= 1;			// divide a by 2 (floor rounding)
		}
		return res;
	}

	//Element-wise sqrt
	vector sqrt(const vector& v) {
		vector res(v);
		for (size_t i = 0; i < v.size(); ++i) {
			res[i] = std::sqrt(res[i]);
		}
		return res;
	}

	// Output vector to stream
	std::ostream& operator<<(std::ostream& os, const vector& v) {
		for (size_t i = 0; i < v.size(); ++i)
			os << v[i] << " ";
		os << std::endl;
		return os;
	}
}