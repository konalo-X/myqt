#include "mainwindow.h"
#include"replacedlg.h"
#include<QMessageBox>
#include"aboutdlg.h"
#include<QtGui>
#include<QFontDialog>
#include<QFont>
#include<QFileDialog>
#include<QFile>
#include<QPrintPreviewDialog>
#include<QPageSetupDialog>
#include<QTextCursor>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //loadFile(fileName);
    //fileName="hello";
   // if(fileName.isEmpty())
     //   fileName="无标题";
    setWindowTitle("记事本");
    //setSizeIncrement(1800,600);
    widget=new showWidget(this);
    setCentralWidget(widget);
    finddlg=new findDlg(this);
    createActions();
    createMenus();
    p=new QPrinter;





//connect(widget->text,SIGNAL(textChanged()),this,SLOT(checkState()));
    //createToolBars();
}

MainWindow::~MainWindow()
{

}

void MainWindow::creatwidget()
{

}



void MainWindow::createActions()
{
    aboutAction=new QAction(tr("关于记事本"),this);
    aboutAction->setStatusTip("About");
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(showAbout()));

    copyAction=new QAction("复制",this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip("Copy select");
    copyAction->setDisabled(true);
    connect(widget->text,SIGNAL(copyAvailable(bool)),copyAction,SLOT(setEnabled(bool)));
    connect(copyAction,SIGNAL(triggered()),widget->text,SLOT(copy()));

    cutAction=new QAction(tr("剪切"),this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip("Cut selcet");
    cutAction->setDisabled(true);
    connect(widget->text,SIGNAL(copyAvailable(bool)),cutAction,SLOT(setEnabled(bool)));
    connect(cutAction,SIGNAL(triggered()),widget->text,SLOT(cut()));

    pageSettingAction=new QAction(tr("页面设置"),this);
    connect(pageSettingAction,SIGNAL(triggered()),this,SLOT(pageSet()));
    exitAction=new QAction(tr("退出"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("Exit Program");
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    newFileAction=new QAction(tr("新建"),this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip("New File");
    connect(newFileAction,SIGNAL(triggered()),this,SLOT(createFile()));

    openFileAction=new QAction(tr("打开"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(tr("Open File"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(OpenFile()));

    saveFileAction=new QAction(tr("保存"),this);
    saveFileAction->setShortcut(tr("Ctrl+S"));
    connect(saveFileAction,SIGNAL(triggered()),this,SLOT(saveFile()));

    saveAnotherAction=new QAction(tr("另存为"),this);
    saveAnotherAction->setShortcut(tr("Ctrl+A"));
    connect(saveAnotherAction,SIGNAL(triggered()),this,SLOT(saveAnother()));

    pasteAction=new QAction(tr("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("paste select"));
    connect(pasteAction,SIGNAL(triggered()),widget->text,SLOT(paste()));

    printAction=new QAction(tr("打印"),this);
    printAction->setShortcut(tr("Ctrl+P"));
    printAction->setStatusTip(tr("Print file"));
    connect(printAction,SIGNAL(triggered()),this,SLOT(printFile()));

    deleteAction=new QAction(tr("删除"),this);
    deleteAction->setShortcut(tr("delete"));
    deleteAction->setStatusTip(tr("Delete the select"));
    deleteAction->setDisabled(true);
    connect(widget->text,SIGNAL(copyAvailable(bool)),deleteAction,SLOT(setEnabled(bool)));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteSelect()));
    //connect(widget->text,SIGNAL(selectionChanged()),deleteAction,SLOT());

    undoAction=new QAction(tr("撤销"),this);
    undoAction->setStatusTip(tr("Undo the file"));
    connect(undoAction,SIGNAL(triggered()),widget->text,SLOT(undo()));

    findAction=new QAction(tr("查找"),this);
    findAction->setShortcut(tr("Ctrl+F"));
    findAction->setDisabled(true);
    connect(widget->text,SIGNAL(textChanged()),this,SLOT(setfindEnabled()));
    connect(findAction,SIGNAL(triggered()),this,SLOT(showFind()));
    connect(finddlg->findNextBtn,SIGNAL(clicked(bool)),this,SLOT(search()));

    findNextAction=new QAction(tr("查找下一个"),this);
    findNextAction->setShortcut(tr("F3"));
    findNextAction->setDisabled(true);
    connect(findNextAction,SIGNAL(triggered(bool)),SLOT(search()));
    replaceAction=new QAction(tr("替换"),this);
    replaceAction->setShortcut(tr("Ctrl+H"));
    connect(replaceAction,SIGNAL(triggered(bool)),this,SLOT());

    gotoAction=new QAction(tr("转到"),this);
    gotoAction->setShortcut(tr("Ctrl+G"));

    selectAllAction=new QAction(tr("全选"),this);
    selectAllAction->setShortcut(tr("Ctrl+A"));
    connect(selectAllAction,SIGNAL(triggered()),widget->text,SLOT(selectAll()));
    datetimeAction=new QAction(tr("时间/日期"),this);
    datetimeAction->setShortcut(tr("F5"));
    connect(datetimeAction,SIGNAL(triggered()),widget,SLOT(insertdate()));;

    lineWarpAction=new QAction(tr("自动换行"),this);
    lineWarpAction->setCheckable(true);
    fontAction=new QAction(tr("字体"),this);
    connect(fontAction,SIGNAL(triggered()),this,SLOT(SetFont()));
    showStatusbarAction=new QAction(tr("状态栏"),this);
    watchHelpAction=new QAction(tr("查看帮助"),this);
    connect(watchHelpAction,SIGNAL(triggered()),this
            ,SLOT(openURL()));//QDesktopServices::openUrl(QUrl("http://www.baidu.com"))));
}
void MainWindow::createMenus()
{
    fileMenu=menuBar()->addMenu(tr("文件"));

    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAnotherAction);
    fileMenu->addSeparator();
    fileMenu->addAction(pageSettingAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu=menuBar()->addMenu(tr("编辑"));
    editMenu->addAction(undoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(findNextAction);
    editMenu->addAction(replaceAction);
    editMenu->addAction(gotoAction);
    editMenu->addSeparator();
    editMenu->addAction(selectAllAction);
    editMenu->addAction(datetimeAction);

    formatMenu=menuBar()->addMenu(tr("格式"));
    formatMenu->addAction(lineWarpAction);
    formatMenu->addAction(fontAction);
    //formatMenu->setBaseSize(42,27);

    watchMenu=menuBar()->addMenu(tr("查看"));
    watchMenu->addAction(showStatusbarAction);

    help_Menu=menuBar()->addMenu(tr("帮助"));
    help_Menu->addAction(watchHelpAction);
    help_Menu->addSeparator();
    help_Menu->addAction(aboutAction);



}

void MainWindow::loadFile(QString filename)
{
    //setWindowTitle();
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())//while(!file.atEnd())
        {
            widget->text->append(textStream.readLine());
        }
    }

}

//bool MainWindow::checkState()
//{
//    if(cursor.hasSelection())
//     deleteAction->setDisabled(false);
//    else
//        deleteAction->setDisabled(true);
//    return true;
//}

void MainWindow::setfind()
{

}

void MainWindow::setfindEnabled()
{
    if(widget->text->toPlainText().isEmpty())
    {
    findAction->setDisabled(true);
    findNextAction->setDisabled(true);
    }
    else
    {
        findAction->setDisabled(false);
        findNextAction->setDisabled(false);
    }

}

void MainWindow::search()
{
    QTextCursor cursor(widget->text->document());
    QString findtext=finddlg->textfind->text();
    //QString widgetText=widget->text->toPlainText().trimmed();
    if(!finddlg->downBtn->isChecked())
    {
        if(finddlg->isUpLow->checkState()==Qt::Checked)
        {
            //findtext=findtext.toUpper();
            //widget->text->setText(findtext);

            if(widget->text->find(findtext,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively))
            {

            }
            else
            {
                QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
            }


        }
        else
        {
            //findtext=findtext.toUpper();
            if(widget->text->find(findtext,QTextDocument::FindBackward))
            {


            }
            else
            {
                QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
            }
        }
    }
    else
    {
        if(finddlg->isUpLow->checkState()==Qt::Checked)
        {
            //findtext=findtext.toUpper();
            //widget->text->setText(findtext);

            if(widget->text->find(findtext,QTextDocument::FindCaseSensitively))
            {

            }
            else
            {
                QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
            }


        }
        else
        {
            //findtext=findtext.toUpper();
            if(widget->text->find(findtext))
            {


            }
            else
            {
                QMessageBox::information(this,tr("注意"),tr("没有找到内容"),QMessageBox::Ok);
            }
        }
    }
}



void MainWindow::showAbout()
{
    //QMessageBox *customDlg;
    AboutDlg *about=new AboutDlg;
    about->show();
    about->setWindowTitle("关于\"记事本\" ");

}

void MainWindow::SetFont()
{

    QFontDialog *fontDlg=new QFontDialog;
    bool ok;
    QFont f=fontDlg->getFont(&ok);
    if(ok)
    widget->text->setFont(f);
}

void MainWindow::createFile()
{
    if(!widget->text->toPlainText().trimmed().isEmpty())
       {
    MainWindow *newFile=new MainWindow;
    newFile->show();
    }
}

void MainWindow::OpenFile()
{
   fileName=QFileDialog::getOpenFileName(this);
   if
   (widget->text->document()->isEmpty())
   {
    loadFile(fileName);
   }
   else
   {
    //widget->text->setText(fileName);
       MainWindow *newFile=new MainWindow;
       newFile->loadFile(fileName);
       newFile->show();
   }
}

void MainWindow::saveFile()
{

    QFile file(fileName);
    if(fileName!=NULL){
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream textStream(&file);
    textStream<<widget->text->document()->toPlainText();
    }
    else
    {
        saveAnother();
    }

}

void MainWindow::saveAnother()
{
    fileName=QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream textStream(&file);
    textStream<<widget->text->document()->toPlainText();
}

void MainWindow::printFile()
{

    QPrintDialog print(p,this);
    if(print.exec())
    {
        QTextDocument *doc=widget->text->document();
        doc->print(p);
    }

}

void MainWindow::printPreview()
{
    //p=new QPrinter(QPrinter::HighResolution);
    QPrintPreviewDialog preview(p,this);
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),this,SLOT(view(QPrinter*)));
    preview.exec();

}

void MainWindow::pageSet()
{

    QPageSetupDialog setPage(p,this);
    setPage.exec();
}

void MainWindow::view(QPrinter *preview)
{
    //preview->pageSize();
    widget->text->document()->print(preview);
}

void MainWindow::openURL()
{
    QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}

void MainWindow::deleteSelect()
{
   QTextCursor cursor=widget->text->textCursor();
    if(cursor.hasSelection())
    {
        cursor.removeSelectedText();
    }
    return;

}

void MainWindow::showFind()
{

    finddlg->show();
}
