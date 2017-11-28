#ifndef FilterManagerBackend_H
#define FilterManagerBackend_H

#include <QObject>
#include <QtCore>
#include <QHash>
#include <QMultiHash>
#include <QList>
#include <QVector>
#include <QPair>
#include <QVariant>


#include "AbstractFilter.h"
#include "FilterCreator.h"

struct Connection
{
    int targetFilter;
    int targetSlot;
    int currentSlot;

    Connection(int _targetFilter, int _targetSlot,int _currentSlot):
        targetFilter(_targetFilter), targetSlot(_targetSlot), currentSlot(_currentSlot) {}
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
    //QList<Connection> m_connections;
    QMultiHash<int, Connection> m_outConnections, m_inConnections;

    QHash<int, AbstractFilter * > m_filters;
};

#endif // FilterManagerBackend_H
