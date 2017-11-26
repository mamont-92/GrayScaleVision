#include "FilterManagerBackend.h"
#include <QDebug>
#include <QMap>

FilterManagerBackend::FilterManagerBackend(QObject *parent) : QObject(parent)
{
    qDebug() << "constructor";
}

void FilterManagerBackend::addFilter(int num, QString type)
{
    AbstractFilter * ptr = FilterCreator::create(type);
    qDebug() << "add filter: " << num << "  " << type << " " << ptr;
    m_filters.insert(num, ptr);
    qDebug() << "size: " << FilterCreator::filtersInfo().size();
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

QVariant FilterManagerBackend::filterCreationTemplate()
{
    /*QVariantMap resultObject;

    QVariantMap inverisonObject;
    QVariantMap addWeightedObject;

    inverisonObject.insert("inConnectors", 1);
    inverisonObject.insert("outConnectors", 1);

    addWeightedObject.insert("inConnectors", 2);
    addWeightedObject.insert("outConnectors", 1);

    resultObject.insert("inversion", QVariant::fromValue(inverisonObject));
    resultObject.insert("add weighted", QVariant::fromValue(addWeightedObject));

    return QVariant::fromValue(resultObject);*/

    QVariantMap resultMap;

    FilterInfoIterator iter(FilterCreator::filtersInfo());
    while (iter.hasNext()) {
        iter.next();
        QVariantMap currentFilterMap;
        currentFilterMap.insert("outConnectors", iter.value().outputs);
        currentFilterMap.insert("inConnectors", iter.value().inputs);
        resultMap.insert(iter.key(), QVariant::fromValue(currentFilterMap));
    }

    return QVariant::fromValue(resultMap);
}
