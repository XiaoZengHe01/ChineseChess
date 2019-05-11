#include <QApplication>

#include "ChineseChess.h"


int main(int Argc,char** Argv)
{
    QApplication App(Argc,Argv);

    ChineseChess w;
    w.show();

    return App.exec();
}
