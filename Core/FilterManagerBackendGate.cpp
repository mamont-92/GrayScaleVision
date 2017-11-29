#include "FilterManagerBackendGate.h"
#include "GlobalContext.h"

FilterManagerBackendGate::FilterManagerBackendGate(QObject *parent) : QObject(parent), m_filterManager(NULL)
{
    m_filterManager = GlobalContext::instance().filterManager();
}

void FilterManagerBackendGate::addFilter(int num, QString type)
{
    if(m_filterManager)
        m_filterManager->addFilter(num, type);
}

void FilterManagerBackendGate::removeFilter(int num)
{
    if(m_filterManager)
        m_filterManager->removeFilter(num);
}

void FilterManagerBackendGate::connectFilters(int filterOut, int connectorOut, int filterIn, int connectorIn)
{
    if(m_filterManager)
        m_filterManager->connectFilters(filterOut, connectorOut, filterIn, connectorIn);
}

QVariant FilterManagerBackendGate::filterCreationTemplate()
{
    if(m_filterManager)
        return m_filterManager->filterCreationTemplate();
    return QVariant();
}