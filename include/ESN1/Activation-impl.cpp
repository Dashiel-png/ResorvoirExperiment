#include "Activation.hpp"

using VectorXd = Eigen::VectorXd;

VectorXd TanH::compute(VectorXd x){
    VectorXd output = x.array().tanh();
    return output;
}