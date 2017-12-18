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
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlotLock("src");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);

    cv::Mat outMat, inMat(inputDataPtr->height(), inputDataPtr->width(), CV_32FC1, inputDataPtr->data());

    cv::bilateralFilter(inMat, outMat, diameter.valueInt(), sigmaIntensity.valueInt(), sigmaSpace.valueInt());

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(outMat.cols, outMat.rows);
    memcpy(reinterpret_cast<uchar*>(resultDataPtr->data()), outMat.data, sizeof(float)*outMat.cols*outMat.rows);

    setOutSlot("res", resultDataPtr);
}
