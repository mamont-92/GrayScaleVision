#include "BoundByPercent.h"

BoundByPercent::BoundByPercent() : AbstractFilter(),
    minPercent(0.0f, 0.0f, 100.0f),
    maxPercent(100.0f, 0.0f, 100.0f)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("start", &minPercent);
    registerParameter("end", &maxPercent);
}

void BoundByPercent::update()
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

    float minRatio = minPercent.valueReal()*0.01;
    float maxRatio = maxPercent.valueReal()*0.01;

    outDataPtr->resize(inDataPtr->size());

    float * inRawData = inDataPtr->data();
    float * outRawData = outDataPtr->data();

    float minVal, maxVal;
    ImageDataUtils::min_max(*inDataPtr, minVal, maxVal);
    float delta = maxVal - minVal;

    float newMinVal = minVal + delta*minRatio;
    float newMaxVal = minVal + delta*maxRatio;

    int maxInd = qMin(inDataPtr->pixelCount(), outDataPtr->pixelCount());

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        outRawData[i] = qBound(newMinVal, inRawData[i], newMaxVal);
    }

    outSlotPtr->setSpatialChanged();
}

