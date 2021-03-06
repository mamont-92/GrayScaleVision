#include "FilterProcessorGate.h"
#include "GlobalContext.h"
#include "Commands.h"

using namespace FilterProcessorComands;

FilterProcessorGate::FilterProcessorGate(QObject *parent) : QObject(parent), m_filterProcessor(NULL)
{
    m_filterProcessor = GlobalContext::instance().filterManager();
    connect(m_filterProcessor, &FilterProcessor::imageRastered, [this] (int number) {
        emit imageRastered(number);
    });
    connect(m_filterProcessor, &FilterProcessor::paramsChanged, [this] (const FilterParams & params){
        QVariantMap paramsMap = {
            {"filterNumber", QVariant::fromValue(params.filterNumber)},
            {"params", params.parameter},
        };
        emit paramsChanged(QVariant::fromValue(paramsMap));
    });
}

void FilterProcessorGate::addFilter(int num, QString type)
{
    if(m_filterProcessor)
        m_filterProcessor->execute(new AddFilter(num, type));
}

void FilterProcessorGate::removeFilter(int num)
{
    if(m_filterProcessor)
        m_filterProcessor->execute(new RemoveFilter(num));
}

void FilterProcessorGate::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    if(m_filterProcessor)
        m_filterProcessor->execute(new ConnectFilters(filterOut, connectorOut, filterIn, connectorIn));
}

void FilterProcessorGate::setParameterValueForFilter(int filterNumber, QString paramName, QVariant value)
{
    if(m_filterProcessor)
        m_filterProcessor->execute(new SetParameterForFilter(filterNumber, paramName, value));
}

QVariant FilterProcessorGate::availableFilters()
{
    if(m_filterProcessor)
        return m_filterProcessor->availableFilters();
    return QVariant();
}

QVariant FilterProcessorGate::availableRasterModes()
{
    if(m_filterProcessor)
        return m_filterProcessor->availableRasterModes();
    return QVariant();
}

void FilterProcessorGate::setRasterMode(QString mode)
{
    if(m_filterProcessor)
        m_filterProcessor->execute(new SetRasterMode(mode));
}
