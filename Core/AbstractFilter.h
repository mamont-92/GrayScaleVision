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

    virtual void update() = 0;

    int number();
    void setNumber(int _number);

    void setInSlot(QString name, ImageDataSpatial data);
    void setInSlot(qint8 number, ImageDataSpatial data);

    ImageDataSpatial outSlot(QString name);
    ImageDataSpatial outSlot(qint8 number);
protected:
    void registerInSlot(QString name, qint8 number);
    void registerOutSlot(QString name, qint8 number);
    void setOutSlot(QString name, ImageDataSpatial data);
    void setOutSlot(int number, ImageDataSpatial data);
private:
    QHash<QString, int> m_outNames;
    QHash<QString, int> m_inNames;
    QVector<ImageDataSpatial > m_outSlots;
    QVector<ImageDataSpatial > m_inSlots;
};

#endif // ABSTRACTFILTER_H
