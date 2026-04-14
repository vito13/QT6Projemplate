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
#include "studentmodel.h"
#include <QQmlContext>

int quickEngineTest(int argc, char* argv[])
{  
	QGuiApplication app(argc, argv);

	StudentModel model;
    if (!model.initDB("D:/hhhw/book/Qt6_Cplusplus-DevelopmentTutorialCode/Source/Chap09_Database/demodb.db3")) {
        qWarning("数据库初始化失败！");
        return -1;
    }

	QQmlApplicationEngine engine;
	engine.addImportPath("C:/Qt/6.10.2/msvc2022_64/qml");
	engine.rootContext()->setContextProperty("studentModel", &model);
	engine.load(QUrl(QStringLiteral("qrc:/qmls/quicktableview.qml")));
	return app.exec();
}


int main(int argc, char *argv[])
{
	return quickEngineTest(argc, argv);
}