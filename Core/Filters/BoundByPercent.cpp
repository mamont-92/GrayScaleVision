#include "BoundByPercent.h"

BoundByPercent::BoundByPercent() : AbstractFilter(),
    minPercent(0.0f, 0.0f, 100.0f),
    maxPercent(100.0f, 0.0f, 100.0f)
{
    registerInSlot("scr", 0);
    registerOutSlot("res", 0);
    registerParameter("start", &minPercent);
    registerParameter("end", &maxPercent);
}

void BoundByPercent::update()
{
    clearOutSlots();
    float minRatio = minPercent.valueReal()*0.01;
    float maxRatio = maxPercent.valueReal()*0.01;

    ImageDataSpatialPtr inputDataPtr = inSlotLock("scr");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float * inData = inputDataPtr->data();

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(inputDataPtr->width(), inputDataPtr->height());
    float * outData = resultDataPtr->data();

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);
    float delta = maxVal - minVal;

    float newMinVal = minVal + delta*minRatio;
    float newMaxVal = minVal + delta*maxRatio;

    int maxInd = inputDataPtr->pixelCount();

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        outData[i] = qBound(newMinVal, inData[i], newMaxVal);
    }

    setOutSlot("res", resultDataPtr);
}

