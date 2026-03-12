#include <QApplication>
#include "mywidget.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDIR>
#include <QQuickView>
#include <QProcessEnvironment>

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
	engine.load(QUrl(QStringLiteral("qrc:/qmls/component.qml")));
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
		// QuickViewTest(argc, argv); // 显示为白
		// quickEngineTest(argc, argv);
		testDLLFunctions(argc, argv);
	
	
	
}