#include "Power.h"
#include "opencv2/opencv.hpp"

Power::Power() : AbstractFilter(),
    power(1.0f, 0.0f, 10.0f)

{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("power", &power);
}

void Power::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    float minVal, maxVal;
    inDataPtr->calcMinMax(minVal, maxVal);
    float delta = qMax(maxVal - minVal, (float)0.00001);

    cv::Mat outMat,  inMat(inDataPtr->height(), inDataPtr->width(), CV_32FC1, inDataPtr->data());
    inMat.convertTo(outMat, -1, 1.f/delta, (-1.0)*minVal/delta);
    cv::pow(outMat, power.valueReal(), outMat);
    outMat.convertTo(outMat, -1, delta, minVal);

    outDataPtr->setWithCopyData(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
}
