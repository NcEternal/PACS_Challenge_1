#ifndef HH_MATH_VECTOR_CLASS_HH
#define HH_MATH_VECTOR_CLASS_HH

#include <vector>
#include <string>
#include <iosfwd>
#include <sstream>

namespace math {
	/*Implements mathematical operations between vectors. Supports only vector of doubles.*/
	class vector
	{
	protected:
		std::vector<double> v_data;

	public:
		// constructors
		vector() = default;
		vector(const std::vector<double>& d) : v_data(d) {}
		vector(const std::initializer_list<double>& d) : v_data(d) {}
		vector(const unsigned size, const double value) : v_data(size, value) {}
		vector(const vector& v) : v_data(v.v_data) {};
		vector(const std::string& v) {
			std::stringstream iss(v);
			double n;
			while (iss >> n)
				v_data.push_back(n);
		};


		// some std::vector methods
		std::size_t size() const;
		void swap(math::vector& v);
		decltype(auto) emplace_back(const double value) {
#if __cplusplus < 201703L
			//emplace_back has no return value before C++17
			v_data.emplace_back(value);
			return;
#else
			return v_data.emplace_back(value);
#endif
		}


		// random access
		double at(std::size_t i) const;
		double& at(std::size_t i);
		double operator[](std::size_t i) const;
		double& operator[](std::size_t i);


		// mathematical operations
		double square_norm() const; //Square of norm
		double norm() const; //Euclidian norm
		vector& operator+=(const vector& b); //The result has the same size as the original vector. The one on the right gets treated as smaller or bigger (0-padded) if necessary
		vector& operator-=(const vector& b); //The result has the same size as the original vector. The one on the right gets treated as smaller or bigger (0-padded) if necessary
		vector& operator*=(const vector& b); //Element-wise multiplication. The result has the same size as the original vector. The one on the right gets treated as smaller or bigger (1-padded) if necessary

	};
	// mathematical operations
	vector operator+(const vector& a, const vector& b); //The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (0-padded) if necessary
	vector operator-(const vector& a, const vector& b); //The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (0-padded) if necessary
	vector operator*(double a, const vector& v); //Product with scalar
	vector operator*(const vector& v, double a); //Product with scalar
	vector operator*(const vector& a, const vector& b); //Element-wise multiplication. The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (1-padded) if necessary
	vector operator/(const vector& v, double a); //Division with scalar
	vector operator/(const vector& a, const vector& b); //Element-wise division. The result has the same size as the vector on the left. The one on the right gets treated as smaller or bigger (1-padded) if necessary
	vector pow(const vector& v, double a);	//Element-wise power
	vector pow(const vector& v, unsigned a); //Optimized Element-wise power for positive integers
	vector sqrt(const vector& v);	//Element-wise sqrt

	// printing the vector
	std::ostream& operator<<(std::ostream& os, const vector& v);
}
#endif // !HH_MATH_VECTOR_CLASS_HH

