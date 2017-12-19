#include "Laplacian.h"
#include "opencv2/opencv.hpp"

Laplacian::Laplacian() : AbstractFilter(),
    kernelSize(3, 1, 7, IntegerParameter::OnlyOdd)
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
}

void Laplacian::update()
{
    auto inDataPtr = inSlotLock("src");
    auto outDataPtr = outSlot("res");

    if(inDataPtr.isNull() || inDataPtr->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    cv::Mat outMat,  inMat(inDataPtr->height(), inDataPtr->width(), CV_32FC1, inDataPtr->data());
    cv::Laplacian(inMat, outMat, -1, kernelSize.valueInt());

    outDataPtr->setWithCopyData(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
}
