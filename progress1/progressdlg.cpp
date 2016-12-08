#include "progressdlg.h"
#include<QProgressDialog>
#include<QFont>

ProgressDlg::ProgressDlg(QWidget *parent)
    : QDialog(parent)
{
    QFont font("ZYSong18030",12);
    setFont(font);
    FileNum=new QLabel;
    FileNum->setText(tr("文件数目:"));
    ProgressType=new QLabel;
    ProgressType->setText(tr("显示类型:"));
    FileNumLineEdit=new QLineEdit;
    FileNumLineEdit->setText(tr("100000"));
    comboBox=new QComboBox;
    comboBox->addItem(tr("ProgressBar"));
    comboBox->addItem(tr("ProgressDialog"));

     progressBar=new QProgressBar(this);
//progressbar->setSizePolicy();

    startBtn=new QPushButton("开始");
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(FileNum,0,0);
    mainLayout->addWidget(FileNumLineEdit,0,1);
    mainLayout->addWidget(ProgressType,1,0);
    mainLayout->addWidget(comboBox,1,1);
    mainLayout->addWidget(progressBar,2,0,1,2);
    mainLayout->addWidget(startBtn,3,1);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startProgress()));


}


ProgressDlg::~ProgressDlg()
{

}

void ProgressDlg::startProgress()
{
    bool ok;
    int num =FileNumLineEdit->text().toInt(&ok);

    if(comboBox->currentIndex()==0)
    {/*
        progressBar->setRange(0,num);
        for(int i=1;i<num+1;i++)
        {
            progressBar->setValue(i);
        }
        */
        //comboBox->setCurrentIndex(1);
        progressBar->setRange(0,num);
        for(int i=1;i<num+1;i++)
        progressBar->setValue(i);
    }
    else if(comboBox->currentIndex()==1)
    {
        QProgressDialog *progressDialog=new QProgressDialog(this);
        QFont font("ZYSong18030",12);
        progressDialog->setFont(font);
        progressDialog->setWindowModality(Qt::WindowModal);
        progressDialog->setMinimumDuration(5);//?
        progressDialog->setWindowTitle("please wait");
        progressDialog->setLabelText("Copying.....");
        progressDialog->setCancelButtonText("Cancel");
        progressDialog->setRange(0,num);
        for(int i=1;i<num+1;i++)
        {
            progressDialog->setValue(i);
            if(progressDialog->wasCanceled())
                return ;
        }
    }
}
