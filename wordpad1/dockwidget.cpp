#include "dockwidget.h"

dockWidget::dockWidget(QWidget *parent) : QMainWindow(parent)
{
    //setWindowTitle("dock");
    text=new QTextEdit(this);
    text->setAlignment(Qt::AlignCenter);
    text->setText("hello bbbbbbbbbbbbbbbbb");
    setCentralWidget(text);
    QDockWidget *dock=new QDockWidget(tr("新建"),this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea);
    dock->setWidget(text);

}

void dockWidget::createText()
{

}
