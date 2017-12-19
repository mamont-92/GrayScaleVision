#include "AddWeighted.h"
#include "opencv2/opencv.hpp"

AddWeighted::AddWeighted() : AbstractFilter(),
    alpha(1.0f, -10.0f, 10.0f),
    beta(1.0f, -10.0f, 10.0f),
    gamma(0.0f, -65535.0f, 65535.0f)

{
    registerInSlot("src1", 0);
    registerInSlot("src2", 1);
    registerOutSlot("res", 0);
    registerParameter("alpha", &alpha);
    registerParameter("beta", &beta);
    registerParameter("gamma", &gamma);
}


void AddWeighted::update()
{
    auto inDataPtr1 = inSlotLock("src1");
    auto inDataPtr2 = inSlotLock("src2");
    auto outDataPtr = outSlot("res");

    if(inDataPtr1.isNull() || inDataPtr2.isNull() || inDataPtr1->isEmpty()|| inDataPtr2->isEmpty()){
        outDataPtr->setEmpty();
        return;
    }

    cv::Mat src1Mat(inDataPtr1->height(), inDataPtr1->width(), CV_32FC1, inDataPtr1->data());
    cv::Mat src2Mat(inDataPtr2->height(), inDataPtr2->width(), CV_32FC1, inDataPtr2->data());
    cv::Mat outMat;

    cv::addWeighted(src1Mat, alpha.valueReal(), src2Mat, beta.valueReal(),gamma.valueReal(), outMat);

    outDataPtr->setWithCopyData(reinterpret_cast<float*>(outMat.data), QSize(outMat.cols, outMat.rows));
}
