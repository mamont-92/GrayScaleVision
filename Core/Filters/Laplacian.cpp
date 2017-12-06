#include "Laplacian.h"
#include "opencv2/opencv.hpp"

Laplacian::Laplacian() : AbstractFilter(),
    kernelSize(3, 1, 7)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
}

void Laplacian::update()
{
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlot("src");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(inputDataPtr->width(), inputDataPtr->height());

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);

    cv::Mat outMat,  inMat(inputDataPtr->height(), inputDataPtr->width(), CV_32FC1, inputDataPtr->data());

    cv::Laplacian(inMat, outMat, -1, kernelSize.valueInt());

    memcpy(reinterpret_cast<uchar*>(resultDataPtr->data()), outMat.data, sizeof(float)*outMat.cols*outMat.rows);

    setOutSlot("res", resultDataPtr);
}
