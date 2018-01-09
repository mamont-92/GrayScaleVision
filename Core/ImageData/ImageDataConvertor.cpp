#include "ImageDataConvertor.h"
/*#include "ImageDataFrequency.h"
#include "ImageDataSpatial.h"
*/
ImageDataSpatialPtr ImageDataConvertor::convertToSpatialData(ImageDataFrequencyPtr dataPtr)
{
    return ImageDataSpatialPtr();
}

ImageDataFrequencyPtr ImageDataConvertor::convertToFrequencyData(ImageDataSpatialPtr dataPtr)
{
    return ImageDataFrequencyPtr();
}
