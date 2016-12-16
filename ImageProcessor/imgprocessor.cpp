#include "imgprocessor.h"
#include<fstream>
#include<QTextStream>
#include<QFile>
#include<QDialog>
#include<QMessageBox>
#include<QFileDialog>
#include<QPrintDialog>
#include<QPrinter>
#include<QPainter>
#include<QColorDialog>
#include<QTextEdit>
#include<QTextList>
ImgProcessor::ImgProcessor(QWidget *parent)
    : QMainWindow(parent)                           //构造函数
{
    setWindowTitle(tr("Easy Word"));        //设置窗口标题
    showWidget=new ShowWidget(this);
    setCentralWidget(showWidget);   //这只showWidget 为中心部件
    fontLabel1=new QLabel(tr("字体"));
    fontComboBox=new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);//?
    fontLabel2=new QLabel(tr("字号"));
    sizeComboBox=new QComboBox;
    QFontDatabase db;
    foreach(int size,db.standardSizes())
        sizeComboBox->addItem(QString::number(size));
    boldBtn=new QToolButton;
    boldBtn->setIcon(QIcon("/Users/konalo/image/bold.png"));
    boldBtn->setCheckable(true);
    italicBtn=new QToolButton;
    italicBtn->setIcon(QIcon("/Users/konalo/image/italic.png"));
    italicBtn->setCheckable(true);
    underlineBtn=new QToolButton;
    underlineBtn->setIcon(QIcon("/Users/konalo/image/underline.png"));
    underlineBtn->setCheckable(true);
    colorBtn=new QToolButton;
    colorBtn->setIcon(QIcon("/Users/konalo/image/color.png"));
    colorBtn->setCheckable(true);
    //排版功能
    listlabel=new QLabel(tr("排序"));
    listComboBox=new QComboBox;
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem(("QTextListFormat::ListLowerAlpha"));//?
    listComboBox->addItem("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");

    /*创建动作 菜单 工具栏的函数*/
    createActions();
    createMenus();
    createToolBars();
    if(img.load("/Users/konalo/image/image.png"))
    {
        //在imagelabel 中心放置图像
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }
    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(showFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked()),this,SLOT(showBildBtn()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(showItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked()),this,SLOT(showUnderlineBtn()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(showColorBtn()));
    connect(showWidget->text,SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),this
            ,SLOT(showCurrentFormatChanged(const QTextCharFormat&)));
    connect(listComboBox,SIGNAL(activated(int)),this,SLOT(showList(int)));
    connect(showWidget->text->document(),SIGNAL(undoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(showWidget->text,SIGNAL(cursorPositionChanged()),this,SLOT(showCursorPositionChanged()));
}

ImgProcessor::~ImgProcessor()                       //析构函数
{

}

void ImgProcessor::createActions()                  //创建动作
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
    printTextAction->setShortcut(tr("Ctrl+P"));
    connect(printTextAction,SIGNAL(triggered()),this,SLOT(showPrintText()));
    //"打印图像"动作
    printImageAction=new QAction(tr("打印图像"),this);
    printImageAction->setStatusTip(tr("打印一副图像"));
    connect(printImageAction,SIGNAL(triggered()),this,SLOT(showPrintImage()));
    //"放大"动作
    zoomInAction=new QAction(tr("放大"),this);
    zoomInAction->setStatusTip(tr("放大一张图片"));
    connect(zoomInAction,SIGNAL(triggered()),this,SLOT(showZoomIn()));
    //"缩小"动作
    zoomOutAction=new QAction(tr("缩小"),this);
    zoomOutAction->setStatusTip(tr("缩小一张图片"));
    connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(showZoomOut()));
    //旋转动作
    //旋转90°
    rotate90Action=new QAction(tr("旋转90°"),this);
    rotate90Action->setStatusTip(tr("将图像旋转90°"));
    connect(rotate90Action,SIGNAL(triggered()),this,SLOT(showRotate90()));
    //旋转180°
    rotate180Action=new QAction(tr("旋转180°"),this);
    rotate180Action->setStatusTip(tr("将图像旋转180°"));
    connect(rotate180Action,SIGNAL(triggered()),this,SLOT(showRotate180()));
    //旋转270°
    rotate270Action=new QAction(tr("旋转270°"),this);
    rotate270Action->setStatusTip(tr("将图像旋转270°"));
    connect(rotate270Action,SIGNAL(triggered()),this,SLOT(showRotate270()));
    //实现图像镜像动作
    //纵向镜像
    mirrorVerticalAction=new QAction(tr("纵向镜像"),this);
    mirrorVerticalAction->setStatusTip(tr("对一幅图做纵向镜像"));
    connect(mirrorVerticalAction,SIGNAL(triggered()),this,SLOT(showMirrorVertical()));
    //横向镜像
     mirroeHorizontalAction=new QAction(tr("横向镜像"),this);
     mirroeHorizontalAction->setStatusTip(tr("对一幅图做横向镜像"));
     connect(mirroeHorizontalAction,SIGNAL(triggered()),this,SLOT(showMirrorHorizontal()));
    //实现撤销和恢复动作
     //撤销和恢复
     undoAction=new QAction("撤销",this);
     connect(undoAction,SIGNAL(triggered()),showWidget->text,SLOT(undo()));
     redoAction=new QAction("重做",this);
     connect(redoAction,SIGNAL(triggered()),showWidget->text,SLOT(redo()));

     //段落
     actGrp=new QActionGroup(this);

     leftAction=new QAction(QIcon("/Users/konalo/image/left.png"),
                            tr("左对齐"),actGrp);
     leftAction->setStatusTip("左对齐");
     leftAction->setCheckable(true);
     //connect(leftAction,SIGNAL(triggered()),showWidget->text,SLOT(showLeft()));
     rightAction=new QAction(QIcon("/Users/konalo/image/right.png"),
                             "右对齐",actGrp);
     rightAction->setStatusTip("右对齐");
     rightAction->setCheckable(true);
     //connect(rightAction,SIGNAL(triggered()),showWidget->text,SLOT(showRight()));
     centerAction=new QAction(QIcon("/Users/konalo/image/center.png"),
                              "居中",actGrp);
     centerAction->setStatusTip("居中");
     centerAction->setCheckable(true);
    // connect(justifyAction,SIGNAL(triggered()),;
     justifyAction=new QAction(QIcon("/Users/konalo/image/justify.png"),
                               "两端对齐",actGrp);
     justifyAction->setStatusTip("两端对齐");
     justifyAction->setCheckable(true);
     actGrp->addAction(leftAction);
     actGrp->addAction(rightAction);
     actGrp->addAction(centerAction);
     actGrp->addAction(justifyAction);

     connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(showAlignment(QAction *)));

}

/*      菜单栏     */

void ImgProcessor::createMenus()                    //创建菜单栏
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
    mirrorMenu->addAction(mirroeHorizontalAction);


}
//工具栏
void ImgProcessor::createToolBars()                 //创建工具栏
{
    //文件工具条
    fileTool=addToolBar("File111");
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

    mirrorTool=addToolBar("Mirror");
    mirrorTool->addAction(mirrorVerticalAction);
    mirrorTool->addAction(mirroeHorizontalAction);

    //字体栏
    fontToolBar=addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);

    //段落栏
    listToolBar=addToolBar("list");
    listToolBar->addWidget(listlabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actGrp->actions());

}

void ImgProcessor::loadFile(QString filename)       //加载文档
{
    //printf("file name:%s\n",filename.data());
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

void ImgProcessor::mergeFormat(QTextCharFormat fmt) //合并格式
{
    QTextCursor cursor=showWidget->text->textCursor();                                  //获得光标位置(需要改变格式位置的光标)
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);                                        //将光标所在处的词作为选择对象
    cursor.mergeCharFormat(fmt);
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::showAbout()                      //关于
{
    //QDialog *d=new QDialog(this);
    QMessageBox::about(this,"关于","This software is for learning,developed by konalo\n all Copyright©️ reserved ");
    return;
}

void ImgProcessor::newFile()                        //新建文档
{
    ImgProcessor *newfile=new ImgProcessor;
    newfile->show();
}

void ImgProcessor::openFile()                       //打开文档
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

void ImgProcessor::saveFile()                       //保存文档
{

    filename=QFileDialog::getSaveFileName(this,tr("Save File"),
                                          "/Users/konalo/myqt/新建文本.txt"
                                          );

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream out(&file);
          out<<showWidget->text->toPlainText() ;

}

void ImgProcessor::showPrintText()                  //打印文本
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec())
    {
        //获得QTextEdit对象的文档
        QTextDocument *doc=showWidget->text->document();
        doc->print(&printer);
    }
}

void ImgProcessor::showPrintImage()                 //打印图片
{
    QPrinter printer;
    QPrintDialog printerDialog(&printer,this);
    if(printerDialog.exec())//判断打印对话框显示后用户是否单击"打印"按钮
    {
        QPainter painter(&printer);//连接打印机,在打印机上画图
        QRect rec=painter.viewport();//返回图的矩形视图
        QSize size=img.size();//返回长和宽
        size.scale(rec.size(),Qt::KeepAspectRatio);//void QSize::scale(const QSize &size, Qt::AspectRatioMode mode)
        //Scales(缩放) the size to a rectangle with the given size, according to the specified mode.
   //enum Qt::AspectRatioMode 有三种KeepAspectRatio 保持长宽比率,自一张纸最大
        //KeepAspectRatioByExpanding 保持长宽比,突破一张纸
        //IgnoreAspectRatio  忽略长宽比,铺满一张纸
       // This enum type defines what happens to the aspect(朝向) ratio(比率) when scaling an rectangle.
       painter.setViewport(rec.x(),rec.y(),size.width(),size.height());
       painter.setWindow(img.rect());//设置QPainter窗口大小为图像大小
       painter.drawImage(0,0,img);//打印图像
    }
}

void ImgProcessor::showZoomIn()                     //缩放图片
{
    if(img.isNull())
        return;
    QMatrix matrix;//QMatrix 类提供二维世界坐标转换功能
    matrix.scale(2,2);
    //QImage img1=img;
    img=img.transformed(matrix);
    //重新显示设置图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::showZoomOut()                    //放大图片
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.scale(0.5,0.5);
    //QImage img1=img;
    img=img.transformed(matrix);
    //重新显示设置图形
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImgProcessor::showRotate90()                       //旋转90°
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.rotate(90);
    img=img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));

}

void ImgProcessor::showRotate180()                      //旋转180°
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.rotate(180);
    img=img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::showRotate270()                      //旋转270°
{
    if(img.isNull())
        return;
    QMatrix matrix;
    matrix.rotate(270);
    img=img.transformed(matrix);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::showMirrorVertical()                 //水平镜像
{
    if(img.isNull())
        return;
    img=img.mirrored(false,true);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::showMirrorHorizontal()               //垂直镜像
{
    if(img.isNull())
        return;
    img=img.mirrored(true,false);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImgProcessor::showFontComboBox(QString comboStr)
{
    QTextCharFormat fmt;            //创建一个QTextCharFormat 对象
    fmt.setFontFamily(comboStr);//设置字体名称
    mergeFormat(fmt);                   //合并格式
}

void ImgProcessor::ShowSizeSpinBox(QString spinValue)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(spinValue.toFloat());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::showBildBtn()                        //粗体设置
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold : QFont::Normal);
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImgProcessor::showItalicBtn()                      //斜体设置
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    showWidget->text->setCurrentCharFormat(fmt);
}

void ImgProcessor::showUnderlineBtn()                   //下划线设置
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    showWidget->text->setCurrentCharFormat(fmt);
}

void ImgProcessor::showColorBtn()
{
    QColor color=QColorDialog::getColor(Qt::red,this);//
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        showWidget->text->setCurrentCharFormat(fmt);
    }
}

void ImgProcessor::showCurrentFormatChanged(const QTextCharFormat &fmt)
{
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));//?
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.FontPointSize)));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}

/*段落*/
void ImgProcessor::showList(int index)
{
    //获得编辑框的QTextCursor对象指针
    QTextCursor cursor=showWidget->text->textCursor();
    if(index!=0)
    {
        QTextListFormat::Style style=QTextListFormat::ListDisc;//?
        switch(index)
        {
        default:
        case 1:
            style=QTextListFormat::ListDisc;
            break;
        case 2:
            style=QTextListFormat::ListCircle;
            break;
        case 3:
            style=QTextListFormat::ListSquare;
            break;
        case 4:
            style=QTextListFormat::ListDecimal;
            break;
        case 5:
            style=QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style=QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            style=QTextListFormat::ListLowerRoman;
            break;
        case 8:
            style=QTextListFormat::ListUpperRoman;
            break;
        }
        /*设置缩进值*/
        cursor.beginEditBlock();//?
        QTextBlockFormat blockfmt=cursor.blockFormat();
        QTextListFormat listfmt;
        if(cursor.currentList())
        {
            //QTextList *TL=cursor.currentList();
            listfmt=cursor.currentList()->format();
        }
        else
        {
            listfmt.setIndent(blockfmt.indent()+1);
            blockfmt.setIndent(0);
            cursor.setBlockFormat(blockfmt);
        }
        listfmt.setStyle(style);
        cursor.createList(listfmt);
        cursor.endEditBlock();
    }
    else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }

}

void ImgProcessor::showAlignment(QAction *act)
{
    //QTextCursor cursor=showWidget->text->textCursor();

    if(act==leftAction)
        showWidget->text->setAlignment(Qt::AlignLeft);
    if(act==rightAction)
        showWidget->text->setAlignment(Qt::AlignRight);
    if(act==centerAction)
        showWidget->text->setAlignment(Qt::AlignCenter);
    if(act==justifyAction)
        showWidget->text->setAlignment((Qt::AlignJustify));
    //QTextBlockFormat fmt=cursor.blockFormat();
    //cursor.mergeBlockFormat(fmt);

}

void ImgProcessor::showCursorPositionChanged()
{
    if(showWidget->text->alignment()==Qt::AlignLeft)
        leftAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignRight)
        rightAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignCenter)
        centerAction->setChecked(true);
    if(showWidget->text->alignment()==Qt::AlignJustify)
        justifyAction->setChecked(true);
}
