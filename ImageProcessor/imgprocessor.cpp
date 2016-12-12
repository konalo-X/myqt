#include "imgprocessor.h"
#include<fstream>
#include<QTextStream>
#include<QFile>
#include<QDialog>
#include<QMessageBox>
#include<QFileDialog>
ImgProcessor::ImgProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Easy Word"));        //设置窗口标题
    showWidget=new ShowWidget(this);
    setCentralWidget(showWidget);   //这只showWidget 为中心部件
    /*创建动作 菜单 工具栏的函数*/
    createActions();
    createMenus();
    createToolBars();
    if(img.load("/Users/konalo/image/image.png"))
    {
        //在imagelabel 中心放置图像
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }

}

ImgProcessor::~ImgProcessor()
{

}

void ImgProcessor::createActions()
{
    //"打开"动作
    openFileAction =new QAction(tr("打开"),this);
    openFileAction->setShortcut(tr("Ctrl+o"));          //定义快捷键
    openFileAction->setStatusTip(tr("打开一个文件"));//???????????
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    //"新建"动作
    newFileAction=new QAction(tr("新建"),this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip(tr("新建一个文件"));
    connect(newFileAction,SIGNAL(triggered()),this,SLOT(newFile()));
    //保存动作
    SaveFileAction=new QAction(tr("保存"),this);
    SaveFileAction->setShortcut(tr("Ctrl+S"));
    SaveFileAction->setStatusTip(tr("保存文件"));
    connect(SaveFileAction,SIGNAL(triggered()),this,SLOT(saveFile()));
    //"退出"动作
    exitAction=new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    //"复制"动作
    copyAction=new QAction(tr("复制"),this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("复制文件"));
    connect(copyAction,SIGNAL(triggered()),showWidget->text,SLOT(copy()));
    //"剪切"动作
    cutAction=new QAction(tr("剪切"),this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("剪切文件"));
    connect(cutAction,SIGNAL(triggered()),showWidget->text,SLOT(cut()));
    //"粘贴"动作
    pasteAction=new QAction(tr("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip("粘贴文件");
    connect(pasteAction,SIGNAL(triggered()),showWidget->text,SLOT(paste()));
    //"about"动作
    aboutAction=new QAction(tr("关于"),this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(showAbout()));

    //"打印"动作
    printTextAction=new QAction(tr("打印文本"),this);
    printTextAction->setStatusTip(tr("打印一个文本"));
    //"打印图像"动作
    printImageAction=new QAction(tr("打印图像"),this);
    printImageAction->setStatusTip(tr("打印一副图像"));
    //"放大"动作
    zoomInAction=new QAction(tr("放大"),this);
    zoomInAction->setStatusTip(tr("放大一张图片"));
    //"缩小"动作
    zoomOutAction=new QAction(tr("缩小"),this);
    zoomOutAction->setStatusTip(tr("缩小一张图片"));
    //旋转动作
    //旋转90°
    rotate90Action=new QAction(tr("旋转90°"),this);
    rotate90Action->setStatusTip(tr("将图像旋转90°"));
    //旋转180°
    rotate180Action=new QAction(tr("旋转180°"),this);
    rotate180Action->setStatusTip(tr("将图像旋转180°"));
    //旋转270°
    rotate270Action=new QAction(tr("旋转270°"),this);
    rotate270Action->setStatusTip(tr("将图像旋转270°"));
    //实现图像镜像动作
    //纵向镜像
    mirrorVerticalAction=new QAction(tr("纵向镜像"),this);
    mirrorVerticalAction->setStatusTip(tr("对一幅图做纵向镜像"));
    //横向镜像
     mirroeHorizontalAction=new QAction(tr("横向镜像"),this);
     mirroeHorizontalAction->setStatusTip(tr("对一幅图做横向镜像"));
    //实现撤销和恢复动作
     //撤销和恢复
     undoAction=new QAction("撤销",this);
     connect(undoAction,SIGNAL(triggered()),showWidget->text,SLOT(undo()));
     redoAction=new QAction("重做",this);
     connect(redoAction,SIGNAL(triggered()),showWidget->text,SLOT(redo()));

}

/*      菜单栏     */

void ImgProcessor::createMenus()
{
    //文件菜单
    fileMenu=menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(printTextAction);
    fileMenu->addAction(printImageAction);
    fileMenu->addAction(SaveFileAction);
    fileMenu->addSeparator();//增加分隔符
    fileMenu->addAction(exitAction);
    //缩放菜单
    zoomMenu=menuBar()->addMenu(tr("编辑"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);

    //旋转菜单
    rotateMenu=menuBar()->addMenu(tr("旋转"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    //镜像菜单
    mirrorMenu=menuBar()->addMenu(tr("镜像"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorVerticalAction);


}
//工具栏
void ImgProcessor::createToolBars()
{
    //文件工具条
    fileTool=addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(newFileAction);
    fileTool->addAction(SaveFileAction);
    fileTool->addAction(printTextAction);
    fileTool->addAction(printImageAction);
    //编辑工具条
    zoomTool=addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addAction(aboutAction);
    zoomTool->addSeparator();
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);
    //旋转工具条
    rotateTool=addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);
    //撤销和重做工具条
    doToolBar=addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);



}

void ImgProcessor::loadFile(QString filename)
{
    printf("file name:%s\n",filename.data());
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            showWidget->text->append(textStream.readLine());
            printf("read line \n");
            printf("end\n");
        }
    }


}

void ImgProcessor::showAbout()
{
    //QDialog *d=new QDialog(this);
    QMessageBox::about(this,"关于","This software is for learning,developed by konalo\n all Copyright©️ reserved ");
    return;
}

void ImgProcessor::newFile()
{
    ImgProcessor *newfile=new ImgProcessor;
    newfile->show();
}

void ImgProcessor::openFile()
{

    filename=QFileDialog::getOpenFileName(this,"打开文件...","/Users/konalo","*.txt  :: *.cpp :: *.hpp :: *.h :: *.c :: *.pro");
   //if(!filename.isEmpty())
   {
    if(showWidget->text->document()->isEmpty())
    {
        loadFile(filename);
    }
    else
    {
         ImgProcessor *newfile=new ImgProcessor;
         newfile->show();
         newfile->loadFile(filename);
    }
    }
}

void ImgProcessor::saveFile()
{

    filename=QFileDialog::getSaveFileName(this);

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream out(&file);
          out<<showWidget->text->toPlainText() ;

}
