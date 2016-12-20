#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"showwidget.h"
#include"finddlg.h"
#include"replacedlg.h"
//#include"testdlg.h"////////////////////////
#include <QMainWindow>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QWidget>
#include<QToolBar>
#include<QStatusBar>
#include<QDockWidget>
#include<QPrinter>
#include<QPrintDialog>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void creatwidget();
    void createActions();
    void createMenus();
    //void createToolBars();
    void createStatusBar();
    void loadFile(QString);


private:
    showWidget *widget;
    QTextCursor cursor;
    Ui::replaceDlg *re;

    QPrinter *p;
    findDlg *finddlg;
    bool ok;
    QAction *openFileAction;        //打开
    QAction *newFileAction;         //新建
    QAction *saveFileAction;        //保存
    QAction *saveAnotherAction;     //另存为
    QAction *pageSettingAction;     //页面设置
    QAction *printAction;           //打印
    QAction *exitAction;            //退出
    QAction *copyAction;            //复制
    QAction *cutAction;             //剪切
    QAction *pasteAction;           //粘贴
    QAction *undoAction;            //撤销
    QAction *deleteAction;          //删除
    QAction *findAction;            //查找
    QAction *findNextAction;        //查找下一个
    QAction *replaceAction;         //替换
    QAction *gotoAction;            //跳转
    QAction *selectAllAction;       //全选
    QAction *datetimeAction;        //时间/日期
    QAction *lineWarpAction;        //自动换行
    QAction *fontAction;            //字体
    QAction *showStatusbarAction;       //状态栏
    QAction *watchHelpAction;       //查看帮助
    QAction *aboutAction;           //关于记事本

//    QToolBar *fileToolBar;          //文件工具栏
//    QToolBar *editToolBar;          //编辑
//    QToolBar *formatToolBar;        //格式
//    QToolBar *watchToolBar;         //查看
//    QToolBar *helpToolBar;          //帮助

    QMenu *fileMenu;                //文件菜单栏
    QMenu *editMenu;                //编辑
    QMenu *formatMenu;              //格式
    QMenu *watchMenu;               //查看
    QMenu *help_Menu;               //关于

    //QDockWidget *dockwindow;
    QStatusBar *statusBar;          //状态栏
    QString fileName;

signals:

private slots:

    void showAbout();
    void SetFont();
    void createFile();
    void OpenFile();
    void saveFile();
    void saveAnother();
    void printFile();
    void printPreview();
    void pageSet();
    void view(QPrinter*);
    void openURL();
    void deleteSelect();
    void showFind();
    //bool checkState();
    void setfind();
    void setfindEnabled();
    void search();
};

#endif // MAINWINDOW_H
