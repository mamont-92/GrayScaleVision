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
    void setInSlot(qint8 number, ImageDataSpatialPtr data);

    ImageDataSpatialPtr outSlot(QString name);
    ImageDataSpatialPtr outSlot(qint8 number);
protected:
    void registerInSlot(QString name, qint8 number);
    void registerOutSlot(QString name, qint8 number);
    void setOutSlot(QString name, ImageDataSpatialPtr data);
    void setOutSlot(int number, ImageDataSpatialPtr data);
private:
    QHash<QString, int> m_outNames;
    QHash<QString, int> m_inNames;
    QVector<ImageDataSpatialPtr> m_outSlots;
    QVector<ImageDataSpatialPtr> m_inSlots;
};

#endif // ABSTRACTFILTER_H
