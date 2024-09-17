#ifndef NN16X16_H
#define NN16X16_H

#include "matrix.h"
#include "util.h"

class nn16x16
{
private:
    //hidden layers
    matrix<16, 28*28> w1;
    matrix<16, 1> b1;
    matrix<16, 16> w2;
    matrix<16, 1> b2;
    //output
    matrix<10, 16> wo;
    matrix<10, 1> bo;

public:

    matrix<10,1> predict(matrix<28*28, 1> in)
    {
        auto l1 = relu(w1 * in + b1);
        auto l2 = relu(w2 * l1 + b2);
        auto out = relu(wo * l2 + bo);

        return out;
    }

    void train(const std::vector<std::pair<matrix<28*28, 1>, matrix<10, 1>>>& dataset)
    {
        // while gradient magnitude is significant
        {
            float cost = 0.0f;
            for (const auto& sample : dataset)
            {
                auto pred = predict(sample.first);
                for (int i = 0; i < pred.I; i++)
                {
                    cost += 
                        (
                            (pred[i][0] - sample.second[i][0]) * 
                            (pred[i][0] - sample.second[i][0])
                        ) / (float)dataset.size();
                }
            }

            // calculate gradient (back propagation)
        };
    }

    float test(const std::vector<matrix<28*28, 1>>& dataset)
    {
        return 0;
    }
};

#endif