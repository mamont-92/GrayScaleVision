#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

#include "FilterCreator.h"
#include "ImageData/ImageDataSpatial.h"
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

    ImageDataSpatialPtr outSlot(QString name);
    ImageDataSpatialPtr outSlot(int number);
protected:
    ImageDataSpatialPtr inSlot(QString name);
    ImageDataSpatialPtr inSlot(int number);

    void registerInSlot(QString name, int number);
    void registerOutSlot(QString name, int number);
    void setOutSlot(QString name, ImageDataSpatialPtr data);
    void setOutSlot(int number, ImageDataSpatialPtr data);
private:
    QHash<QString, int> m_outNames;
    QHash<QString, int> m_inNames;
    QVector<ImageDataSpatialPtr> m_outSlots;
    QVector<ImageDataSpatialPtr> m_inSlots;
};

#endif // ABSTRACTFILTER_H
