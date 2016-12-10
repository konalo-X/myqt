#ifndef EXTENSIONDLG_H
#define EXTENSIONDLG_H
#include"db.h"
#include <QDialog>

class ExtensionDlg : public QDialog
{
    Q_OBJECT

public:
    ExtensionDlg(QWidget *parent = 0);
    ~ExtensionDlg();
private:
    void createBaseDlg();//实现基本对话框
    void createDetailDlg();//实现拓展对话框
    QWidget *baseWidget;//基本窗体部件
    QWidget *detailWidget;//拓展窗体部件
    bool isShow;
    class db;
private slots:
    void showDetail();//显示拓展窗体

};

#endif // EXTENSIONDLG_H
