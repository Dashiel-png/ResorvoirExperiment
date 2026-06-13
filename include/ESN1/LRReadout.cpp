#include "LRReadout.hpp"

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;


LRReadout::LRReadout(int rows, int cols) : Linear(rows, cols, 1, 0) {};

void LRReadout::train(MatrixXd x_train, MatrixXd y_train){
    MatrixXd X_bias = MatrixXd::Ones(x_train.rows(), x_train.cols() + 1);
    X_bias.rightCols(x_train.cols());
    Linear::setWeight(X_bias.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(y_train));
}