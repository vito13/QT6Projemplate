#pragma once

#include <QRunnable>
#include <QDebug>

class myprocess: public QRunnable
{
public:
    myprocess();
    void run() override;
};
