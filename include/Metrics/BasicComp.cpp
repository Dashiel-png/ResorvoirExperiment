#ifndef ESNCOMP1
#define ESNCOMP1

#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <random>

namespace ESNBenchmark {
    //this first one is for the NARMA10 time series that uses moving average
    template <typename Derived>
    //dense base is the base class for all eigen dense objects
    Eigen::VectorXd generate_narma10(const Eigen::DenseBase<Derived>& input_sequence) {
        if (input_sequence.size() < 10) {
            throw std::invalid_argument("Input sequence must contain at least 10 elements.");
        }

        const int n_steps = input_sequence.size();
        Eigen::VectorXd y = Eigen::VectorXd::Zero(n_steps);

        // Initial 10 steps of the series are initialized to small random values or zeros
        for (int t = 9; t < n_steps - 1; ++t) {
            // sum_{i=0}^9 y(t - i)
            double sum_y = 0.0;
            for (int i = 0; i < 10; ++i) {
                sum_y += y(t - i);
            }

            y(t + 1) = 0.3 * y(t) 
                       + 0.05 * y(t) * sum_y 
                       + 1.5 * input_sequence(t) * input_sequence(t - 9) 
                       + 0.1;
        }

        return y;
    }

    //this next one is for the normalised root mean square error divide rmse by sd of all actual output data
    template <typename Derived1, typename Derived2>
    double NRMSE(Eigen::DenseBase<Derived1> target, Eigen::DenseBase<Derived1> pred){
        if(target.size() != pred.size() || target.size() == 0){
            throw std::invalid_argument("dimension mismatch or invalid");
        }

        double mse = (target - pred).squaredNorm() / target.size;
        double rmse = std::sqrt(mse);

        double mean_target = target.mean();
        double var = 0;
        for(int i=0; i<target.size(); ++i){
            var += std::pow(target(i) - mean_target, 2);
        }
        var = var/target.size();
        double std_target = std::sqrt(var);
        if (std_target < 1e-12) {
            return 0.0;
        }
        return rmse/std_target;
    }
}

#endif