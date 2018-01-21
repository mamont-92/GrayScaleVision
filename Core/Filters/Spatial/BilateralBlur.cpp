#include "BilateralBlur.h"
#include "opencv2/opencv.hpp"

BilateralBlur::BilateralBlur() : AbstractFilter(),
    sigmaIntensity(1000, 1, 10000),
    sigmaSpace(3,1, 10)

{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("sigma intensity", &sigmaIntensity);
    registerParameter("sigma space", &sigmaSpace);
}

void BilateralBlur::update()
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

    cv::Mat outMat, inMat(inDataPtr->height(), inDataPtr->width(), CV_32FC1, inDataPtr->data());
    cv::bilateralFilter(inMat, outMat, diameter.valueInt(), sigmaIntensity.valueInt(), sigmaSpace.valueInt());
    cv::bilateralFilter(inMat, outMat, -1, sigmaIntensity.valueInt(), sigmaSpace.valueInt());

    outDataPtr->setDataWithCopy(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
    outSlotPtr->setSpatialChanged();
}
