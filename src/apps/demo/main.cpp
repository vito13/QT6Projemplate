#include <QApplication>
#include "mywidget.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDIR>
#include <QQuickView>
#include <QProcessEnvironment>
#include <QTimer>
#include <QDateTime>
#include <QObject>
#include "myclock.h"

int testDLLFunctions(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MyWidget w;   // 从 DLL 创建控件
	w.show();
	showSum(5, 7);                  // 弹出消息框显示结果
	showMessage("Hello from DLL!"); // 弹出消息框显示自定义文本
	return app.exec();
}


int quickEngineTest(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.addImportPath("C:/Qt/6.10.2/msvc2022_64/qml");
	engine.load(QUrl(QStringLiteral("qrc:/qmls/scripttut.qml")));
	return app.exec();
}

int quickEngineClockTest(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.addImportPath("C:/Qt/6.10.2/msvc2022_64/qml");
	engine.load(QUrl(QStringLiteral("qrc:/qmls/clock.qml")));
	
	if (engine.rootObjects().isEmpty())
        return -1;

   	QObject *root = engine.rootObjects().first();
	// 创建 MyClock 实例，并将其作为 "backend" 属性暴露给 QML
	MyClock c;
	root->setProperty("backend", QVariant::fromValue(&c));

    // QTimer *timer = new QTimer(&app);
    // QObject::connect(timer, &QTimer::timeout, [=]() {
    //     QString currTime = QDateTime::currentDateTime()
    //                            .toString("HH:mm:ss");

    //     root->setProperty("currTime", currTime);
    // });

    // timer->start(100); // 100 ms

	return app.exec();
}

int QuickViewTest(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	QQuickView viewer;
	viewer.setResizeMode(QQuickView::SizeRootObjectToView);
	viewer.setSource(QUrl("qrc:/qmls/component.qml"));
	viewer.show();
	return app.exec();
}



int main(int argc, char *argv[])
{

	return
		// quickEngineClockTest(argc, argv);
		// QuickViewTest(argc, argv); // 显示为白
		quickEngineTest(argc, argv);
		// testDLLFunctions(argc, argv);
	
	
	
}