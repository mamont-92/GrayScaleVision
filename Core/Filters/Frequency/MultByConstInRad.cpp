#include "MultByConstInRad.h"

#include "Core/ImageData/ImageDataConvertor.h"

MultByConstInRad::MultByConstInRad() : AbstractFilter(),
    multiplier(0.9f, 0.0f, 1.0f),
    radius(1, 0, 65535)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("multiplier", &multiplier);
    registerParameter("radius", &radius);
}

void MultByConstInRad::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    auto freqDataPtr = ImageDataConvertor::convertToFrequencyData(inDataPtr);

    float mult = multiplier.valueReal();

    complexFloat * compData = freqDataPtr->data();

    int _width = freqDataPtr->width();
    int _height = freqDataPtr->height();

    quint64 imageRadSqr = radius.valueInt();
    imageRadSqr *= imageRadSqr;

    int centerX = _width / 2;
    int centerY = _height / 2;

    #pragma omp parallel for
    for(int i = 0; i < _height; ++i){
        int columnInd = i*_width;
        quint64 yDelta = i - centerY;
        yDelta*=yDelta;
        for(int j = 0; j < _width; ++j){
            quint64 xDelta = j - centerX;
            xDelta*=xDelta;
            compData[columnInd + j] *= ((xDelta+yDelta) > imageRadSqr) ? 1.0 : mult;
        }
    }


    auto tempSpatial = ImageDataConvertor::convertToSpatialData(freqDataPtr);

    outDataPtr->setWithCopyData(tempSpatial->data(), tempSpatial->size());
}

