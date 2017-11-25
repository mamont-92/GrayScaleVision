#include "FilterManagerBackend.h"
#include <QDebug>

FilterManagerBackend::FilterManagerBackend(QObject *parent) : QObject(parent)
{
    qDebug() << "constructor";
}

void FilterManagerBackend::addFilter(int num, QString type)
{
    qDebug() << "add filter: " << num << "  " << type;
    m_filters.insert(num, Filter(type));
}

void FilterManagerBackend::removeFilter(int num)
{
    qDebug() << "remove filter: " << num;
    m_filters.remove(num);
}

void FilterManagerBackend::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    qDebug() << "connect filters: " << filterOut << "  " << filterIn;
    m_connections.append(Connection(filterOut, connectorOut, filterIn, connectorIn));
}
