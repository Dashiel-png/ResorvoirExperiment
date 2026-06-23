#include "mainwindow.h"


using VectorXd = Eigen::VectorXd;
using MatrixXd = Eigen::MatrixXd;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize the plot widget
    customPlot = new QCustomPlot(this);
    //main window is patent of qcustomplot so once dtor called, dtor is called on qcustomplot so no need to delete
    setCentralWidget(customPlot);
    
    // Configure and populate the plot
    setupPlot2(1, 100, 100, 1000);
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


void MainWindow::setupPlot2(int dim_in, int dim_esn, int washout_time, int sample_time){
    //this will do washout with 3 different initial states of ESN
    int t_tot = washout_time + sample_time;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    TanH tanh = TanH();

    Eigen::MatrixXd X_init = MatrixXd::NullaryExpr(3, dim_esn, [&]() { return dist(gen); } ); //initial states of ESN
    Eigen::MatrixXd input = MatrixXd::NullaryExpr(t_tot, dim_in, [&]() { return dist(gen); } ); //input sequence same for each esn to see if washout works

    Linear W_in = Linear(dim_in, dim_esn, 0.1, 0);
    uint32_t seed = 42;
    ESN net1 = ESN(dim_esn, X_init.row(0).transpose(), tanh, seed);
    ESN net2 = ESN(dim_esn, X_init.row(1).transpose(), tanh, seed);
    ESN net3 = ESN(dim_esn, X_init.row(2).transpose(), tanh, seed);

    Eigen::MatrixXd xs1 = MatrixXd::Zero(t_tot, dim_esn); // T x N
    Eigen::MatrixXd xs2 = MatrixXd::Zero(t_tot, dim_esn);
    Eigen::MatrixXd xs3 = MatrixXd::Zero(t_tot, dim_esn);
    for(int i = 0; i < t_tot; i++){
        xs1.row(i) = net1.step(W_in.forward(input.row(i).transpose())).transpose();
        xs2.row(i) = net2.step(W_in.forward(input.row(i).transpose())).transpose();
        xs3.row(i) = net3.step(W_in.forward(input.row(i).transpose())).transpose();
    }   

    int T = xs1.rows();
    int N = xs1.cols();
    QVector<double> ts(T); //for plotting
    QVector<double> x0_esn1(T);
    QVector<double> x0_esn2(T);
    QVector<double> x0_esn3(T); //one for each of the echo state network with different initial inputs
    QVector<double> meanX_esn1(T);
    QVector<double> meanX_esn2(T);
    QVector<double> meanX_esn3(T);
    
    for(int i = 0; i<T; i++){
        ts[i] = i;
        x0_esn1[i] = xs1(i,0);
        x0_esn2[i] = xs2(i,0);
        x0_esn3[i] = xs3(i,0);
        meanX_esn1[i] = xs1.row(i).mean();
        meanX_esn1[i] = xs2.row(i).mean();
        meanX_esn1[i] = xs3.row(i).mean();
    }

    //plotting
    QCPLayoutGrid *grid = new QCPLayoutGrid;
    customPlot->plotLayout()->clear();
    customPlot->plotLayout()->addElement(0,0,grid);

    QCPAxisRect *rect00 = new QCPAxisRect(customPlot);
    QCPAxisRect *rect01 = new QCPAxisRect(customPlot);
    QCPAxisRect *rect10 = new QCPAxisRect(customPlot);
    QCPAxisRect *rect11 = new QCPAxisRect(customPlot);

    grid->addElement(0,0,rect00);
    grid->addElement(0,1,rect01);
    grid->addElement(1,0,rect10);
    grid->addElement(1,1,rect11);


    QVector<double> ts_mid = ts.mid(0, washout_time);
    QVector<double> ts_last = ts.mid(ts.size() - washout_time, washout_time);
    QVector<double> mean_mid_1 = meanX_esn1.mid(0, washout_time);
    QVector<double> mean_last_1 = meanX_esn1.mid(meanX_esn1.size() - washout_time, washout_time);
    QVector<double> mean_mid_2 = meanX_esn2.mid(0, washout_time);
    QVector<double> mean_last_2 = meanX_esn2.mid(meanX_esn2.size() - washout_time, washout_time);
    QVector<double> mean_mid_3 = meanX_esn3.mid(0, washout_time);
    QVector<double> mean_last_3 = meanX_esn3.mid(meanX_esn3.size() - washout_time, washout_time);

    QVector<double> x0_esn1_mid = x0_esn1.mid(0, washout_time);
    QVector<double> x0_esn1_last = x0_esn1.mid(x0_esn1.size() - washout_time, washout_time); 
    QVector<double> x0_esn2_mid = x0_esn2.mid(0, washout_time);
    QVector<double> x0_esn2_last = x0_esn2.mid(x0_esn2.size() - washout_time, washout_time); 
    QVector<double> x0_esn3_mid = x0_esn3.mid(0, washout_time);
    QVector<double> x0_esn3_last = x0_esn3.mid(x0_esn3.size() - washout_time, washout_time); 

    QCPGraph *g00_1 = customPlot->addGraph(rect00->axis(QCPAxis::atBottom), rect00->axis(QCPAxis::atLeft)); //specifies graph axis
    QCPGraph *g00_2 = customPlot->addGraph(rect00->axis(QCPAxis::atBottom), rect00->axis(QCPAxis::atLeft));
    QCPGraph *g00_3 = customPlot->addGraph(rect00->axis(QCPAxis::atBottom), rect00->axis(QCPAxis::atLeft));
    QCPGraph *g01_1 = customPlot->addGraph(rect01->axis(QCPAxis::atBottom), rect01->axis(QCPAxis::atLeft));
    QCPGraph *g01_2 = customPlot->addGraph(rect01->axis(QCPAxis::atBottom), rect01->axis(QCPAxis::atLeft));
    QCPGraph *g01_3 = customPlot->addGraph(rect01->axis(QCPAxis::atBottom), rect01->axis(QCPAxis::atLeft));
    QCPGraph *g11_1 = customPlot->addGraph(rect11->axis(QCPAxis::atBottom), rect11->axis(QCPAxis::atLeft));
    QCPGraph *g11_2 = customPlot->addGraph(rect11->axis(QCPAxis::atBottom), rect11->axis(QCPAxis::atLeft));
    QCPGraph *g11_3 = customPlot->addGraph(rect11->axis(QCPAxis::atBottom), rect11->axis(QCPAxis::atLeft));
    QCPGraph *g10_1 = customPlot->addGraph(rect10->axis(QCPAxis::atBottom), rect10->axis(QCPAxis::atLeft));
    QCPGraph *g10_2 = customPlot->addGraph(rect10->axis(QCPAxis::atBottom), rect10->axis(QCPAxis::atLeft));
    QCPGraph *g10_3 = customPlot->addGraph(rect10->axis(QCPAxis::atBottom), rect10->axis(QCPAxis::atLeft));

    g10_1->setData(ts_mid, mean_mid_1);
    g10_2->setData(ts_mid, mean_mid_2);
    g10_3->setData(ts_mid, mean_mid_3);
    g11_1->setData(ts_last, mean_last_1);
    g11_2->setData(ts_last, mean_last_2);
    g11_3->setData(ts_last, mean_last_3);
    g00_1->setData(ts_mid, x0_esn1_mid);
    g00_2->setData(ts_mid, x0_esn2_mid);
    g00_3->setData(ts_mid, x0_esn3_mid);
    g01_1->setData(ts_last, x0_esn1_last);
    g01_2->setData(ts_last, x0_esn2_last);
    g01_3->setData(ts_last, x0_esn3_last);

    customPlot->rescaleAxes();
    customPlot->replot();
}