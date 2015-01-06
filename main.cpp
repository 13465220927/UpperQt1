#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString::fromUtf8("ZigBee实训上位机"));
    w.show();
    w.InitUI();
    return a.exec();
}
