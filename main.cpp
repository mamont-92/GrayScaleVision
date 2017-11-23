#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Core/FilterManagerBackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<FilterManagerBackend>("grayscalevision.core", 1, 0, "FilterManagerBackend");
    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    return app.exec();
}
