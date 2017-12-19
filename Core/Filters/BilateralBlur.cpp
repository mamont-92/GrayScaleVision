#include "BilateralBlur.h"
#include "opencv2/opencv.hpp"

BilateralBlur::BilateralBlur() : AbstractFilter(),
    diameter(9,0,9, IntegerParameter::OnlyOdd),
    sigmaIntensity(3000, 1, 65535),
    sigmaSpace(50,1, 1000)

{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("diameter", &diameter);
    registerParameter("sigma intensity", &sigmaIntensity);
    registerParameter("sigma space", &sigmaSpace);
}

void BilateralBlur::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    cv::Mat outMat, inMat(inDataPtr->height(), inDataPtr->width(), CV_32FC1, inDataPtr->data());
    cv::bilateralFilter(inMat, outMat, diameter.valueInt(), sigmaIntensity.valueInt(), sigmaSpace.valueInt());

    outDataPtr->setWithCopyData(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
}
