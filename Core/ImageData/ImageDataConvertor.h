#ifndef IMAGEDATACONVERTOR_H
#define IMAGEDATACONVERTOR_H

/*class ImageDataFrequencyPtr;
class ImageDataSpatialPtr;*/

#include "ImageDataFrequency.h"
#include "ImageDataSpatial.h"

class ImageDataConvertor
{
public:
    static ImageDataSpatialPtr convertToSpatialData(ImageDataFrequencyPtr frequencyDataPtr);
    static ImageDataFrequencyPtr convertToFrequencyData(ImageDataSpatialPtr spatialDataPtr);
};

#endif // IMAGEDATACONVERTOR_H
