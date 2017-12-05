#include "Power.h"
#include <QDebug>
#include "opencv2/opencv.hpp"

Power::Power() : AbstractFilter()
{
    qDebug() << "Constructor Power";
    registerInSlot("scr", 0);
    registerOutSlot("res", 0);
}

void Power::update()
{
    qDebug() << "Power::update";
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlot("scr");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float * inData = inputDataPtr->data();

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(inputDataPtr->width(), inputDataPtr->height());
    float * outData = resultDataPtr->data();

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);
    float delta = qMax(maxVal - minVal, (float)0.00001);

    cv::Mat outMat,  inMat(inputDataPtr->height(), inputDataPtr->width(), CV_32FC1, inputDataPtr->data());
    inMat.convertTo(outMat, -1, 1.f/delta, (-1.0)*minVal/delta);
    cv::pow(outMat, 0.5, outMat);
    outMat.convertTo(outMat, -1, delta, minVal);

    memcpy(reinterpret_cast<uchar*>(resultDataPtr->data()), outMat.data, sizeof(float)*outMat.cols*outMat.rows);

    setOutSlot("res", resultDataPtr);
}
