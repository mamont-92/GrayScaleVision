#include "MultByConstInRad.h"

#include "Core/ImageData/ImageDataConvertor.h"

MultByConstInRad::MultByConstInRad() : AbstractFilter(),
    multiplier(0.7f, 0.0f, 1.0f),
    radius(90, 0, 65535)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("multiplier", &multiplier);
    registerParameter("radius", &radius);
}

void MultByConstInRad::update()
{
    auto inSlotPtr1 = inSlotLock("src");
    auto outSlotPtr = outSlot("res");
    auto outDataPtr = outSlotPtr->asFrequencyData();

    if(inSlotPtr1.isNull()){
        outDataPtr->setEmpty();
        return;
    }

    auto inDataPtr = inSlotPtr1->asFrequencyData();

    if(inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }


    outDataPtr->resize(inDataPtr->size());
    float mult = multiplier.valueReal();

    complexFloat * inCompData = inDataPtr->data();
    complexFloat * outCompData = outDataPtr->data();

    int _width = inDataPtr->width();
    int _height = inDataPtr->height();

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
            float scale = ((xDelta+yDelta) > imageRadSqr) ? 1.0 : mult; //
            outCompData[columnInd + j] = scale * inCompData[columnInd + j];
        }
    }

    outSlotPtr->setFrequencyChanged();
}

