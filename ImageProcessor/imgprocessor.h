#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include <QMainWindow>
#include<QImage>
#include<QLabel>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QComboBox>
#include<QSpinBox>//?
#include<QToolBar>
#include<QFontComboBox>
#include<QToolButton>
#include<QTextCharFormat>
#include"showwidget.h"

class ImgProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImgProcessor(QWidget *parent = 0);
    ~ImgProcessor();
    void createActions();                   //创建动作
    void createMenus();                     //创建菜单
    void createToolBars();                  //创建工具栏
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);
protected slots:
    void showAbout();
    void newFile();
    void openFile();
    void saveFile();
    void showPrintText();
    void showPrintImage();
    void showZoomIn();
    void showZoomOut();
    void showRotate90();
    void showRotate180();
    void showRotate270();
    void showMirrorVertical();
    void showMirrorHorizontal();
    //字体
protected slots:
    void showFontComboBox(QString comboStr);
    void ShowSizeSpinBox(QString spinValue);
    void showBildBtn();
    void showItalicBtn();
    void showUnderlineBtn();
    void showColorBtn();
    void showCurrentFormatChanged(const QTextCharFormat &fmt);
    //段落
    void showList(int);
    void showAlignment(QAction *);
    void showCursorPositionChanged();
private:
    QMenu *fileMenu;                    //各项菜单栏
    QMenu*zoomMenu;
    QMenu*rotateMenu;
    QMenu*mirrorMenu;
    QImage img;
    QString filename;
    ShowWidget *showWidget;
    QAction *openFileAction;
    QAction*newFileAction;
    QAction*printTextAction;
    QAction*printImageAction;
    QAction*exitAction;
    QAction*SaveFileAction;
    QAction*copyAction;                 //编辑菜单栏
    QAction*cutAction;
    QAction*pasteAction;
    QAction*aboutAction;
    QAction*zoomInAction;
    QAction*zoomOutAction;
    QAction*rotate90Action;             //旋转菜单栏
    QAction*rotate180Action;
    QAction*rotate270Action;
    QAction*mirrorVerticalAction;       //镜像菜单栏
    QAction*mirroeHorizontalAction;
    QAction*undoAction;
    QAction*redoAction;
    QToolBar*fileTool;                       //工具栏
    QToolBar*zoomTool;
    QToolBar*rotateTool;
    QToolBar*mirrorTool;
    QToolBar*doToolBar;
    /*字体设置*/
    QLabel *fontLabel1;
    QFontComboBox *fontComboBox;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;
    QToolBar *fontToolBar;
    /*段落设置*/
    QLabel *listlabel;
    QComboBox *listComboBox;
    QActionGroup *actGrp;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QToolBar *listToolBar;

};

#endif // IMGPROCESSOR_H
