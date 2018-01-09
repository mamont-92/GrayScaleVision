#ifndef IMAGEDATACONVERTOR_H
#define IMAGEDATACONVERTOR_H

/*class ImageDataFrequencyPtr;
class ImageDataSpatialPtr;*/

#include "ImageDataFrequency.h"
#include "ImageDataSpatial.h"

class ImageDataConvertor
{
public:
    static ImageDataSpatialPtr convertToSpatialData(ImageDataFrequencyPtr dataPtr);
    static ImageDataFrequencyPtr convertToFrequencyData(ImageDataSpatialPtr dataPtr);
};

#endif // IMAGEDATACONVERTOR_H
