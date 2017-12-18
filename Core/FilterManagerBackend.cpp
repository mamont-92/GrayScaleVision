#include "FilterManagerBackend.h"
#include "FilterCreator.h"
#include <QDebug>
#include <QMap>
#include <QSet>
#include <QList>
#include "ImageData/ImageDataRasterizer.h"
#include <QMutexLocker>

FilterManagerBackend::FilterManagerBackend(QObject *parent) :QObject(parent)
{
}

void FilterManagerBackend::addFilter(int num, QString type)
{
    AbstractFilter * ptr = FilterCreator::create(type);
    m_filters.insert(num, ptr);
    updateAllFilters();
}

void FilterManagerBackend::removeFilter(int num) // TO DO :  add removing filter connections
{
    removeAllConnections(num);
    AbstractFilter * ptr  = m_filters.value(num, NULL);
    m_filters.remove(num);
    if(ptr)
        delete ptr;
    updateAllFilters();
}

void FilterManagerBackend::removeAllConnections(int filterNumber)
{
    m_outConnections.remove(filterNumber);
    m_inConnections.remove(filterNumber);

    QMutableHashIterator<int, Connection> inConIter(m_inConnections);
    while(inConIter.hasNext()){
        inConIter.next();
        if(inConIter.value().targetFilter == filterNumber){
            AbstractFilter * filterPtr = m_filters.value(inConIter.key(), NULL);
            if(filterPtr)
                filterPtr->clearInSlot(inConIter.value().currentSlot);
            inConIter.remove();
        }
    }


    QMutableHashIterator<int, Connection> outConIter(m_outConnections);
    while(outConIter.hasNext()){
        outConIter.next();
        if(outConIter.value().targetFilter == filterNumber){
            outConIter.remove();
        }
    }
}

void FilterManagerBackend::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    //TO DO: add removing conection for "filterIn" at slot "connectorIn"
    removeConnectionsForFilterInSlot(filterIn, connectorIn);
    m_outConnections.insertMulti(filterOut, Connection(filterIn, connectorIn, connectorOut));
    m_inConnections.insertMulti(filterIn,Connection(filterOut,connectorOut, connectorIn));

    updateAllFilters();
}

void FilterManagerBackend::removeConnectionsForFilterInSlot(int filterNumber, int slot)
{
    AbstractFilter * filterPtr = m_filters.value(filterNumber, NULL);
    if(filterPtr)
        filterPtr->clearInSlot(slot);

    QMutableHashIterator<int, Connection> inConIter(m_inConnections);
    while(inConIter.hasNext()){
        inConIter.next();
        if((inConIter.key() == filterNumber) && (inConIter.value().currentSlot == slot)){
            inConIter.remove();
        }
    }


    QMutableHashIterator<int, Connection> outConIter(m_outConnections);
    while(outConIter.hasNext()){
        outConIter.next();
        if((outConIter.value().targetFilter == filterNumber) && (outConIter.value().targetSlot == slot) ){
            outConIter.remove();
        }
    }
}

void FilterManagerBackend::setParameterValueForFilter(int filterNumber, QString paramName, QVariant value)
{
    AbstractFilter * filterPtr = m_filters.value(filterNumber, NULL);
    if(filterPtr)
        filterPtr->setParameter(paramName, value);
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

QVariant FilterManagerBackend::filterParamsInfo(int filterNumber)
{
    AbstractFilter * filterPtr = m_filters.value(filterNumber, NULL);
    if(filterPtr)
        return filterPtr->allParametersInfo();
    return QVariant();
}

void FilterManagerBackend::updateAllFilters()
{
    m_imageMutex.lock();
    m_images.clear();
    m_imageMutex.unlock();

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

                    QImage img = ImageDataRasterizer::ImageDataToQImage(filterPtr->outSlot((qint8)0));
                    m_imageMutex.lock();
                    m_images.insert(curFilter, img);
                    m_imageMutex.unlock();
                    emit imageRastered(curFilter);

                    QList<Connection> outConnections = m_outConnections.values(curFilter);
                    QListIterator<Connection> outConIter(outConnections);
                    while(outConIter.hasNext() ){
                        Connection outCon = outConIter.next();
                        AbstractFilter * targetPtr = m_filters.value(outCon.targetFilter, NULL);
                        if(targetPtr){


                            targetPtr->setInSlot((qint8)outCon.targetSlot, filterPtr->outSlot(outCon.currentSlot));
                            //targetPtr->setInSlot(outCon.targetSlot, filterPtr->outSlot(outCon.currentSlot));
                        }
                    }

                }
                mainFilterIterator.remove();
                updatedFilters.insert(curFilter);
            }
        }
    }
}

QImage FilterManagerBackend::images(int filterNumber)
{
    QMutexLocker locker(&m_imageMutex);
    return m_images.value(filterNumber, QImage());
}
