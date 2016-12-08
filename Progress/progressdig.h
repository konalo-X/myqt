#ifndef PROGRESSDIG_H
#define PROGRESSDIG_H

#include <QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QProgressBar>
#include<QComboBox>
#include<QPushButton>
#include<QGridLayout>
class ProgressDig : public QDialog
{
    Q_OBJECT

public:
    ProgressDig(QWidget *parent = 0);
    ~ProgressDig();

private slots:
    void startProgress();

private:
    QLabel *FileNum;
    QLineEdit *FileNumLineEdit;
    QLabel *ProgressType;
    QComboBox *comboBox;
    QProgressBar *progressBar;
    QPushButton *starBtn;
    QGridLayout*mainLayout;
};

#endif // PROGRESSDIG_H
