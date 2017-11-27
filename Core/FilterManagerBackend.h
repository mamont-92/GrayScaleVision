#ifndef FilterManagerBackend_H
#define FilterManagerBackend_H

#include <QObject>
#include <QtCore>
#include <QHash>
#include <QList>
#include <QVector>
#include <QPair>
#include <QVariant>

#include "AbstractFilter.h"
#include "FilterCreator.h"

struct Connection
{
    int outFilter;
    int outConnector;
    int inFilter;
    int inConnector;

    Connection(int _outFilter, int _outConnector,int _inFilter, int _inConnector):
        outFilter(_outFilter), outConnector(_outConnector), inFilter(_inFilter), inConnector(_inConnector) {}
};

class FilterManagerBackend : public QObject
{
    Q_OBJECT

public:
    explicit FilterManagerBackend(QObject *parent = nullptr);

    Q_INVOKABLE void addFilter(int num, QString type);
    Q_INVOKABLE void removeFilter(int num);
    Q_INVOKABLE void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);
    Q_INVOKABLE QVariant filterCreationTemplate();

    void updateAllFilters();
private:
    QList<Connection> m_connections;
    QHash<int, AbstractFilter * > m_filters;
};

#endif // FilterManagerBackend_H
