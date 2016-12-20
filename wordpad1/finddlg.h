#ifndef FINDDLG_H
#define FINDDLG_H

#include <QObject>
#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QDialog>
#include<QHBoxLayout>
#include<QGroupBox>
#include<QCheckBox>
#include<QRadioButton>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QLabel>
class findDlg : public QDialog

{
public:
    findDlg(QWidget *parent=0);
    QLineEdit *textfind;
    QPushButton *findNextBtn;
    QPushButton *cancelBtn;
    QCheckBox *isUpLow;
    QGroupBox *direction;
    QRadioButton *upBtn;
    QRadioButton *downBtn;
    QLabel *findContent;
    //QHBoxLayout *layout;
    //QGridLayout *mainlayout;

};

#endif // FINDDLG_H
