#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <QObject>
#include <QTimer>

class MyClock : public QObject
{
    Q_OBJECT

public:
    explicit MyClock(QObject *parent = NULL);

signals:
    void updated(QString time);

private:
    QTimer *timer;

private slots:
    void updateTime();
};

#endif // MYCLOCK_H
