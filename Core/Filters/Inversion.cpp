#include "Inversion.h"
#include <QDebug>

Inversion::Inversion() : AbstractFilter()
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
}

void Inversion::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    outDataPtr->resize(inDataPtr->size());

    float * inRawData = inDataPtr->data();
    float * outRawData = outDataPtr->data();

    float minVal, maxVal;
    inDataPtr->calcMinMax(minVal, maxVal);

    int maxInd = qMin(inDataPtr->pixelCount(), outDataPtr->pixelCount());

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        outRawData[i] = maxVal - inRawData[i];
    }
}
