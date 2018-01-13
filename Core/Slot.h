#ifndef SLOT_H
#define SLOT_H

#include "ImageData/ImageDataFrequency.h"
#include "ImageData/ImageDataSpatial.h"
#include <QSharedPointer>
#include <QWeakPointer>

class Slot;
typedef QSharedPointer<Slot> SlotPtr;
typedef QWeakPointer<Slot> SlotWeakPtr;

class Slot
{
public:
    Slot();

    ImageDataSpatial * asSpatialData();
    ImageDataFrequency * asFrequencyData();

    void setSpatialChanged();
    void setFrequencyChanged();
private:
    bool m_isSpatialActual, m_isFrequencyActual;
    ImageDataSpatial m_spatialData;
    ImageDataFrequency m_frequencyData;
};

#endif // SLOT_H
