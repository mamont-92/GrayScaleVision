#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include "Core/FilterManagerBackend.h"
#include "Core/FilterManagerBackendGate.h"
//#include "Core/RasterImageProvider.h"
#include "Core/GlobalContext.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qmlRegisterType<FilterManagerBackendGate>("grayscalevision.core", 1, 0, "FilterManagerBackend");
    engine.addImageProvider(QLatin1String("rasterizer"), GlobalContext::instance().imageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    return app.exec();
}
