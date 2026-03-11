#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>

// DLL 导出宏
#ifdef _WIN32
  #ifdef MYDLL_BUILD
    #define MYDLL_BUILD __declspec(dllexport)
  #else
    #define MYDLL_BUILD __declspec(dllimport)
  #endif
#else
  #define MYDLL_BUILD
#endif

class MYDLL_BUILD MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

private:
    QLabel *label;
    QPushButton *button;

private slots:
    void onButtonClicked();
};

extern "C" {
    MYDLL_BUILD void showSum(int a, int b);        // 显示 a + b
    MYDLL_BUILD void showMessage(const char* msg); // 显示任意字符串
}