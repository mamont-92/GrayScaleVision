#ifndef IMAGEDATARASTERIZER_H
#define IMAGEDATARASTERIZER_H

#include <QImage>
#include "ImageDataSpatial.h"

class ImageDataRasterizer
{
public:
    static QImage ImageDataToQImage(const ImageDataSpatial & imgData);
};

#endif // IMAGEDATARASTERIZER_H
