#include "ImageDataConvertor.h"

#include <opencv2/opencv.hpp>

using namespace cv;

void swapMatQuadtrants(Mat & mat){
    int cx2 = mat.cols/2;
    int cy2 = mat.rows/2;

    Mat q0_2(mat, Rect(0, 0, cx2, cy2));   // Top-Left - Create a ROI per quadrant
    Mat q1_2(mat, Rect(cx2, 0, cx2, cy2));  // Top-Right
    Mat q2_2(mat, Rect(0, cy2, cx2, cy2));  // Bottom-Left
    Mat q3_2(mat, Rect(cx2, cy2, cx2, cy2)); // Bottom-Right

    Mat tmp_2;                           // swap quadrants (Top-Left with Bottom-Right)
    q0_2.copyTo(tmp_2);
    q3_2.copyTo(q0_2);
    tmp_2.copyTo(q3_2);

    q1_2.copyTo(tmp_2);                    // swap quadrant (Top-Right with Bottom-Left)
    q2_2.copyTo(q1_2);
    tmp_2.copyTo(q2_2);
}

ImageDataSpatialPtr ImageDataConvertor::convertToSpatialData(ImageDataFrequencyPtr frequencyDataPtr)
{
    if((frequencyDataPtr.isNull()) || (frequencyDataPtr->isEmpty()))
        return ImageDataSpatialPtr();

    const std::complex<float> * scrComplexData = frequencyDataPtr->data();

    qint32 scrWidth = frequencyDataPtr->width();
    qint32 scrHeight = frequencyDataPtr->height();
    qint32 scrDataSize = frequencyDataPtr->pixelCount();

    float * realComplexData = new float[scrDataSize];
    float * imagComplexData = new float[scrDataSize];

    for(qint32 i = 0; i < scrDataSize; ++i){
        realComplexData[i] = scrComplexData[i].real();
        imagComplexData[i] = scrComplexData[i].imag();
    }

    Mat scrRealComplexMat(scrHeight, scrWidth, CV_32F, realComplexData);
    Mat scrImagComplexMat(scrHeight, scrWidth, CV_32F, imagComplexData);

    Mat planes[] = {Mat_<float>(scrRealComplexMat), Mat_<float>(scrImagComplexMat)};

    swapMatQuadtrants(planes[0]);
    swapMatQuadtrants(planes[1]);

    Mat complexMat;
    merge(planes, 2, complexMat);

    Mat inverseTransform;
    cv::dft(complexMat, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);

    qint32 resultWidth =  inverseTransform.cols;
    qint32 resultHeight = inverseTransform.rows;
    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(resultWidth, resultHeight);
    qint32 resultDataSize = resultDataPtr->pixelCount();

    float * ptr = reinterpret_cast<float*>(inverseTransform.data);
    float * resultPtrData = resultDataPtr->data();
    for(qint32 i = 0; i < resultDataSize; ++i){
        resultPtrData[i] = ptr[i] / (float)resultDataSize;
    }

    delete [] realComplexData;
    delete [] imagComplexData;

    return resultDataPtr;
}

ImageDataFrequencyPtr ImageDataConvertor::convertToFrequencyData(ImageDataSpatialPtr spatialDataPtr)
{
    if((spatialDataPtr.isNull()) || (spatialDataPtr->isEmpty()))
        return ImageDataFrequencyPtr();

    qint32 scrWidth = spatialDataPtr->width();
    qint32 scrHeight = spatialDataPtr->height();
    qint32 scrDataSize = spatialDataPtr->pixelCount();

    float * scrData = new float [scrDataSize];
    memcpy(scrData, spatialDataPtr->data(), scrDataSize*sizeof(float));

    Mat I(scrHeight, scrWidth, CV_32F, scrData);
    Mat planes[] = {Mat_<float>(I), Mat::zeros(I.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);
    dft(complexI, complexI);

    split(complexI, planes);

    swapMatQuadtrants(planes[0]);
    swapMatQuadtrants(planes[1]);

    qint32 resultWidth =  planes[0].cols;
    qint32 resultHeight = planes[0].rows;
    ImageDataFrequencyPtr resultDataPtr = ImageDataFrequencyPtr::create(resultWidth, resultHeight);
    qint32 maxInd = spatialDataPtr->pixelCount();

    std::complex<float> * resultComplexData = resultDataPtr->data();
    float * realComplexData = reinterpret_cast<float*>(planes[0].data);
    float * imagComplexData = reinterpret_cast<float*>(planes[1].data);

    for(qint32 i = 0; i < maxInd; ++i){
        resultComplexData[i] = std::complex<float>(realComplexData[i], imagComplexData[i]);
    }

    delete [] scrData;

    return resultDataPtr;
}
