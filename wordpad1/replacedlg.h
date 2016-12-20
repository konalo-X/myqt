#ifndef REPLACEDLG_H
#define REPLACEDLG_H

#include <QDialog>

namespace Ui {
class replaceDlg;
}

class replaceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit replaceDlg(QWidget *parent = 0);
    ~replaceDlg();

private:
    Ui::replaceDlg *ui;
};

#endif // REPLACEDLG_H
