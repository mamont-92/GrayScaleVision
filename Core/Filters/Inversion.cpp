#include "Inversion.h"
#include <QDebug>

Inversion::Inversion() : AbstractFilter()
{
    qDebug() << "Constructor Inversion";
    registerInSlot("scr", 0);
    registerOutSlot("res", 0);
}

void Inversion::update()
{
    qDebug() << "Inversion::update";
    clearOutSlots();

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
    int maxInd = inputDataPtr->pixelCount();

    for(int i = 0; i < maxInd; ++i){
        outData[i] = maxVal - inData[i];
    }

    setOutSlot("res", resultDataPtr);
}
