#include "finddlg.h"
#include<QWidget>
findDlg::findDlg(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("查找");
    findContent=new QLabel(this);
    findContent->setText(tr("查找内容( &N)"));
    textfind=new QLineEdit(this);
    //textfind->setFocus();
    findContent->setBuddy(textfind);
    findNextBtn=new QPushButton(this);
    findNextBtn->setText(tr("查找下一个( &F)"));
    cancelBtn=new QPushButton(this);
    cancelBtn->setText(tr("取消"));
    isUpLow=new QCheckBox(this);
    isUpLow->setText(tr("区分大小写( &C)"));
    isUpLow->setCheckState(Qt::CheckState::Unchecked);
    direction=new QGroupBox(tr("方向"));
    //direction->setObjectName("方向");
    upBtn=new QRadioButton;
    upBtn->setText(tr("向上( &U)"));
    downBtn=new QRadioButton;
    downBtn->setText(tr("向下( &D)"));
    upBtn->setChecked(true);
    QHBoxLayout *inGroup=new QHBoxLayout;
    inGroup->addWidget(upBtn);
    inGroup->addWidget(downBtn);
    direction->setLayout(inGroup);
    //direction->;
    //direction->;
    //mainlayout=new QGridLayout(this);
    //QWidget *left=new QWidget;
    //QWidget *rignt=new QWidget;
    QGridLayout *leftWidget=new QGridLayout;
    leftWidget->addWidget(findContent,0,0);
    leftWidget->addWidget(textfind,0,1,1,3);
    leftWidget->addWidget(isUpLow,1,0,Qt::AlignBottom);
    //leftWidget->addWidget(direction,1,1);
    leftWidget->addWidget(direction,1,1,1,1);
    //leftWidget->addWidget(downBtn,1,2);
    QVBoxLayout *rightlayout=new QVBoxLayout;
    rightlayout->addWidget(findNextBtn);
    rightlayout->addWidget(cancelBtn);
    QHBoxLayout *layout=new QHBoxLayout(this);
    layout->addLayout(leftWidget);
    layout->addLayout(rightlayout);
    //layout->SetFixedSize;
    setFixedSize(sizeHint());
    setTabOrder(textfind,findNextBtn);
    setTabOrder(findNextBtn,isUpLow);
    setTabOrder(isUpLow,downBtn);
    setTabOrder(downBtn,cancelBtn);
    connect(cancelBtn,SIGNAL(clicked(bool)),SLOT(close()));


    //text=new QLineEdit(this);
    //okBtn=new QPushButton(this);
    //okBtn->setText("Ok");

}
