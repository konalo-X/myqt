#include "palette.h"
#include<QGridLayout>
#include<QHBoxLayout>
Palette::Palette(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout *mainLayout=new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

Palette::~Palette()
{

}

void Palette::createCtrlFrame()
{
    ctrlFrame=new QFrame;//颜色选择面板

    windowLabel=new QLabel(tr("QPalette::window:    "));
    windowComboBox=new QComboBox;//创建一个comboBox对象
    fillColorList(windowComboBox);//?
    connect(windowComboBox,SIGNAL(activated(int)),this,SLOT(showWindow()));//??
    windowTextLabel=new QLabel(tr("QPalette::WindowText:    "));
    windowTextComboBox=new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox,SIGNAL(activated(int)),this,SLOT(showWindowText()));
    buttonLabel=new QLabel(tr("QPalttte::Button:    "));
    buttonComboBox=new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox,SIGNAL(activated(int)),this,SLOT(showButton()));
    buttonTextLabel=new QLabel(tr("QPalette::ButtonText:    "));
    buttonTextComboBox=new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox,SIGNAL(activated(int)),this,SLOT(showButtonText()));
    baseLabel=new QLabel(tr("QPalette::Base:    "));
    baseComboBox=new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox,SIGNAL(activated(int)),this,SLOT(showBase()));
    //左侧布局
    QGridLayout *leftlayout=new QGridLayout(ctrlFrame);
    leftlayout->addWidget(windowLabel,0,0);
    leftlayout->addWidget(windowComboBox,0,1);
    leftlayout->addWidget(windowTextLabel,1,0);
    leftlayout->addWidget(windowTextComboBox,1,1);
    leftlayout->addWidget(buttonLabel,2,0);
    leftlayout->addWidget(buttonComboBox,2,1);
    leftlayout->addWidget(buttonTextLabel,3,0);
    leftlayout->addWidget(buttonTextComboBox,3,1);
    leftlayout->addWidget(baseLabel,4,0);
    leftlayout->addWidget(baseComboBox,4,1);
    leftlayout->setMargin(10);
    leftlayout->setSpacing(15);
}

void Palette::createContentFrame()
{
    contentFrame=new QFrame;
    label1=new QLabel(tr("请选择一个值:"));
    label2=new QLabel(tr("请输入字符串:"));
    comboBox1=new QComboBox;
    comboBox1->setAutoFillBackground(true);
    comboBox1->setEditable(true);
    lineEdit2=new QLineEdit;
    QGridLayout *rightTopLayout=new QGridLayout;
    rightTopLayout->addWidget(label1,0,0);
    rightTopLayout->addWidget(comboBox1,0,1);
    rightTopLayout->addWidget(label2,1,0);
    rightTopLayout->addWidget(lineEdit2,1,1);


    textEdit=new QTextEdit;
    OkBtn=new QPushButton(tr("确认"));
    CancelBtn=new QPushButton(tr("取消"));
    QHBoxLayout *buttomLayout=new QHBoxLayout;
    buttomLayout->addWidget(OkBtn);
    buttomLayout->addWidget(CancelBtn);

    QVBoxLayout *rightLayout=new QVBoxLayout(contentFrame);
    rightLayout->addLayout(rightTopLayout);
    rightLayout->addWidget(textEdit);
    rightLayout->addLayout(buttomLayout);



}

void Palette::fillColorList(QComboBox *comboBox)
{
    QStringList colorList;
   // colorList<<"yellow"<<"red";
    colorList=QColor::colorNames();
    //comboBox->addItems(colorList);
    QString color;
    foreach(color,colorList)
    {
        QPixmap pix(QSize(70,20));
        pix.fill(QColor(color));
        comboBox->addItem(QIcon(pix),NULL);
        comboBox->setIconSize(pix.size());
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

void Palette::showWindow()
{
    //QPalette::setColor(QPalette::Window,QColor::setColorFromString)
    //获得当前的颜色值
    QStringList colorList=QColor::colorNames();
    QColor color=QColor(colorList[(windowComboBox->currentIndex())]);
    QPalette p=contentFrame->palette();
    p.setColor(QPalette::Window,color);
    //把修改后的调色板信息应用到contentFrame窗体中,更新显示
    contentFrame->setPalette(p);
    contentFrame->update();

}

void Palette::showWindowText()
{
    //确认当前选择的颜色
    QStringList ColorList=QColor::colorNames();
    QColor color=QColor(ColorList[windowComboBox->currentIndex()]);
    QPalette p=ctrlFrame->palette();//?
    p.setColor(QPalette::WindowText,color);
    contentFrame->setPalette(p);
    contentFrame->update();

}

void Palette::showButton()
{
    QStringList colorlist=QColor::colorNames();
    //获得当前选择的颜色
    QColor color=QColor(colorlist[buttonComboBox->currentIndex()]);
    QPalette p=contentFrame->palette();
    p.setColor(QPalette::Button,color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showButtonText()
{
    QStringList colorlist=QColor::colorNames();
    QColor color=QColor(colorlist[buttonTextComboBox->currentIndex()]);
    QPalette p=contentFrame->palette();
    p.setColor(QPalette::ButtonText,color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Palette::showBase()
{
    QStringList colorlist=QColor::colorNames();
    QColor color=QColor(colorlist[baseComboBox->currentIndex()]);
    QPalette p=contentFrame->palette();
   // p.setColor(QPalette::Base,color);
    QBrush brush;//=QBrush();
    brush.setTextureImage(QImage("/Users/konalo/Pictures/IMG_0333.jpg"));
    p.setBrush(QPalette::Base,brush);
    contentFrame->setPalette(p);
    contentFrame->update();
}
