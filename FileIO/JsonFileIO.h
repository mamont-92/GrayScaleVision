#ifndef JSONFILEIO_H
#define JSONFILEIO_H

#include <QJsonArray>
#include <QVariant>

class JsonFileIO : public QObject
{
    Q_OBJECT
public:
    explicit JsonFileIO(QObject *parent = nullptr);
    Q_INVOKABLE QVariant readJSONFromFile(QString fileName);
    Q_INVOKABLE bool writeJSONToFile(QString fileName, QVariant obj);

};

#endif // JSONFILEIO_H
