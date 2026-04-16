#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include "myworker.h"
#include <QThreadPool>
#include "myprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void mySlot();
    void handleResults(int res);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
