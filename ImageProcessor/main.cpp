#include "imgprocessor.h"
#include <QApplication>
#include<QFont>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImgProcessor w;
    QFont font("ZYSong18030",14);
    w.setFont(font);
    w.show();

    return a.exec();
}
