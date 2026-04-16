#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QDialog>
#include <QPainter>
class QSvgGenerator;
namespace Ui {
class mylogin;
}

class mylogin : public QDialog
{
    Q_OBJECT

  public:
    explicit mylogin(QDialog* parent = NULL);
    ~mylogin();
    virtual void paintEvent(QPaintEvent* event);
    void paintAll();
  signals:
    void doNow();
  private slots:
    void on_loginButton_clicked();

  private:
    Ui::mylogin* ui;
    QImage image;
};
#endif // MYLOGIN_H
