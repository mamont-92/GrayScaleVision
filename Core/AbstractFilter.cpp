#include "AbstractFilter.h"

AbstractFilter::AbstractFilter()
{

}

AbstractFilter::~AbstractFilter()
{

}

void AbstractFilter::registerInSlot(QString name, int number)
{
    m_inNames.insert(name, number);
    if(m_inSlots.size() <= number)
        m_inSlots.resize(number+1);
}

void AbstractFilter::registerOutSlot(QString name, int number)
{
    m_outNames.insert(name, number);
    if(m_outSlots.size() <= number)
        m_outSlots.resize(number+1);
    m_outSlots[number] = ImageDataSpatialPtr::create(0,0);
}

void AbstractFilter::registerParameter(QString name, AbstractParameter * parameter)
{
    m_params.insert(name, parameter); // warning: no memory managment there, need delete objects in source
}

void AbstractFilter::setInSlot(QString name, ImageDataSpatialPtr data)
{
    int ind = m_inNames.value(name, -1);
    setInSlot(ind, data);
}

void AbstractFilter::setInSlot(int number, ImageDataSpatialPtr data)
{
    if( (number >= 0) && (number < m_inSlots.size()) )
        m_inSlots[number] = ImageDataSpatialWeakPtr(data);
}

void AbstractFilter::clearInSlot(int number)
{
    if( (number >= 0) && (number < m_inSlots.size()) )
        m_inSlots[number].clear();
}

void AbstractFilter::setParameter(QString name, QVariant value)
{
    AbstractParameter * parameter = m_params.value(name, NULL);
    if(parameter)
        parameter->setValue(value);
}

QVariant AbstractFilter::parameterValue(QString name) const
{
    AbstractParameter * parameter = m_params.value(name, NULL);
    if(parameter)
        return parameter->value();
    return QVariant();
}

QVariant AbstractFilter::parameterInfo(QString name) const
{
    AbstractParameter * parameter = m_params.value(name, NULL);
    if(parameter)
        return parameter->info();
    return QVariant();
}

QVariant AbstractFilter::allParametersInfo() const
{
    QVariantMap resultMap;

    QHashIterator<QString, AbstractParameter*> iter(m_params);
    while(iter.hasNext()){
        iter.next();
        if(iter.value())
            resultMap.insert(iter.key(), iter.value()->info());
    }
    return QVariant::fromValue(resultMap);
}

ImageDataSpatialPtr AbstractFilter::outSlot(QString name)
{
    return outSlot(m_outNames.value(name, -1));
}

ImageDataSpatialPtr AbstractFilter::outSlot(int number)
{
    return  m_outSlots.value(number);
}

ImageDataSpatialWeakPtr AbstractFilter::inSlot(QString name)
{
    return inSlot(m_inNames.value(name, -1));
}

ImageDataSpatialWeakPtr AbstractFilter::inSlot(int number)
{
    return m_inSlots.value(number);
}

ImageDataSpatialPtr AbstractFilter::inSlotLock(QString name)
{
    return inSlot(name).lock();
}

ImageDataSpatialPtr AbstractFilter::inSlotLock(int number)
{
    return inSlot(number).lock();
}
