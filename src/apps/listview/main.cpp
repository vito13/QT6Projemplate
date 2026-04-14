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

int quickEngineTest(int argc, char* argv[])
{  
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.addImportPath("C:/Qt/6.10.2/msvc2022_64/qml");
	
	engine.load(QUrl(QStringLiteral("qrc:/qmls/listview.qml")));
	return app.exec();
}


int main(int argc, char *argv[])
{
	return quickEngineTest(argc, argv);
}