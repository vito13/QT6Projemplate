#include "myclock.h"
#include <QDateTime>

MyClock::MyClock(QObject *parent)
    : QObject(parent)
{
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout,
            this, &MyClock::updateTime);

    timer->start(1000); // 1000ms (1 second)
}

void MyClock::updateTime()
{
    QString currTime = QDateTime::currentDateTime()
                           .toString("HH:mm:ss");

    emit updated(currTime); // 触发所有连接的槽（slot），在 QML 里就是 Connections 的 onUpdated
}