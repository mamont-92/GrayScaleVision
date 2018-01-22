#ifndef IMAGEDATACONVERTOR_H
#define IMAGEDATACONVERTOR_H

#include "ImageData.h"

class ImageDataConvertor
{
public:
    static ImageDataSpatial convertToSpatialData(const ImageDataFrequency & frequencyDataPtr);
    static ImageDataFrequency convertToFrequencyData(const ImageDataSpatial & spatialDataPtr);
};

#endif // IMAGEDATACONVERTOR_H
