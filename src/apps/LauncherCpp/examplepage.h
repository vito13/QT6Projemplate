#pragma once

#include <QQuickWidget>
#include <QWidget>
#include <QUrl>

class ExamplePage : public QWidget
{
    Q_OBJECT

public:
    explicit ExamplePage(const QUrl &url, QWidget *parent = NULL);

private:
    QQuickWidget *view;
};
