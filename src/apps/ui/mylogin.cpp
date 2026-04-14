#include "mylogin.h"
#include "ui_mylogin.h"
#include <QMessageBox>
#include "myrect.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QEventTransition>

mylogin::mylogin(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::mylogin)
{
    ui->setupUi(this);
    myrect* mc = new myrect(this);
    connect(this, &mylogin::doNow, mc, &myrect::doSomething);

    
QStateMachine *machine = new QStateMachine(this);
QState *s1 = new QState();
QState *s2 = new QState();


s1->assignProperty(ui->stateLabel, "text", "Current state: 1");
s1->assignProperty(ui->pushButton, "geometry", QRect(50, 200,
100, 50));
s2->assignProperty(ui->stateLabel, "text", "Current state: 2");
s2->assignProperty(ui->pushButton, "geometry", QRect(200, 50,
140, 100));

QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton, "geometry");
animation->setEasingCurve(QEasingCurve::OutBounce);
QEventTransition *t1 = new QEventTransition(ui->changeState, QEvent::MouseButtonPress);
t1->setTargetState(s2);
t1->addAnimation(animation);
s1->addTransition(t1);
QEventTransition *t2 = new QEventTransition(ui->changeState, QEvent::MouseButtonPress);
t2->setTargetState(s1);
t2->addAnimation(animation);
s2->addTransition(t2);

machine->addState(s1);
machine->addState(s2);
machine->setInitialState(s1);
machine->start();

}

mylogin::~mylogin()
{
    delete ui;
}

void mylogin::on_loginButton_clicked() {
    emit doNow();
    
}
