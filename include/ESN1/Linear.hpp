#ifndef LINEAR
#define LINEAR

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <Eigen/Dense>

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

class Linear{
    MatrixXd weights;
    VectorXd bias;

    int inputdim, outputdim;

    public:
    //generate weights based on uniform distribution
    Linear(int inputdim, int outputdim, double distbounds, double biasbound);

    ~Linear() {};

    VectorXd forward(const VectorXd& in);

    const MatrixXd& getWeight();

    void setWeight(MatrixXd w);
};


#endif