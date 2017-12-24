#include "JsonFileIO.h"
#include <QFile>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>
#include <QJsonObject>

JsonFileIO::JsonFileIO(QObject *parent) : QObject(parent)
{

}

QVariant JsonFileIO::readJSONFromFile(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        auto doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        return doc.toVariant();
    }
    return QVariant();
}
bool JsonFileIO::writeJSONToFile(QString fileName, QVariant obj)
{
    auto doc = QJsonDocument::fromVariant(obj.toMap());
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)){
        int bc = file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        return bc > 0;
    }
    return false;
}
