#include "FilterManagerBackend.h"
#include "FilterCreator.h"
#include <QDebug>
#include <QMap>
#include <QSet>
#include <QList>

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
    qDebug() << "UPDATE ALL FILTERS";

    QSet<int> updatedFilters;
    QList<int> nonUpdatedFilters = m_filters.keys();

    while(nonUpdatedFilters.count() > 0){
        QMutableListIterator<int> mainFilterIterator(nonUpdatedFilters);
        while(mainFilterIterator.hasNext()){
            int curFilter = mainFilterIterator.next();
            bool isEndPoint = true;

            QList<Connection> inConnections = m_inConnections.values(curFilter);
            QListIterator<Connection> inConIter(inConnections);
            while(inConIter.hasNext() && isEndPoint){
                Connection inCon = inConIter.next();
                isEndPoint = isEndPoint && updatedFilters.contains(inCon.targetFilter);
            }

            if(isEndPoint){
                AbstractFilter * filterPtr = m_filters.value(curFilter, NULL);
                if(filterPtr){
                    filterPtr->update();

                    QList<Connection> outConnections = m_outConnections.values(curFilter);
                    QListIterator<Connection> outConIter(outConnections);
                    while(outConIter.hasNext() ){
                        Connection outCon = outConIter.next();
                        AbstractFilter * targetPtr = m_filters.value(outCon.targetFilter, NULL);
                        if(targetPtr)
                            targetPtr->setInSlot(outCon.targetSlot, filterPtr->outSlot(outCon.currentSlot));
                    }

                }
                mainFilterIterator.remove();
                updatedFilters.insert(curFilter);
            }
        }
    }
}
