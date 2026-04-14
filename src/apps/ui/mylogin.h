#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QDialog>


namespace Ui {
    class mylogin;
}

class mylogin : public QDialog
{
    Q_OBJECT

public:
    explicit mylogin(QDialog *parent = NULL);
    ~mylogin();
signals:
    void doNow();
private slots:
    void on_loginButton_clicked();
private:
    Ui::mylogin *ui;
};
#endif // MYLOGIN_H
