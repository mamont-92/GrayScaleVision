#ifndef IMAGEDATARASTERIZER_H
#define IMAGEDATARASTERIZER_H

#include <QVariant>
#include <QMap>
#include <QImage>
#include "ImageData.h"

class ImageDataRasterizer
{
public:
    static QImage ImageDataToQImage(const ImageDataSpatial & imgDataPtr, QString colorMode = "Grayscale");
    //static QImage ImageDataToQImage(ImageDataSpatial * imgDataPtr, QString colorMode = "Grayscale");
    static QStringList availableRasterModes();
private:
    static const QMap<QString, int> m_rasterModes;
};

#endif // IMAGEDATARASTERIZER_H
