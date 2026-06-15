#include "ESN1/ESN.hpp"
#include "ESN1/Linear.hpp"
#include "Metrics/BasicComp.cpp"
#include "qcustomplot/qcustomplot.h"

int main(void){
    // 1. Solve system or model data using Eigen
    Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(100, 0, 10);
    Eigen::VectorXd y = x.array().sin(); 

    // 2. Convert Eigen vectors to std::vector to interface with the GUI
    std::vector<double> x_data(x.data(), x.data() + x.size());
    std::vector<double> y_data(y.data(), y.data() + y.size());

    // 3. Plot inside Qt (using QCustomPlot)
    QCustomPlot *customPlot = new QCustomPlot();
    QVector<double> qX(x_data.begin(), x_data.end());
    QVector<double> qY(y_data.begin(), y_data.end());
    customPlot->addGraph();
    customPlot->graph(0)->setData(qX, qY);
    customPlot->rescaleAxes();
    customPlot->replot();
    return 0;
}

