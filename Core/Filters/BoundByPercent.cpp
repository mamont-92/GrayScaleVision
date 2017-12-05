#include "BoundByPercent.h"
#include <QDebug>

BoundByPercent::BoundByPercent() : AbstractFilter()
{
    qDebug() << "Constructor BoundByPercent";
    registerInSlot("scr", 0);
    registerOutSlot("res", 0);
}

void BoundByPercent::update()
{
    qDebug() << "BoundByPercent::update";
    clearOutSlots();
    float minPercent = 0.1;
    float maxPercent = 0.9;

    ImageDataSpatialPtr inputDataPtr = inSlot("scr");
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

    float newMinVal = minVal + delta*minPercent;
    float newMaxVal = minVal + delta*maxPercent;

    int maxInd = inputDataPtr->pixelCount();

    for(int i = 0; i < maxInd; ++i){
        outData[i] = qBound(newMinVal, inData[i], newMaxVal);
    }

    setOutSlot("res", resultDataPtr);
}
