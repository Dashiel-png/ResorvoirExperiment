#include "Tanh.hpp"

TanH::TanH() : Activation() {}

VectorXd TanH::compute(VectorXd x){
    VectorXd output = x.array().tanh();
    return output;
}