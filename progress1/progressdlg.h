#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H

#include <QDialog>
#include<QLabel>
#include<QPushButton>
#include<QComboBox>
#include<QLineEdit>
#include<QProgressBar>
#include<QGridLayout>
class ProgressDlg : public QDialog
{
    Q_OBJECT

public:
    ProgressDlg(QWidget *parent = 0);
    ~ProgressDlg();
private:
    QLabel *FileNum;
    QLabel *ProgressType;
    QLineEdit *FileNumLineEdit;
    QComboBox *comboBox;
    QPushButton *startBtn;
    QProgressBar *progressBar;
    QGridLayout *mainLayout;

private slots:
    void startProgress();
};

#endif // PROGRESSDLG_H
