#include "dialog.h"
#include<QFileDialog>
#include<QString>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    fileBtn=new QPushButton;
    fileBtn->setText(tr("选择文件"));
    fileLineEdit=new QLineEdit();
    QFileDialog *fileDlg=new QFileDialog(this);
    //fileDlg->setWindowTitle(tr("文件选择对话框"));
    mainlayout=new QGridLayout(this);
    mainlayout->addWidget(fileBtn,0,0);
    mainlayout->addWidget(fileLineEdit,0,1);
    //QFileDialog::getOpenFileName(this,"请选择一个文件","/", " C++ File (*.cpp :: *.h :: *.hpp :: *.c )");
    //
    connect(fileBtn,SIGNAL(clicked()),this,SLOT(showFileDlg()));
}

Dialog::~Dialog()
{

}

void Dialog::showFileDlg()
{

    QString s=QFileDialog::getOpenFileName(this,"请选择一个文件","/Users/konalo/", " C++ File (*.cpp :: *.h :: *.hpp :: *.c )");
    fileLineEdit->setText(s);
    return;
}
