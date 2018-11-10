#include "mainwindow.h"
#include "appcore.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    APPCore::shared().init();
    APPModel::shared().initModels();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
