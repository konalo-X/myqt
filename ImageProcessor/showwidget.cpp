#include "showwidget.h"
#include<QHBoxLayout>//添加水平布局
ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    imageLabel=new QLabel;
    imageLabel->setScaledContents(true);//尽可能使pixmap填充空间
    text=new QTextEdit;
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(text);

}
