#include "ESN1/ESN.hpp"
#include "ESN1/Linear.hpp"
#include "Metrics/BasicComp.cpp"
#include "qcustomplot/qcustomplot.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(600, 400);
    w.show();
    return a.exec();
}

