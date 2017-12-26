#include "FilterProcessorGate.h"
#include "GlobalContext.h"

FilterProcessorGate::FilterProcessorGate(QObject *parent) : QObject(parent), m_filterManager(NULL)
{
    m_filterManager = GlobalContext::instance().filterManager();
    connect(m_filterManager, &FilterProcessor::imageRastered, [this] (int number) {
        emit imageRastered(number);
    });
}

void FilterProcessorGate::addFilter(int num, QString type)
{
    if(m_filterManager)
        m_filterManager->addFilter(num, type);
}

void FilterProcessorGate::removeFilter(int num)
{
    if(m_filterManager)
        m_filterManager->removeFilter(num);
}

void FilterProcessorGate::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    if(m_filterManager)
        m_filterManager->connectFilters(filterOut, connectorOut, filterIn, connectorIn);
}

void FilterProcessorGate::setParameterValueForFilter(int filterNumber, QString paramName, QVariant value)
{
    if(m_filterManager)
        m_filterManager->setParameterValueForFilter(filterNumber, paramName, value);
}

QVariant FilterProcessorGate::availableFilters()
{
    if(m_filterManager)
        return m_filterManager->availableFilters();
    return QVariant();
}

QVariant FilterProcessorGate::filterParamsInfo(int filterNumber)
{
    if(m_filterManager)
        return m_filterManager->filterParamsInfo(filterNumber);
    return QVariant();
}
