#include "AbstractFilter.h"

AbstractFilter::AbstractFilter()
{

}

void AbstractFilter::registerInSlot(QString name, qint8 number)
{
    m_inNames.insert(name, number);
    if(m_inSlots.size() < (number+1))
        m_inSlots.resize(number+1);
}

void AbstractFilter::registerOutSlot(QString name, qint8 number)
{
    m_outNames.insert(name, number);
    if(m_outSlots.size() < (number+1))
        m_outSlots.resize(number+1);
}

void AbstractFilter::setOutSlot(QString name, ImageDataSpatial data)
{
    int ind = m_outNames.value(name, -1);
        setOutSlot(ind, data);
}

void AbstractFilter::setOutSlot(int number, ImageDataSpatial data)
{
    if( (number > 0) && (number < m_outSlots.size()) )
         m_outSlots[number] = data;
}

void AbstractFilter::setInSlot(QString name, ImageDataSpatial data)
{
    setInSlot(m_inNames.value(name, -1), data);
}

void AbstractFilter::setInSlot(qint8 number, ImageDataSpatial data)
{
    if( (number > 0) && (number < m_outSlots.size()) )
        m_inSlots[number] = data;
}


ImageDataSpatial AbstractFilter::outSlot(QString name)
{
    return outSlot(m_outNames.value(name, -1));
}

ImageDataSpatial AbstractFilter::outSlot(qint8 number)
{
    if( (number > 0) && (number < m_outSlots.size()) )
        return m_outSlots[number];
    return  ImageDataSpatial();
}
