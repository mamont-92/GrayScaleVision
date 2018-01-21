#include "Inversion.h"
#include <QDebug>

Inversion::Inversion() : AbstractFilter()
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
}

void Inversion::update()
{
    auto inSlotPtr1 = inSlotLock("src");
    auto outSlotPtr = outSlot("res");
    auto outDataPtr = outSlotPtr->asSpatialData();

    if(inSlotPtr1.isNull()){
        outDataPtr->setEmpty();
        return;
    }

    auto inDataPtr = inSlotPtr1->asSpatialData();

    if(inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    outDataPtr->resize(inDataPtr->size());

    float * inRawData = inDataPtr->data();
    float * outRawData = outDataPtr->data();

    float minVal, maxVal;
    min_max(*inDataPtr, minVal, maxVal);
    //inDataPtr->calcMinMax(minVal, maxVal);

    int maxInd = qMin(inDataPtr->pixelCount(), outDataPtr->pixelCount());

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        outRawData[i] = maxVal - inRawData[i];
    }

    outSlotPtr->setSpatialChanged();
}
