#include "ESN.hpp"

using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

ESN::ESN(int dim, Activation& f, double p, VectorXd init): param{p}, f{f}, dim{dim}, state{init} {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);

    this->weights = MatrixXd::NullaryExpr(dim, dim, [&]() { return dist(gen); } ); //initialised adjacency matrix with normal distribution
    if(p < 1){
        this->weights = MatrixXd::Zero(dim, dim);
        this->weights.reshaped().head(int(dim * dim * p)).setOnes();
        Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm(this->weights.rows()); //permutation mat of size rows

        std::iota(perm.indices().data(), perm.indices().data() + perm.indices().size(), 0); //permutation idicies filled with 0,1,...
        std::shuffle(perm.indices().data(), perm.indices().data() + perm.indices().size(), gen);

        this->weights = this->weights * perm * this->weights.transpose();
    }


    Eigen::SelfAdjointEigenSolver<MatrixXd> solver(weights);
    double maxEigen = 0;
    for(int i = 0; i < dim; i++){
        maxEigen = std::max(maxEigen, std::abs(solver.eigenvalues()(i)));
    }
    this->weights = (this->weights / maxEigen); //normalise the weights using the spectral radius

}

const VectorXd& ESN::call(VectorXd x, VectorXd v){
    VectorXd x_next = this->weights * x;
    x_next = x_next + v;
    x_next = this->f.compute(x_next); //maybe add a leaky rate later
    return x_next;
}

VectorXd& ESN::step(VectorXd v){
    this->state = this->call(this->state, v);
    return this->state;
}

