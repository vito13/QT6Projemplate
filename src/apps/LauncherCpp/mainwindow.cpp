#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "LauncherItemWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    loadData();
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget;
    setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout(central);



    list = new QListWidget;
    pageContainer = new QWidget;

    layout->addWidget(list);

    layout->addWidget(pageContainer, 1);
    auto backBtn = new QPushButton("Back");
    layout->addWidget(backBtn);



    connect(backBtn, &QPushButton::clicked, this, &MainWindow::goBack);
}

void MainWindow::loadData()
{
    model = {
        {"Example 1", "1 demo page", QUrl("qrc:/qmlsnowin/R1.qml")},
        {"Example 2", "2 demo page", QUrl("qrc:/qmlsnowin/R2.qml")},
        {"Example 3", "3 demo page", QUrl("qrc:/qmlsnowin/R3.qml")},
    };

    for (int i = 0; i < model.size(); ++i)
    {
        const auto &item = model[i];
        LauncherItemWidget* widget = new LauncherItemWidget;
        widget->setName(item.name);
        widget->setDescription(item.desc);
        widget->setUrl(item.url);

        QListWidgetItem* lwItem = new QListWidgetItem(list);
        lwItem->setSizeHint(QSize(200, 90));
        list->addItem(lwItem);
        list->setItemWidget(lwItem, widget);

        connect(widget, &LauncherItemWidget::clicked, this, [this, url = item.url]() {
            openExample(url);
        });
    }
}

void MainWindow::openExample(const QUrl &url)
{
    ExamplePage* page = new ExamplePage(url, this);

    pageStack.push(page);

    page->setWindowFlags(Qt::SubWindow);
    page->resize(list->size());
    page->show();

    list->setVisible(false);
}

void MainWindow::goBack()
{
    if (pageStack.isEmpty())
        return;

    ExamplePage* page = pageStack.pop();
    page->deleteLater();

    if (pageStack.isEmpty())
        list->setVisible(true);
}
