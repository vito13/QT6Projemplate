#include "examplepage.h"
#include <QVBoxLayout>

ExamplePage::ExamplePage(const QUrl &url, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    view = new QQuickWidget;
    view->setResizeMode(QQuickWidget::SizeViewToRootObject);
    view->setSource(url);

    layout->addWidget(view);
}
