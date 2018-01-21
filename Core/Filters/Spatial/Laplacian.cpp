#include "Laplacian.h"
#include "opencv2/opencv.hpp"

Laplacian::Laplacian() : AbstractFilter(),
    kernelSize(3, 1, 15, IntegerParameter::OnlyOdd)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("kernel size", &kernelSize);
}

void Laplacian::update()
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

    cv::Mat outMat,  inMat(inDataPtr->height(), inDataPtr->width(), CV_32FC1, inDataPtr->data());
    cv::Laplacian(inMat, outMat, -1, kernelSize.valueInt());

    outDataPtr->setDataWithCopy(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
    outSlotPtr->setSpatialChanged();
}
