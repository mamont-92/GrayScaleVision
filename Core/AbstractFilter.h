#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include "FilterCreator.h"
#include "ImageData/ImageDataSpatial.h"
#include "AbstractParameter.h"
#include <QVector>
#include <QHash>

class AbstractFilter
{
public:
    AbstractFilter();
    virtual ~AbstractFilter();

    virtual void update() = 0;

    void setInSlot(QString name, ImageDataSpatialPtr data);
    void setInSlot(int number, ImageDataSpatialPtr data);

    void clearInSlot(int number);

    void setParameter(QString name, QVariant value);

    QVariant parameterValue(QString name) const;
    QVariant parameterInfo(QString name) const;

    QVariant allParametersInfo() const;

    ImageDataSpatialPtr outSlot(QString name);
    ImageDataSpatialPtr outSlot(int number);
protected:
    ImageDataSpatialWeakPtr inSlot(QString name);
    ImageDataSpatialWeakPtr inSlot(int number);
    ImageDataSpatialPtr inSlotLock(QString name);
    ImageDataSpatialPtr inSlotLock(int number);

    void registerInSlot(QString name, int number);
    void registerOutSlot(QString name, int number);
    void registerParameter(QString name, AbstractParameter * parameter);
private:
    QHash<QString, int> m_outNames;
    QHash<QString, int> m_inNames;
    QVector<ImageDataSpatialPtr> m_outSlots;
    QVector<ImageDataSpatialWeakPtr> m_inSlots;
    QHash<QString, AbstractParameter* > m_params;
};

#endif // ABSTRACTFILTER_H
