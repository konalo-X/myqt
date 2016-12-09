#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QLineEdit>
#include<QGridLayout>
#include<QPushButton>
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    QPushButton *fileBtn;
    QLineEdit *fileLineEdit;
    QGridLayout *mainlayout;
private slots:
    void showFileDlg();

};

#endif // DIALOG_H
