#ifndef DIALOG_H
#define DIALOG_H
#include<QDialog>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget *parent=0);
};

#endif // DIALOG_H
