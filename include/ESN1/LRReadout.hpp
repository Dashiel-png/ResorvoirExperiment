#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <Eigen/Dense>
#include "Linear.hpp"

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

class LRReadout : public Linear{
    public:
    LRReadout(int rows, int cols);
    void train(MatrixXd x_train, MatrixXd y_train);
};