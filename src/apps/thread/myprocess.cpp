#include "myprocess.h"

myprocess::myprocess() {}

void myprocess::run()
{
    int myNumber = 0;
    for (int i = 0; i < 100000000; ++i)
    {
        myNumber += i;
    }
    qDebug() << myNumber;
}