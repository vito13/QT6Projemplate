#include "mylogin.h"

#include <QEventTransition>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainterPath>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QStateMachine>
#include <QtSvg/QSvgGenerator>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include "myrect.h"
#include "ui_mylogin.h"

mylogin::mylogin(QDialog* parent) : QDialog(parent), ui(new Ui::mylogin)
{
    ui->setupUi(this);
    myrect* mc = new myrect(this);
    connect(this, &mylogin::doNow, mc, &myrect::doSomething);
    QStateMachine* machine = new QStateMachine(this);
    QState* s1 = new QState();
    QState* s2 = new QState();

    s1->assignProperty(ui->stateLabel, "text", "Current state: 1");
    s1->assignProperty(ui->pushButton, "geometry", QRect(50, 200, 100, 50));
    s2->assignProperty(ui->stateLabel, "text", "Current state: 2");
    s2->assignProperty(ui->pushButton, "geometry", QRect(200, 50, 140, 100));

    QPropertyAnimation* animation = new QPropertyAnimation(ui->pushButton, "geometry");
    animation->setEasingCurve(QEasingCurve::OutBounce);
    QEventTransition* t1 = new QEventTransition(ui->changeState, QEvent::MouseButtonPress);
    t1->setTargetState(s2);
    t1->addAnimation(animation);
    s1->addTransition(t1);
    QEventTransition* t2 = new QEventTransition(ui->changeState, QEvent::MouseButtonPress);
    t2->setTargetState(s1);
    t2->addAnimation(animation);
    s2->addTransition(t2);

    machine->addState(s1);
    machine->addState(s2);
    machine->setInitialState(s1);
    machine->start();




    
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&mylogin::paintAll));
    timer->start(1000);

    image = QImage(this->size(), QImage::Format_RGB32);
    image.fill(Qt::white);

}

mylogin::~mylogin()
{
    delete ui;
}

void mylogin::on_loginButton_clicked()
{
    // emit doNow();
   
}

void mylogin::paintEvent(QPaintEvent* event)
{
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), image, image.rect());


}

void mylogin::paintAll()
{
   
    static const QPoint hourHand[3] = {QPoint(4, 4), QPoint(-4, 4), QPoint(0, -40)};
    static const QPoint minuteHand[3] = {QPoint(4, 4), QPoint(-4, 4), QPoint(0, -70)};
    static const QPoint secondHand[3] = {QPoint(2, 2), QPoint(-2, 2), QPoint(0, -90)};
    int side = qMin(width(), height());
    
    QPainter painter(&image);
    painter.fillRect(this->rect(), Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 250.0, side / 250.0);
    for (int i = 0; i < 60; ++i)
    {
        if ((i % 5) != 0)
            painter.drawLine(95, 0, 96, 0);
        else
            painter.drawLine(86, 0, 96, 0);
        painter.rotate(6.0);
        
    }
    QTime time = QTime::currentTime();
    // Draw hour hand
    painter.save();
    painter.rotate((time.hour() * 360) / 12);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
    painter.save();
    painter.rotate((time.minute() * 360) / 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
    painter.save();
    painter.rotate((time.second() * 360) / 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
    this->update();
}