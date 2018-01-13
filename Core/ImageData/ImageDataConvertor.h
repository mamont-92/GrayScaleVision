#ifndef IMAGEDATACONVERTOR_H
#define IMAGEDATACONVERTOR_H


#include "ImageDataFrequency.h"
#include "ImageDataSpatial.h"

class ImageDataConvertor
{
public:
    static ImageDataSpatial convertToSpatialData(const ImageDataFrequency & frequencyDataPtr);
    static ImageDataFrequency convertToFrequencyData(const ImageDataSpatial & spatialDataPtr);
};

#endif // IMAGEDATACONVERTOR_H
