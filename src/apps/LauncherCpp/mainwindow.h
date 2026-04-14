#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QStack>

#include "examplepage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);

private:
    struct Item {
        QString name;
        QString desc;
        QUrl url;
    };

    QList<Item> model;

    QListWidget *list;
    QWidget *pageContainer;

    QStack<ExamplePage*> pageStack;

    void setupUI();
    void loadData();

    void openExample(const QUrl &url);
    void goBack();
};
