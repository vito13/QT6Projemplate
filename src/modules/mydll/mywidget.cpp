#include "mywidget.h"
#include <QMessageBox>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("Hello, MyWidget!", this);
    button = new QPushButton("Click Me", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &MyWidget::onButtonClicked);
}

void MyWidget::onButtonClicked()
{
    label->setText("Button Clicked!");
}

// ------------------ DLL 导出函数实现 ------------------
void showSum(int a, int b)
{
    QString text = QString("Sum: %1 + %2 = %3").arg(a).arg(b).arg(a + b);
    QMessageBox::information(nullptr, "DLL Test", text);
}

void showMessage(const char* msg)
{
    QString text(msg);
    QMessageBox::information(nullptr, "DLL Message", text);
}