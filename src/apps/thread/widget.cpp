#include "widget.h"
#include "ui_widget.h"
#include <QThread>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->labDemo->setText(tr("0"));
    /*
核心流程可以概括为：
创建一个 QThread
创建一个工作对象 myworker
把 workerObject 移动到线程里
线程启动后执行 workerObject::process()
计算完成后发信号回 UI 线程
*/
    /*
    QThread* workerThread = new QThread;
    myworker* workerObject = new myworker;
    workerObject->moveToThread(workerThread);

    // 线程启动 → 发出 started()，process() 确实是在新线程中跑的，不会阻塞 UI
    connect(workerThread, &QThread::started, workerObject, &myworker::process);

    // 任务结束 → 退出线程
    connect(workerObject, &myworker::doneProcess, workerThread, &QThread::quit);

    // 跨线程通信
    connect(workerObject, &myworker::showResults, this, &Widget::handleResults);

    // 自动删除
    connect(workerThread, &QThread::finished, workerObject, &myworker::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &myworker::deleteLater);
    workerThread->start();
    */




    // 测试多线程加锁
    /*   
int myNumber = 5;
    QMutex* newMutex = new QMutex;
    QThread* workerThread = new QThread;
    QThread* workerThread2 = new QThread;
    QThread* workerThread3 = new QThread;
    myworker* workerObject = new myworker(newMutex);
    myworker* workerObject2 = new myworker(newMutex);
    myworker* workerObject3 = new myworker(newMutex);
    workerObject->myInputNumber = &myNumber;
    workerObject->moveToThread(workerThread);
    connect(workerThread, &QThread::started, workerObject, &myworker::process);
    connect(workerObject, &myworker::doneProcess, workerThread, &QThread::quit);
    connect(workerObject, &myworker::doneProcess, workerObject, &myworker::deleteLater);
    connect(workerObject, &myworker::showResults, this, &Widget::handleResults);
    connect(workerThread, &QThread::finished, workerObject, &myworker::deleteLater);
    workerObject2->myInputNumber = &myNumber;
    workerObject2->moveToThread(workerThread2);
    connect(workerThread2, &QThread::started, workerObject2, &myworker::process);
    connect(workerObject2, &myworker::doneProcess, workerThread2, &QThread::quit);
    connect(workerObject2, &myworker::doneProcess, workerObject2, &myworker::deleteLater);
    connect(workerObject2, &myworker::showResults, this, &Widget::handleResults);
    connect(workerThread2, &QThread::finished, workerObject2, &myworker::deleteLater);
    workerObject3->myInputNumber = &myNumber;
    workerObject3->moveToThread(workerThread3);
    connect(workerThread3, &QThread::started, workerObject3, &myworker::process);
    connect(workerObject3, &myworker::doneProcess, workerThread3, &QThread::quit);
    connect(workerObject3, &myworker::doneProcess, workerObject3, &myworker::deleteLater);
    connect(workerObject3, &myworker::showResults, this, &Widget::handleResults);
    connect(workerThread3, &QThread::finished, workerObject3, &myworker::deleteLater);
    workerThread->start();
    workerThread2->start();
    workerThread3->start();
    */


    // 线程池与 QRunnable
    myprocess* process = new myprocess;
    myprocess* process2 = new myprocess;
    myprocess* process3 = new myprocess;
    myprocess* process4 = new myprocess;
    QThreadPool::globalInstance()->start(process);
    QThreadPool::globalInstance()->start(process2);
    QThreadPool::globalInstance()->start(process3);
    QThreadPool::globalInstance()->start(process4);
    qDebug() << QThreadPool::globalInstance()->activeThreadCount();
    this->thread()->sleep(3);
    qDebug() << QThreadPool::globalInstance()->activeThreadCount();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mySlot()
{
    static int count = 0;
    count++;
    ui->labDemo->setText(tr("%1").arg(count));
    qDebug() << "Done!" << QThread::currentThreadId();
}

void Widget::handleResults(int res)
{
    qDebug() << "Handle results" << res;
}