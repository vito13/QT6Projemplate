#include "myrect.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
myrect::myrect(QObject* parent) 
: QObject(parent) 
{

}
void myrect::doSomething() 
{
    QString *html = new QString;
    qDebug() << "Start";
    QNetworkAccessManager manager;
    QNetworkRequest req(QUrl("http://www.dustyfeet.com"));
    QNetworkReply* reply = manager.get(req);
    QObject::connect(reply, &QNetworkReply::readyRead,
        [reply, html]() {
            html->append(QString(reply->readAll()));
        });
    QObject::connect(reply, &QNetworkReply::downloadProgress,
        [reply](qint64 bytesReceived, qint64 bytesTotal) {
            qDebug() << "Progress: " << bytesReceived << "bytes /" << bytesTotal << "bytes";
    });
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        QMessageBox::information(NULL, "Hello", *html);
    });
}