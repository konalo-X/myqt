#include "showwidget.h"

showWidget::showWidget(QWidget *parent) : QWidget(parent)
{

    layout=new QHBoxLayout(this);
    text=new QTextEdit;

    layout->addWidget(text);
    text->show();

}

void showWidget::insertdate()
{

    QDateTime *datetime=new QDateTime;
    date=datetime->currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    text->insertPlainText(date);
}
