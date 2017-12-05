#include "CLAHE.h"
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

CLAHE::CLAHE() : AbstractFilter(),
    clipCount(80, 4, 120),
    tileSize(8,2, 16)
{
    registerInSlot("scr", 0);
    registerOutSlot("res", 0);
    registerParameter("clip count", &clipCount);
    registerParameter("tile size", &tileSize);
}

void CLAHE::update()
{
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlot("scr");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);

    cv::Mat tempUShortMat, outMat,  inMat(inputDataPtr->height(), inputDataPtr->width(), CV_32FC1, inputDataPtr->data());

    const float maxUShortVal = 65535;
    float delta = qMax(maxVal - minVal, (float)0.00001);
    inMat.convertTo(tempUShortMat, CV_16UC1, 1.f/delta*maxUShortVal, (-1.0)*minVal*maxUShortVal/delta);

    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
    clahe->setClipLimit(clipCount.value().toInt());
    int tSize = tileSize.value().toInt();
    clahe->setTilesGridSize(cv::Size(tSize,tSize));
    clahe->apply(tempUShortMat,outMat);

    outMat.convertTo(outMat, CV_32FC1, 1.f/delta*maxUShortVal, 0);

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(outMat.cols, outMat.rows);
    memcpy(reinterpret_cast<uchar*>(resultDataPtr->data()), outMat.data, sizeof(float)*outMat.cols*outMat.rows);

    setOutSlot("res", resultDataPtr);
}
