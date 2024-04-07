//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "Chess.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Chess w;
    w.show();
    return a.exec();
}
