#include "FilterManagerBackend.h"
#include <QDebug>

FilterManagerBackend::FilterManagerBackend(QObject *parent) : QObject(parent)
{
    qDebug() << "constructor";
}

void FilterManagerBackend::addFilter(int num, QString type)
{
    AbstractFilter * ptr = FilterCreator::create(type);
    qDebug() << "add filter: " << num << "  " << type << " " << ptr;
    m_filters.insert(num, ptr);
    qDebug() << "size: " << FilterCreator::filterFuncs().size();
}

void FilterManagerBackend::removeFilter(int num)
{
    qDebug() << "remove filter: " << num;
    m_filters.remove(num); // mem leak now
}

void FilterManagerBackend::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    qDebug() << "connect filters: " << filterOut << "  " << filterIn;
    m_connections.append(Connection(filterOut, connectorOut, filterIn, connectorIn));
}
