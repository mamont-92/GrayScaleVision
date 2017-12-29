#ifndef IMAGEDATARASTERIZER_H
#define IMAGEDATARASTERIZER_H

#include <QVariant>
#include <QMap>
#include <QImage>
#include "ImageDataSpatial.h"

class ImageDataRasterizer
{
public:
    static QImage ImageDataToQImage(ImageDataSpatialPtr imgDataPtr, QString colorMode = "Grayscale");
    static QStringList availableRasterModes();
private:
    static const QMap<QString, int> m_rasterModes;
};

#endif // IMAGEDATARASTERIZER_H
