#include "FilterManagerBackend.h"
#include <QDebug>
#include <QMap>
#include <QSet>

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
    updateAllFilters();
}

void FilterManagerBackend::removeFilter(int num) // TO DO :  add removing filter connections
{
    qDebug() << "remove filter: " << num;
    AbstractFilter * ptr  = m_filters.value(num, NULL);
    m_filters.remove(num);
    if(ptr)
        delete ptr;
    updateAllFilters();
}

void FilterManagerBackend::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    qDebug() << "connect filters: " << filterOut << "  " << filterIn;
    m_outConnections.insertMulti(filterOut, Connection(filterIn, connectorIn, connectorOut));
    m_inConnections.insertMulti(filterIn,Connection(filterOut,connectorOut, connectorIn));
    updateAllFilters();
}

QVariant FilterManagerBackend::filterCreationTemplate()
{
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

void FilterManagerBackend::updateAllFilters()
{
    qDebug() << "update all filters";

    QSet<int> nonUpdatedFilters = QSet<int>::fromList(m_filters.keys()), updatedFilters;
    // " nonUpdatedFilters" set is useless, need to operate with list iter

    while(nonUpdatedFilters.count() > 0){
        QMutableSetIterator<int> iter(nonUpdatedFilters);
        while(iter.hasNext()){
            int curFilter = iter.next();

            QMultiHash<int, Connection>::iterator i = m_inConnections.find(curFilter);
            bool isEndPoint = true;
            while (i != m_inConnections.end() && i.key() == curFilter) {
                isEndPoint = isEndPoint && updatedFilters.contains(i.value().targetFilter);
                ++i;
            }

            if(isEndPoint){
                AbstractFilter * filterPtr = m_filters.value(curFilter, NULL);
                if(filterPtr){
                    filterPtr->update();

                    QMultiHash<int, Connection>::iterator i = m_outConnections.find(curFilter);
                    while (i != m_outConnections.end() && i.key() == curFilter) {
                        AbstractFilter * targetFilterPtr = m_filters.value(i.value().targetFilter, NULL);
                        if(targetFilterPtr){
                            targetFilterPtr->setInSlot(i.value().targetSlot, filterPtr->outSlot(i.value().currentSlot));
                        ++i;
                        }
                    }

                }
                nonUpdatedFilters.remove(curFilter);
                updatedFilters.insert(curFilter);
                nonUpdatedFilters.remove(curFilter);
            }

        }
    }





}
