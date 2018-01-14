#include "Slot.h"
#include "ImageData/ImageDataConvertor.h"
#include <QDebug>

Slot::Slot():
    m_isSpatialActual(true),
    m_isFrequencyActual(true)
{

}

ImageDataSpatial * Slot::asSpatialData()
{
    if(!m_isSpatialActual){
        m_spatialData = ImageDataConvertor::convertToSpatialData(m_frequencyData);
        m_isSpatialActual = true;
    }
    return &m_spatialData;
}

ImageDataFrequency * Slot::asFrequencyData()
{
    if(!m_isFrequencyActual){
        m_frequencyData = ImageDataConvertor::convertToFrequencyData(m_spatialData);
        m_isFrequencyActual = true;
    }
    return &m_frequencyData;
}

void Slot::setSpatialChanged()
{
    m_isSpatialActual = true;
    m_isFrequencyActual = false;
}

void Slot::setFrequencyChanged()
{
    m_isSpatialActual = false;
    m_isFrequencyActual = true;
}
