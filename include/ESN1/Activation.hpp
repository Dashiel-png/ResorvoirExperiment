#ifndef ACTIVATION
#define ACTIVATION

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <Eigen/Dense>

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

class Activation{
    public:
    Activation() = default;
    virtual VectorXd compute(VectorXd) = 0;
    virtual ~Activation() = default;
};


#endif