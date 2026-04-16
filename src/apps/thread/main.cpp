#include <QApplication>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QThread>
#include <QDebug>
#include "widget.h"

void printText(QString text, int count)
{
    for (int i = 0; i < count; ++i)
        qDebug() << text << QThread::currentThreadId();
    qDebug() << text << "Done";
}

int testfeature(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    QFuture<void> f1 = QtConcurrent::run(printText, QString("A"), 100000); // 类似执行线程函数
    QFuture<void> f2 = QtConcurrent::run(printText, QString("B"), 10000);
    QFuture<void> f3 = QtConcurrent::run(printText, QString("C"), 1000);
    QFutureWatcher<void> futureWatcher; // 监视线程函数执行完成，以及下方完毕的回调
    QObject::connect(&futureWatcher, &QFutureWatcher<void>::finished, &w, &Widget::mySlot);
    futureWatcher.setFuture(f1); // 只能监视一个线程函数，监视完成后会发出finished信号，触发回调函数

        QFutureWatcher<void> futureWatcher2;
    QObject::connect(&futureWatcher2, &QFutureWatcher<void>::finished, &w, &Widget::mySlot);
    futureWatcher2.setFuture(f2);
        QFutureWatcher<void> futureWatcher3;
    QObject::connect(&futureWatcher3, &QFutureWatcher<void>::finished, &w, &Widget::mySlot);
    futureWatcher3.setFuture(f3);

    // f1.waitForFinished();
    // f2.waitForFinished();
    // f3.waitForFinished();
    return a.exec();
}



int testworker(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
   
    
    return a.exec();
}

int main(int argc, char* argv[])
{

   return // testfeature(argc, argv);
   testworker(argc, argv);
}