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

	matrix<J, I> transpose() const
	{
		matrix<J, I> transp;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < J; j++)
				transp[j][i] = a[i][j];
		return transp;
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

	matrix operator*(float rhs) const
	{
		matrix prod;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < J; j++)
				prod[i][j] = a[i][j] * rhs;
		return prod;
	}

	matrix hadamard(const matrix& rhs) const
	{
		matrix had;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < J; j++)
				had[i][j] = a[i][j] * rhs[i][j];
		return had;
	}

	matrix operator+(const matrix& rhs) const
	{
		matrix sum;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < J; j++)
				sum[i][j] = a[i][j] + rhs[i][j];
		return sum;
	}

	matrix operator-(const matrix& rhs) const
	{
		matrix sub;
		for (int i = 0; i < I; i++)
			for (int j = 0; j < J; j++)
				sub[i][j] = a[i][j] - rhs[i][j];
		return sub;
	}
};

template <int I, int J>
matrix<I, J> operator*(float lhs, const matrix<I, J>& rhs)
{
	matrix<I, J> prod;
	for (int i = 0; i < I; i++)
	{
		for (int j = 0; j < J; j++)
		{
			prod[i][j] = lhs * rhs[i][j];
		}
	}
	return prod;
}

#endif