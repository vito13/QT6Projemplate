#include <QApplication>
#include "mywidget.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDIR>

int testDLLFunctions(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MyWidget w;   // 从 DLL 创建控件
	w.show();
	showSum(5, 7);                  // 弹出消息框显示结果
	showMessage("Hello from DLL!"); // 弹出消息框显示自定义文本
	return app.exec();
}


int quickTest(int argc, char* argv[])
{
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	const QUrl url("qrc:/qmls/alarms.qml");

	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreated,
		&app,
		[url](QObject* obj, const QUrl& objUrl)
		{
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);

	engine.load(url);
	return app.exec();
}

int main(int argc, char *argv[])
{
	
	return
		quickTest(argc, argv);
		//testDLLFunctions(argc, argv);
	
	
	
}