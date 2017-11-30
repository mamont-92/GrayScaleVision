#ifndef IMAGEDATARASTERIZER_H
#define IMAGEDATARASTERIZER_H

#include <QImage>
#include "ImageDataSpatial.h"

class ImageDataRasterizer
{
public:
    static QImage ImageDataToQImage(ImageDataSpatialPtr imgDataPtr);
};

#endif // IMAGEDATARASTERIZER_H
