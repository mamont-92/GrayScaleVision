#include "AbstractFilter.h"
#include <QDebug>

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
}

void AbstractFilter::setOutSlot(QString name, ImageDataSpatialPtr data)
{
    int ind = m_outNames.value(name, -1);
    setOutSlot(ind, data);
}

void AbstractFilter::setOutSlot(int number, ImageDataSpatialPtr data)
{
    if( (number >= 0) && (number < m_outSlots.size()) )
         m_outSlots[number] = data;
}

void AbstractFilter::setInSlot(QString name, ImageDataSpatialPtr data)
{
    int ind = m_inNames.value(name, -1);
    setInSlot(ind, data);
}

void AbstractFilter::setInSlot(int number, ImageDataSpatialPtr data)
{
    if( (number >= 0) && (number < m_inSlots.size()) )
        m_inSlots[number] = data;
}


ImageDataSpatialPtr AbstractFilter::outSlot(QString name)
{
    return outSlot(m_outNames.value(name, -1));
}

ImageDataSpatialPtr AbstractFilter::outSlot(int number)
{
    if( (number >= 0) && (number < m_outSlots.size()) )
        return m_outSlots[number];
    else
        qDebug() << "assert!";
    return  ImageDataSpatialPtr();
}

ImageDataSpatialPtr AbstractFilter::inSlot(QString name)
{
    return inSlot(m_inNames.value(name, -1));
}

ImageDataSpatialPtr AbstractFilter::inSlot(int number)
{
    if( (number >= 0) && (number < m_inSlots.size()) )
        return m_inSlots[number];
    return  ImageDataSpatialPtr();
}
