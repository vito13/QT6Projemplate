#include "launcheritemwidget.h"
#include <QVBoxLayout>

LauncherItemWidget::LauncherItemWidget(QWidget *parent)
    : QWidget(parent)
{
    title = new QLabel(this);
    desc  = new QLabel(this);

    title->setStyleSheet("font-size:18px;");
    desc->setStyleSheet("color:#666; font-size:12px;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(desc);

    setStyleSheet("background:#ffffff; padding:10px;");
}

void LauncherItemWidget::setName(const QString &name)
{
    title->setText(name);
    this->setToolTip(name);
}

void LauncherItemWidget::setDescription(const QString &d)
{
    desc->setText(d);
    this->setToolTip(d);
}

void LauncherItemWidget::setUrl(const QUrl &url)
{
    m_url = url;
    this->setToolTip(m_url.toString());
}

void LauncherItemWidget::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

void LauncherItemWidget::enterEvent(QEnterEvent *)
{
    hovered = true;
    updateStyle();
    // printf("hovered\n");
}

void LauncherItemWidget::leaveEvent(QEvent *)
{
    hovered = false;
    updateStyle();
    // printf("left\n");
}

void LauncherItemWidget::updateStyle()
{
    setStyleSheet(hovered
        ? "background:#f0f0f0; padding:10px;"
        : "background:#ffffff; padding:10px;");
}
