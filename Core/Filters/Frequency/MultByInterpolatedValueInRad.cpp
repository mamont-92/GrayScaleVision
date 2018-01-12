#include "MultByInterpolatedValueInRad.h"
#include <QDebug>

#include "Core/ImageData/ImageDataConvertor.h"

MultByInterpolatedValueInRad::MultByInterpolatedValueInRad() : AbstractFilter(),
    value1(0.3f, 0.0f, 1.0f),
    value2(1.0f, 0.0f, 1.0f),
    radius(60, 1, 65535)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("value1", &value1);
    registerParameter("value2", &value2);
    registerParameter("radius", &radius);
}

void MultByInterpolatedValueInRad::update()
{
    auto inSlotPtr1 = inSlotLock("src");
    auto outSlotPtr = outSlot("res");
    auto outDataPtr = outSlotPtr->asFrequencyData();

    if(inSlotPtr1.isNull()){
        qDebug() << "slot null";
        outDataPtr->setEmpty();
        return;
    }

    auto inDataPtr = inSlotPtr1->asFrequencyData();

    if(inDataPtr->isEmpty()){
        qDebug() << "slot empty";
        outDataPtr->setEmpty();
        return;
    }


    float val1 = value1.valueReal();
    float val2 = value2.valueReal();

    complexFloat * compData = outDataPtr->data();

    int _width = outDataPtr->width();
    int _height = outDataPtr->height();

    float imageRad = radius.valueInt();

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
            float ratio = sqrt(xDelta+yDelta) / imageRad;
            float mult = val2 * ratio + val1 * (1.0 - ratio);
            compData[columnInd + j] *= (ratio > 1.0) ? 1.0 : mult;
        }
    }

    outSlotPtr->setFrequencyChanged();
}

