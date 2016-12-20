#include "replacedlg.h"
#include "ui_replacedlg.h"

replaceDlg::replaceDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::replaceDlg)
{
    ui->setupUi(this);
}

replaceDlg::~replaceDlg()
{
    delete ui;
}
