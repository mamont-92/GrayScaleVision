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
#include "Commands.h"
#include "CommandCallBackAcceptor.h"
#include "Core/ImageData/imagedata.h"
#include <QDebug>
#include <complex>

using namespace FilterProcessorComands;

FilterProcessor::FilterProcessor(QObject *parent) :QObject(parent)
{
    FilterProcessorComands::AddFilterCallBack addFilterFunc = [this] (const AddFilter & command) {
        this->addFilter(command.filterNumber(), command.name());
    };
    FilterProcessorComands::RemoveFilterCallBack removeFilterFunc = [this] (const RemoveFilter & command) {
        this->removeFilter(command.filterNumber());
    };
    FilterProcessorComands::ConnectFiltersCallBack connectFiltersFunc = [this] (const ConnectFilters & command) {
        this->connectFilters(command.filterOut(), command.connectorOut(), command.filterIn(), command.connectorIn());
    };
    FilterProcessorComands::SetParameterForFilterCallBack setParameterForFilterFunc = [this] (const SetParameterForFilter & command) {
        this->setParameterValueForFilter(command.filterNumber(), command.paramName(), command.value());
    };
    FilterProcessorComands::SetRasterModeCallBack setRasterModeFunc = [this] (const SetRasterMode & command) {
        this->setRasterMode(command.mode());
    };
    m_commandAcceptor = new CommandCallBackAcceptor(addFilterFunc, removeFilterFunc, connectFiltersFunc, setParameterForFilterFunc, setRasterModeFunc);

    connect(&m_updateWatcher, &QFutureWatcher<void>::finished, [this](){
        if(m_commandQueue.count())
            runFilterUpdating();
    });

    /*ImageData<double> dData(10,10);
    ImageData<float> fData(20,35);
    ImageData<std::complex<float> > cfData(45,65);
    qDebug() << "olol" << dData.pixelCount() << fData.height() << cfData.rect();*/
    //qDebug() << "ololo" << cData.getCVType() << fData.getCVType() << usData.getCVType() << CV_32FC1 << CV_16UC1;
}

FilterProcessor::~FilterProcessor()
{
    delete m_commandAcceptor;
}

void FilterProcessor::execute(FilterProcessorComands::ICommand * command)
{
    if(command){
        m_commandQueue.enqueue(command);
        runFilterUpdating();
    }
}

void FilterProcessor::runFilterUpdating()
{
    if(!m_updateWatcher.isRunning()){
        performAccumulatedCommands();
        QFuture<void> updateFuture = QtConcurrent::run([this] () {

            updateNonActualFilters();
            rasterNonActualImages();
        });
        m_updateWatcher.setFuture(updateFuture);
    }
}

void FilterProcessor::performAccumulatedCommands()
{
    m_needUpdatingFilters.clear();
    m_needRastingFilters.clear();

    while(m_commandQueue.count()){
        auto command = m_commandQueue.dequeue();
        command->accept(m_commandAcceptor);
        delete command;
    }
}

void FilterProcessor::addFilter(int num, QString type)
{
    AbstractFilter * ptr = FilterCreator::create(type);
    if(ptr){
        m_filters.insert(num, ptr);
        m_needUpdatingFilters.insert(num);
        emit paramsChanged(FilterParams(num, ptr->allParametersInfo()));
    }
}

void FilterProcessor::removeFilter(int num) // TO DO :  add removing filter connections
{
    m_needUpdatingFilters = m_needUpdatingFilters.unite(allDependentNodes(num));
    removeAllConnections(num);
    updateAllConnectionsForFilters();
    AbstractFilter * ptr  = m_filters.value(num, NULL);
    m_filters.remove(num);
    if(ptr)
        delete ptr;
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
    QSet<int> beforeReconnecting = allDependentNodes(filterIn);

    removeConnectionsForFilterInSlot(filterIn, connectorIn);

    QSet<int> afterReconnecting = allDependentNodes(filterIn);
    m_needUpdatingFilters = m_needUpdatingFilters.unite(beforeReconnecting.unite(afterReconnecting));

    m_outConnections.insertMulti(filterOut, Connection(filterIn, connectorIn, connectorOut));
    m_inConnections.insertMulti(filterIn,Connection(filterOut,connectorOut, connectorIn));

    updateAllConnectionsForFilters(); // need replace all for concrete target filters
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
    m_needUpdatingFilters = m_needUpdatingFilters.unite(allDependentNodes(filterNumber));
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

QVariant FilterProcessor::availableRasterModes()
{
    return QVariant::fromValue(ImageDataRasterizer::availableRasterModes());
}

void FilterProcessor::updateNonActualFilters() // need add lopp detection
{
    updateFilterSet(m_needUpdatingFilters);
}

QSet<int> FilterProcessor::allDependentNodes(int startNode)
{
    QSet<int> dpendentNodes;
    QStack<int> nextFilters;
    nextFilters.push(startNode);
    while(nextFilters.count()){
        int currFilter = nextFilters.pop();
        dpendentNodes.insert(currFilter);
        auto connectionList = m_outConnections.values(currFilter);
        QListIterator<Connection> iter(connectionList);
        while (iter.hasNext()) {
            auto connection = iter.next();
            int nextFilterNumber = connection.targetFilter;
            if(!dpendentNodes.contains(nextFilterNumber)){
                nextFilters.push(nextFilterNumber);
            }
        }
    }
    return  dpendentNodes;
}

void FilterProcessor::updateFilterSet(QSet<int> filterSet)
{

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
                    auto filterOutSlotPtr = filterPtr->outSlot((qint8)0);
                    if(!filterOutSlotPtr.isNull()){
                        QImage img = ImageDataRasterizer::ImageDataToQImage(*(filterOutSlotPtr->asSpatialData()), m_rasterMode);
                        setImageForFilter(curFilter, img);
                    }

                }
                mainFilterIterator.remove();
                updatedFilters.insert(curFilter);
            }
        }
    }
}

inline void FilterProcessor::setImageForFilter(int filterNumber, QImage img)
{
    m_needRastingFilters.remove(filterNumber);
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
    m_needRastingFilters = QSet<int>::fromList(m_filters.keys());
}

void FilterProcessor::rasterNonActualImages()
{
    QSetIterator<int> iter(m_needRastingFilters);
    while(iter.hasNext()){
        int filterNum = iter.next();
        auto filterPtr = m_filters.value(filterNum, NULL);
        if(filterPtr){
            auto filterOutSlotPtr = filterPtr->outSlot((qint8)0);
            if(!filterOutSlotPtr.isNull()){
                QImage img = ImageDataRasterizer::ImageDataToQImage(*(filterOutSlotPtr->asSpatialData()), m_rasterMode);
                setImageForFilter(filterNum, img);
            }
        }
    }
}
