#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // 需要包含这个头文件
#include <QUrl>


#include "../core/service/LoginHandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 1. 创建LoginHandler实例
    LoginHandler loginHandler;

    // 2. 将loginHandler实例暴露给QML，命名为"loginHandler"
    engine.rootContext()->setContextProperty("loginHandler", &loginHandler);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}