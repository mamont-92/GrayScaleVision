#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Core/FilterProcessorGate.h"
#include "Core/GlobalContext.h"
#include "FileIO/JsonFileIO.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<FilterProcessorGate>("grayscalevision.core", 1, 0, "FilterProcessor");
    qmlRegisterType<JsonFileIO>("grayscalevision.fileIO.json", 1, 0, "JsonFileIO");
    engine.addImageProvider(QLatin1String("rasterizer"), GlobalContext::instance().imageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    return app.exec();
}
