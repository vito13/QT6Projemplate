#pragma once

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class LauncherItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LauncherItemWidget(QWidget *parent = nullptr);

    void setName(const QString &name);
    void setDescription(const QString &desc);
    void setUrl(const QUrl &url);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QLabel *title;
    QLabel *desc;

    QUrl m_url;
    bool hovered;

    void updateStyle();
};