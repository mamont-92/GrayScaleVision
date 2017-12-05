#include "Inversion.h"

Inversion::Inversion() : AbstractFilter()
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
}

void Inversion::update()
{
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlot("src");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float * inData = inputDataPtr->data();

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(inputDataPtr->width(), inputDataPtr->height());
    float * outData = resultDataPtr->data();

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);
    int maxInd = inputDataPtr->pixelCount();

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        outData[i] = maxVal - inData[i];
    }

    setOutSlot("res", resultDataPtr);
}
