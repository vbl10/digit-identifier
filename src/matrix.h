#ifndef MATRIX_H
#define MATRIX_H

#include <string>

template<int _I, int _J>
class matrix
{
public:
	static constexpr int I = _I;
	static constexpr int J = _J;

	float a[I][J] = { 0 };

	static matrix identity()
	{
		matrix mat;
		for (int i = 0; i < I; i++)
			mat.a[i][i] = 1;
		return mat;
	}

	float const* operator[](int i) const { return a[i]; }
	float* operator[](int i) { return a[i]; }

	std::string to_string() const
	{
		std::string str;
		for (int i = 0; i < I; i++) {
			for (int j = 0; j < J; j++)
				str += std::to_string(a[i][j]) + '\t';
			str += '\n';
		}
		return str;
	}

	template <int K>
	matrix<I, K> operator*(const matrix<J, K>& rhs) const
	{
		matrix<I, K> prod;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < K; j++)
				for (int k = 0; k < J; k++)
					prod[i][j] += a[i][k] * rhs[k][j];
		return prod;
	}

	matrix operator+(const matrix& rhs) const
	{
		matrix sum;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < J; j++)
				sum[i][j] = a[i][j] + rhs[i][j];
		return sum;
	}
};

#endif