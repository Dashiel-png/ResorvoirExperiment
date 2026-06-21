#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ESN1/ESN.hpp"
#include "ESN1/Linear.hpp"
#include "Metrics/BasicComp.cpp"
#include "ESN1/Tanh.hpp"

#include <QMainWindow>
#include "qcustomplot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QCustomPlot *customPlot;
    void setupPlot();
};

#endif // MAINWINDOW_H