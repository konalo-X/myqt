#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFont font("YZSong18030",12);
   // w.setBaseSize(1000,800);
    w.setMinimumSize(1000,800);
    w.setFont(font);
    w.show();

    return a.exec();
}
