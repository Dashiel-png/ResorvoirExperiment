#ifndef ESNET
#define ESNET


#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <Eigen/Dense>
#include "Activation.hpp"
#include "Tanh.hpp"

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

class ESN{
    MatrixXd weights; //weight matrix
    double param; //density paramter, default to 1 (proportion of elements in matrix set to 1)
    Activation& f; //activation function
    double sr; //spectral radius
    int dim; //number of nodes in ESN
    VectorXd state;

    public:
    ESN(int dim, VectorXd init, Activation& f, double p  = 1.0); //will initialise class weights W_con with density p, and then normalise

    const VectorXd call(VectorXd x, VectorXd v); //using this compute with the current ESN state what would happen given previous time step x and input v to the state of the network

    VectorXd& step(VectorXd v); //call with current state and input v to change network

    const MatrixXd& getWeight();

};


#endif