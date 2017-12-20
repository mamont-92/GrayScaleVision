#include "CLAHE.h"
#include "opencv2/opencv.hpp"

CLAHE::CLAHE() : AbstractFilter(),
    clipCount(80, 4, 120),
    tileSize(8,2, 16)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("clip count", &clipCount);
    registerParameter("tile size", &tileSize);
}

void CLAHE::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    float minVal, maxVal;
    inDataPtr->calcMinMax(minVal, maxVal);

    cv::Mat tempUShortMat, outMat,  inMat(inDataPtr->height(), inDataPtr->width(), CV_32FC1, inDataPtr->data());

    const float maxUShortVal = 65535;
    float delta = qMax(maxVal - minVal, (float)0.00001);
    inMat.convertTo(tempUShortMat, CV_16UC1, 1.f/delta*maxUShortVal, (-1.0)*minVal*maxUShortVal/delta);

    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(clipCount.valueInt());
    int tSize = tileSize.valueInt();
    clahe->setTilesGridSize(cv::Size(tSize,tSize));
    clahe->apply(tempUShortMat,outMat);

    outMat.convertTo(outMat, CV_32FC1, 1.f/delta*maxUShortVal, 0);

    outDataPtr->setWithCopyData(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
}
