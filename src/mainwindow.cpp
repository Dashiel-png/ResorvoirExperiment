#include "mainwindow.h"


using VectorXd = Eigen::VectorXd;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize the plot widget
    customPlot = new QCustomPlot(this);
    //main window is patent of qcustomplot so once dtor called, dtor is called on qcustomplot so no need to delete
    setCentralWidget(customPlot);
    
    // Configure and populate the plot
    setupPlot();
}

MainWindow::~MainWindow() {}

void MainWindow::setupPlot() {
    VectorXd x_init = VectorXd::Zero(500);
    std::cout << "halted here" << std::endl;
    TanH active = TanH();
    ESN echo = ESN(500, x_init, active, 1);
    std::cout << "halted here" << std::endl;
    QVector<double> realParts, imagParts;
    const Eigen::MatrixXd& weights = echo.getWeight();
    assert(weights.rows()==weights.cols());
    Eigen::EigenSolver<Eigen::MatrixXd> solver(weights);
    Eigen::VectorXcd es = solver.eigenvalues();
    std::cout << "halted here" << std::endl;


    for (int i = 0; i < es.size(); ++i) {
        realParts.push_back(es(i).real());
        imagParts.push_back(es(i).imag());
    }

    customPlot->addGraph();
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    customPlot->graph(0)->setData(realParts, imagParts);
    customPlot->rescaleAxes();
    customPlot->replot();

}