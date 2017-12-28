#include "FilterProcessor.h"
#include "FilterCreator.h"
#include <QMap>
#include <QSet>
#include <QList>
#include "ImageData/ImageDataRasterizer.h"
#include <QMutexLocker>
#include <QStack>
#include <QtConcurrent>
#include <QFuture>


FilterProcessor::FilterProcessor(QObject *parent) :QObject(parent)
{
}

void FilterProcessor::addFilter(int num, QString type)
{
    AbstractFilter * ptr = FilterCreator::create(type);
    if(ptr){
        m_filters.insert(num, ptr);
        updateAllFilters();
        emit paramsChanged(FilterParams(num, ptr->allParametersInfo()));
    }
}

void FilterProcessor::removeFilter(int num) // TO DO :  add removing filter connections
{
    removeAllConnections(num);
    updateAllConnectionsForFilters();
    AbstractFilter * ptr  = m_filters.value(num, NULL);
    m_filters.remove(num);
    if(ptr)
        delete ptr;
    updateAllFilters();
}

void FilterProcessor::removeAllConnections(int filterNumber)
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

void FilterProcessor::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    //TO DO: add removing conection for "filterIn" at slot "connectorIn"
    removeConnectionsForFilterInSlot(filterIn, connectorIn);
    m_outConnections.insertMulti(filterOut, Connection(filterIn, connectorIn, connectorOut));
    m_inConnections.insertMulti(filterIn,Connection(filterOut,connectorOut, connectorIn));

    updateAllConnectionsForFilters();
    updateFromFilter(filterIn);
}

void FilterProcessor::removeConnectionsForFilterInSlot(int filterNumber, int slot)
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

void FilterProcessor::setParameterValueForFilter(int filterNumber, QString paramName, QVariant value)
{
    AbstractFilter * filterPtr = m_filters.value(filterNumber, NULL);
    if(filterPtr)
        filterPtr->setParameter(paramName, value);
    updateFromFilter(filterNumber);
}

QVariant FilterProcessor::availableFilters()
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

/*QVariant FilterProcessor::filterParamsInfo(int filterNumber)
{
    AbstractFilter * filterPtr = m_filters.value(filterNumber, NULL);
    if(filterPtr)
        return filterPtr->allParametersInfo();
    return QVariant();
}*/

QVariant FilterProcessor::availableRasterModes()
{
    return QVariant::fromValue(ImageDataRasterizer::availableRasterModes());
}

void FilterProcessor::updateAllFilters() // need add lopp detection
{
    QSet<int> needUpdateFilters = QSet<int>::fromList(m_filters.keys());
    updateFilterSet(needUpdateFilters);
}

void FilterProcessor::updateFromFilter(int number)
{
    QSet<int> needUpdateFilters;
    QStack<int> nextFilters;
    nextFilters.push(number);
    while(nextFilters.count()){
        int currFilter = nextFilters.pop();
        needUpdateFilters.insert(currFilter);
        auto connectionList = m_outConnections.values(currFilter);
        QListIterator<Connection> iter(connectionList);
        while (iter.hasNext()) {
            auto connection = iter.next();
            int nextFilterNumber = connection.targetFilter;
            if(!needUpdateFilters.contains(nextFilterNumber)){
                nextFilters.push(nextFilterNumber);
            }
        }
    }
    updateFilterSet(needUpdateFilters);
}

void FilterProcessor::updateFilterSet(QSet<int> filterSet)
{
    //QFuture<void> updateFuture = QtConcurrent::run([this, filterSet] () {

        QSet<int> updatedFilters = QSet<int>::fromList(m_filters.keys()).subtract(filterSet);
        QList<int> nonUpdatedFilters = QList<int>::fromSet(filterSet);

        while(nonUpdatedFilters.count() > 0){
            QMutableListIterator<int> mainFilterIterator(nonUpdatedFilters);
            while(mainFilterIterator.hasNext()){
                int curFilter = mainFilterIterator.next();
                bool isCompleteNode = true;

                QList<Connection> inConnections = m_inConnections.values(curFilter);
                QListIterator<Connection> inConIter(inConnections);
                while(inConIter.hasNext() && isCompleteNode){
                    Connection inCon = inConIter.next();
                    isCompleteNode = isCompleteNode && updatedFilters.contains(inCon.targetFilter);
                }

                if(isCompleteNode){
                    AbstractFilter * filterPtr = m_filters.value(curFilter, NULL);
                    if(filterPtr){
                        filterPtr->update();

                        QImage img = ImageDataRasterizer::ImageDataToQImage(filterPtr->outSlot((qint8)0), m_rasterMode);
                        setImageForFilter(curFilter, img);
                    }
                    mainFilterIterator.remove();
                    updatedFilters.insert(curFilter);
                }
            }
        }
    //});

    //m_updateWatcher.setFuture(updateFuture);
}

inline void FilterProcessor::setImageForFilter(int filterNumber, QImage img)
{
    m_imageMutex.lock();
    m_images.insert(filterNumber, img);
    m_imageMutex.unlock();
    emit imageRastered(filterNumber);
}

void FilterProcessor::updateAllConnectionsForFilters()
{
    QHashIterator<int, Connection> outConIter(m_outConnections);
    while(outConIter.hasNext()){
        outConIter.next();
        auto outFilterPtr = m_filters.value(outConIter.key(), NULL);
        auto inFilterPtr = m_filters.value(outConIter.value().targetFilter, NULL);

        if(outFilterPtr && inFilterPtr)
            inFilterPtr->setInSlot(outConIter.value().targetSlot, outFilterPtr->outSlot(outConIter.value().currentSlot));
    }
}

QImage FilterProcessor::images(int filterNumber)
{
    QMutexLocker locker(&m_imageMutex);
    return m_images.value(filterNumber, QImage());
}

void FilterProcessor::setRasterMode(QString mode)
{
    m_rasterMode = mode;
    rasterAllImages();
}

void FilterProcessor::rasterAllImages()
{
    QHashIterator<int, AbstractFilter*> iter(m_filters);
    while(iter.hasNext()){
        iter.next();
        auto filterPtr = iter.value();
        if(filterPtr){
            QImage img = ImageDataRasterizer::ImageDataToQImage(filterPtr->outSlot((qint8)0), m_rasterMode);
            setImageForFilter(iter.key(), img);
        }
    }
}
