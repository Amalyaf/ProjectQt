#include "server.h"
#include <iostream>
#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = new MainWindow;
    if(w){
        w->show();
    }
    else
        return 0;
    return a.exec();
}
