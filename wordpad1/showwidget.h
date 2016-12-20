#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H
#include<QAction>
#include <QMainWindow>
#include<QHBoxLayout>
#include<QTextEdit>
#include<QDateTime>
#include<QString>
class showWidget : public QWidget
{
    Q_OBJECT
public:
    explicit showWidget(QWidget *parent = 0);

    QTextEdit *text;

    QHBoxLayout *layout;
    QString date;
    bool checked;
signals:

public slots:
    void insertdate();
};

#endif // SHOWWIDGET_H
