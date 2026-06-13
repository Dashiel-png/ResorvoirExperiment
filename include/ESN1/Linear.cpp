#include "Linear.hpp"

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;


Linear::Linear(int inputdim, int outputdim, double distbounds, double biasbound): inputdim{inputdim}, outputdim{outputdim}{
    std::mt19937 gen(42); // Fixed seed for reproducibility
        std::uniform_real_distribution<double> dist(-distbounds, distbounds);
    
    //Initialize Input weights
    this->weights = MatrixXd::NullaryExpr(outputdim, inputdim, [&]() { return dist(gen); });

    this->bias = VectorXd::NullaryExpr(outputdim, [&]() { return dist(gen); });
}

VectorXd& Linear::forward(const VectorXd& in){
    VectorXd out = this->weights * in + bias;
    return out;
}

const MatrixXd& Linear::getWeight(){
    return this->weights;
}

void Linear::setWeight(MatrixXd w){
    this->weights = w;
}