#ifndef FilterManagerBackend_H
#define FilterManagerBackend_H

#include <QObject>
#include <QtCore>

class FilterManagerBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

public:
    explicit FilterManagerBackend(QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

    void addFilter(int num, QString type);
    void deleteFilter(int num);
    void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);


signals:
    void userNameChanged();

private:
    QString m_userName;
};

#endif // FilterManagerBackend_H
