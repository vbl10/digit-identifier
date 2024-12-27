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
    matrix<10, 16> w3;
    matrix<10, 1> b3;

public:

    matrix<10,1> predict(matrix<28*28, 1> in)
    {
        auto a1 = relu(w1 * in + b1);
        auto a2 = relu(w2 * a1 + b2);
        auto a3 = relu(w3 * a2 + b3);

        return a3;
    }

    void train(const std::vector<std::pair<matrix<28*28, 1>, char>>& dataset)
    {
        // while gradient magnitude is significant
        {            
            matrix<16, 28*28> grad_w1;
            matrix<16, 1> grad_b1;
            matrix<16, 16> grad_w2;
            matrix<16, 1> grad_b2;
            matrix<10, 16> grad_w3;
            matrix<10, 1> grad_b3;

            //use only 100 random samples for each gradient descent step (gradient approximation)
            for (int gradientApproxCount = 0; gradientApproxCount < 100; gradientApproxCount++)
            {
                const auto& sample = dataset[int((float)rand() / (float)RAND_MAX * 60000.0f)];

                matrix<10, 1> y = { 0 };
                y[sample.second][0] = 1.0f;
                
                // value of the layer 3 node
                auto z1 = w1 * sample.first + b1;
                auto a1 = relu(z1);
                auto z2 = w2 * a1 + b2;
                auto a2 = relu(z2);
                auto z3 = w3 * a2 + b3;
                auto a3 = relu(z3);

                // cost
                // auto C = (a3 - y).hadamard(a3 - y);

                const auto dC_dz3 = 2.0f*(a3 - y).hadamard(drelu(z3));
                // dC/dw3 = dC/da3 * da3/dz3 * dz3/dw3
                // dC/dw3 = 2*(a3 - y) * relu'(z3) * a2
                grad_w3 = grad_w3 + dC_dz3 * a2.transpose();

                // dC/db3 = dC/da3 * da3 * dz3/db3
                // dC/dw3 = 2*(a3 - y) * relu'(z3) * 1
                grad_b3 = grad_b3 + dC_dz3;

                // C = (a3 - y)²
                // C = [(relu(w3 * a2 + b3)) - y]²
                // C = [(relu(w3 * relu(w2 * a1 + b2) + b3)) - y]²
                //
                // dC/dw2 = 
                //  2*[(relu(w3 * relu(w2 * a1 + b2) + b3)) - y] * 
                //  relu'(w3 * relu(w2 * a1 + b2) + b3)) * 
                //  relu'(w2 * a1 + b2) * 
                //  a1
                //
                // dC/dw2 = 
                //  2*[a3 - y] * 
                //  relu'(z3)) * 
                //  relu'(z2) * 
                //  a1
                //
                // dC/dw2 = 
                //  dC/dz3 * 
                //  relu'(z2) * 
                //  a1
                //
                
                grad_w2 = dC_dz3 * drelu(z2) * a1;

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