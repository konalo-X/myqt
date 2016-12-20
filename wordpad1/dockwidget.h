#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H
//#include"showwidget.h"
#include <QMainWindow>
#include<QTextEdit>
#include<QDockWidget>
class dockWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit dockWidget(QWidget *parent = 0);
    void createText();
public:
    QTextEdit *text;
signals:

public slots:
};

#endif // DOCKWIDGET_H
