#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDIR>
#include <QQuickView>
#include <QProcessEnvironment>
#include <QTimer>
#include <QDateTime>
#include <QObject>
#include <QQmlContext>
#include <QQuickWidget>

int quickEngineTest(int argc, char* argv[])
{  
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.addImportPath("C:/Qt/6.10.2/msvc2022_64/qml");
	engine.load(QUrl(QStringLiteral("qrc:/qmls/modelview.qml")));
	return app.exec();
}


int QuickViewTest(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QQuickWidget *view = new QQuickWidget;
	view->setSource(QUrl::fromLocalFile("D:/hhhw/test/QT6Projemplate/res/qmls/modelview.qml"));
	view->show();
	return app.exec();
}
int main(int argc, char *argv[])
{
	return 
	QuickViewTest(argc, argv);
	// quickEngineTest(argc, argv);
}