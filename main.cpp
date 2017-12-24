#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Core/FilterManagerBackendGate.h"
#include "Core/GlobalContext.h"
#include "FileIO/JsonFileIO.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<FilterManagerBackendGate>("grayscalevision.core", 1, 0, "FilterManagerBackend");
    qmlRegisterType<JsonFileIO>("grayscalevision.fileIO.json", 1, 0, "JsonFileIO");
    engine.addImageProvider(QLatin1String("rasterizer"), GlobalContext::instance().imageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    return app.exec();
}
