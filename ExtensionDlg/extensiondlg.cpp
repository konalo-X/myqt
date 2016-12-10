#include "extensiondlg.h"
#include<QVBoxLayout>
#include<QLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QComboBox>
ExtensionDlg::ExtensionDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Extension Dialog"));//设置对话框标题
    createBaseDlg();
    createDetailDlg();
    QVBoxLayout *layout=new QVBoxLayout(this);//垂直布局
    layout->addWidget(baseWidget);
    layout->addWidget(detailWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(10);


}

ExtensionDlg::~ExtensionDlg()
{

}

void ExtensionDlg::createBaseDlg()
{
    baseWidget=new QWidget(this);
    QLabel *nameLabel=new QLabel(tr("姓名:"));
    QLineEdit *nameLineEdit=new QLineEdit;
    QPushButton *okBtn=new QPushButton(tr("确定"));
    QLabel *sexLabel=new QLabel(tr("性别:"));
    QComboBox *sexComboBox=new QComboBox;
    sexComboBox->addItem(tr("男"));
    sexComboBox->addItem(tr("女"));
    QPushButton *detailBtn=new QPushButton(tr("详细"));
    QGridLayout *baseLayout=new QGridLayout(baseWidget);
    baseLayout->addWidget(nameLabel,0,0);
    baseLayout->addWidget(nameLineEdit,0,1);
    baseLayout->addWidget(okBtn,0,2);
    baseLayout->addWidget(sexLabel,1,0);
    baseLayout->addWidget(sexComboBox,1,1);
    baseLayout->addWidget(detailBtn,1,2);

    connect(detailBtn,SIGNAL(pressed()),this,SLOT(showDetail()));
}

void ExtensionDlg::createDetailDlg()
{
    detailWidget=new QWidget(this);
    QLabel *ageLabel=new QLabel("年龄:");
    QLineEdit *ageLineEdit=new QLineEdit;
    QLabel *departmentLabel=new QLabel("部门:");
    QStringList list;
    list<<"部门1"<<"部门2"<<"部门3";
    QComboBox *departmentComo=new QComboBox;
    departmentComo->addItems(list);
    QLabel *emailLabel=new QLabel("E-Mail:");
    QLineEdit *emailLineEdit=new QLineEdit;
    QGridLayout *detaillayout=new QGridLayout(detailWidget);
    detaillayout->addWidget(ageLabel,0,0);
    detaillayout->addWidget(ageLineEdit,0,1);
    detaillayout->addWidget(departmentLabel,1,0);
    detaillayout->addWidget(departmentComo,1,1);
    detaillayout->addWidget(emailLabel,2,0);
    detaillayout->addWidget(emailLineEdit,2,1);
    detailWidget->hide();
    isShow=true;

}

void ExtensionDlg::showDetail()
{

    if(isShow==true)
    {
     detailWidget->show();
     isShow=false;
    }
    else
    {
        detailWidget->hide();
        isShow=true;
    }

}
