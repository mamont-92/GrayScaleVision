#ifndef FilterManagerBackend_H
#define FilterManagerBackend_H

#include <QObject>
#include <QtCore>
#include <QHash>
#include <QMultiHash>
#include <QVariant>

#include "AbstractFilter.h"

struct Connection
{
    int targetFilter;
    int targetSlot;
    int currentSlot;

    Connection(int _targetFilter, int _targetSlot,int _currentSlot):
        targetFilter(_targetFilter), targetSlot(_targetSlot), currentSlot(_currentSlot) {}
};

class FilterManagerBackend{
public:
    FilterManagerBackend();

    void addFilter(int num, QString type);
    void removeFilter(int num);
    void connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn);
    QVariant filterCreationTemplate();

    void updateAllFilters();
private:
    QMultiHash<int, Connection> m_outConnections, m_inConnections;
    QHash<int, AbstractFilter * > m_filters;
};

#endif // FilterManagerBackend_H
