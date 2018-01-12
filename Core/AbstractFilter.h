#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include "FilterCreator.h"
//#include "ImageData/ImageDataSpatial.h"
#include "Slot.h"
#include "AbstractParameter.h"
#include <QVector>
#include <QHash>

class AbstractFilter
{
public:
    AbstractFilter();
    virtual ~AbstractFilter();

    virtual void update() = 0;

    void setInSlot(QString name, SlotPtr data);
    void setInSlot(int number, SlotPtr data);

    void clearInSlot(int number);

    void setParameter(QString name, QVariant value);

    QVariant parameterValue(QString name) const;
    QVariant parameterInfo(QString name) const;

    QVariant allParametersInfo() const;

    SlotPtr outSlot(QString name);
    SlotPtr outSlot(int number);
protected:
    SlotWeakPtr inSlot(QString name);
    SlotWeakPtr inSlot(int number);
    SlotPtr inSlotLock(QString name);
    SlotPtr inSlotLock(int number);

    void registerInSlot(QString name, int number);
    void registerOutSlot(QString name, int number);
    void registerParameter(QString name, AbstractParameter * parameter);
private:
    QHash<QString, int> m_outNames;
    QHash<QString, int> m_inNames;
    QVector<SlotPtr> m_outSlots;
    QVector<SlotWeakPtr> m_inSlots;
    QHash<QString, AbstractParameter* > m_params;
};

#endif // ABSTRACTFILTER_H
