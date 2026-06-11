#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <Eigen/Dense>

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

class Activation{
    public:
    virtual VectorXd compute(VectorXd);
};

class TanH : public Activation{
    public:
    VectorXd compute(VectorXd);
};