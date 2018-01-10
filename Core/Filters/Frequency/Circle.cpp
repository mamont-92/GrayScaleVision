#include "Circle.h"

#include "Core/ImageData/ImageDataConvertor.h"

Circle::Circle() : AbstractFilter(),
    minPercent(0.0f, 0.0f, 100.0f),
    maxPercent(100.0f, 0.0f, 100.0f)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("start", &minPercent);
    registerParameter("end", &maxPercent);
}

void Circle::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    auto freqDataPtr = ImageDataConvertor::convertToFrequencyData(inDataPtr);
    auto tempSpatial = ImageDataConvertor::convertToSpatialData(freqDataPtr);

    outDataPtr->setWithCopyData(tempSpatial->data(), tempSpatial->size());
}

