#include "BilateralBlur.h"
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

BilateralBlur::BilateralBlur() : AbstractFilter(),
    diameter(9,0,9),
    sigmaIntensity(3000, 1, 65535),
    sigmaSpace(50,1, 1000)

{
    qDebug() << "Constructor BilateralBlur";
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("diameter", &diameter);
    registerParameter("sigma intensity", &sigmaIntensity);
    registerParameter("sigma space", &sigmaSpace);
}

void BilateralBlur::update()
{
    qDebug() << "BilateralBlur::update";
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlot("src");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);

    cv::Mat tempUShortMat, outMat,  inMat(inputDataPtr->height(), inputDataPtr->width(), CV_32FC1, inputDataPtr->data());

    const float maxUShortVal = 65535;
    float delta = qMax(maxVal - minVal, (float)0.00001);

    cv::bilateralFilter(inMat, outMat, diameter.valueInt(), sigmaIntensity.valueInt(), sigmaSpace.valueInt());

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(outMat.cols, outMat.rows);
    memcpy(reinterpret_cast<uchar*>(resultDataPtr->data()), outMat.data, sizeof(float)*outMat.cols*outMat.rows);

    setOutSlot("res", resultDataPtr);
}
