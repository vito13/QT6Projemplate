#pragma once

#include <QObject>
#include <QDebug>
#include <QMutex>

class myworker : public QObject
{
    Q_OBJECT

public:
    explicit myworker(QMutex *mutex);
    int* myInputNumber;
    QMutex* myMutex;
signals:
    void showResults(int res);
    void doneProcess();
public slots:
    void process();
};
