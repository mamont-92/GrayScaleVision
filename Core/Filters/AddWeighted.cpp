#include "AddWeighted.h"
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

AddWeighted::AddWeighted() : AbstractFilter(),
    alpha(1.0f, -10.0f, 10.0f),
    beta(1.0f, -10.0f, 10.0f),
    gamma(0.0f, -65535.0f, 65535.0f)

{
    qDebug() << "Constructor Add Weighted";
    registerInSlot("src1", 0);
    registerInSlot("src2", 1);
    registerOutSlot("res", 0);
    registerParameter("alpha", &alpha);
    registerParameter("beta", &beta);
    registerParameter("gamma", &gamma);
}


void AddWeighted::update()
{
    qDebug() << "Add Weighted::update";
    clearOutSlots();

    clearOutSlots();

    ImageDataSpatialPtr src1DataPtr = inSlot("src1");
    ImageDataSpatialPtr src2DataPtr = inSlot("src2");

    if(src1DataPtr.isNull() || src2DataPtr.isNull())
        return;

    if(src1DataPtr->isEmpty() || src2DataPtr->isEmpty())
        return;


    cv::Mat src1Mat(src1DataPtr->height(), src1DataPtr->width(), CV_32FC1, src1DataPtr->data());
    cv::Mat src2Mat(src2DataPtr->height(), src2DataPtr->width(), CV_32FC1, src2DataPtr->data());
    cv::Mat outMat;

    cv::addWeighted(src1Mat, alpha.valueReal(), src2Mat, beta.valueReal(),gamma.valueReal(), outMat);

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(outMat.cols, outMat.rows);
    memcpy(reinterpret_cast<uchar*>(resultDataPtr->data()), outMat.data, sizeof(float)*outMat.cols*outMat.rows);

    setOutSlot("res", resultDataPtr);
}
