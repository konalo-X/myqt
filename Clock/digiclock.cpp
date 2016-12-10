#include "digiclock.h"
#include<QTimer>
#include<QTime>
#include<QMouseEvent>
#include<QPalette>
#include<QDialog>
#include<QString>
DigiClock::DigiClock(QWidget * parent):
    QLCDNumber(parent)
{
    /*设置时钟背景*/
    QPalette p=palette();
    p.setColor(QPalette::Window,Qt::white);
    p.setColor(QPalette::WindowText,Qt::black);
    setPalette(p);
    setWindowFlags(Qt::FramelessWindowHint);//?//设置窗体标示,此处设置为一个没有面板边框和标题栏的窗体
    setWindowTitle(tr("电子时钟"));
    setWindowOpacity(0.5);//设置窗体透明度
    QTimer *timer=new QTimer(this);//定时器,设定多少时间刷新一次
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(1000);//1秒刷新一次
    showTime();
    resize(200,60);
    showColon=true;
}

void DigiClock::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton)
    {
        dragPosition=event->globalPos()-frameGeometry().topLeft();
        //globalPos()--Returns the global position of the mouse cursor at the time of the event.返回鼠标敲击结束时的位置
       //frameGeometry().topLeft()----Returns window frame topleft 返回窗口左顶点位置

        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
        close();
    }
}

void DigiClock::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-dragPosition);
        event->accept();
    }
}


void DigiClock::showTime()
{
    QTime time=QTime::currentTime();
    QString text=time.toString("hh:mm:ss");
    if(showColon)
    {
        text[2]=':';
        text[5]=':';

        showColon=false;
    }
    else
    {
        text[2]=' ';
        text[5]=' ';


        showColon=true;
    }
    DigiClock::setDigitCount(8);
    display(text);

}
