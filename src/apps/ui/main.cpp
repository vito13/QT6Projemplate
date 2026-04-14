#include "mylogin.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mylogin w;
    w.show();
    return a.exec();
}
