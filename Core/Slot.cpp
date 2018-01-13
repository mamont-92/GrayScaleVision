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
        qDebug() << "convertion spatial";
        m_spatialData = ImageDataConvertor::convertToSpatialData(m_frequencyData);
        qDebug() << "end spatial convertion";
        m_isSpatialActual = true;
    }
    return &m_spatialData;
}

ImageDataFrequency * Slot::asFrequencyData()
{
    if(!m_isFrequencyActual){
        qDebug() << "convertion freq";
        m_frequencyData = ImageDataConvertor::convertToFrequencyData(m_spatialData);
        qDebug() << "end freq convertion";
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
