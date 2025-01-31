#ifndef UTIL_H
#define UTIL_H

#include "matrix.h"
#include <algorithm>

template<int I, int J>
matrix<I, J> relu(const matrix<I, J>& in)
{
    matrix<I, J> out;
    for (int i = 0; i < I; i++)
        for (int j = 0; j < J; j++)
            out[i][j] = std::max(in[i][j], 0.f);
    return out;
}

template<int I, int J>
matrix<I, J> drelu(const matrix<I, J>& in)
{
    matrix<I, J> out;
    for (int i = 0; i < I; i++)
        for (int j = 0; j < J; j++)
            out[i][j] = in[i][j] > 0.0f ? 1.0f : 0.0f;
    return out;
}



#endif