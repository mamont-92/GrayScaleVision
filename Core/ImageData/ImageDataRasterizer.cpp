#include "ImageDataRasterizer.h"

#include "opencv2/opencv.hpp"

QImage ImageDataRasterizer::ImageDataToQImage(ImageDataSpatialPtr imgDataPtr){
    if(imgDataPtr.isNull())
        return QImage();
    if(imgDataPtr->isEmpty())
        return QImage();

    float minVal, maxVal;
    imgDataPtr->calcMinMax(minVal, maxVal);
    const float epsilon = 0.00000001f;
    float invDelta = 255.0 / qMax((maxVal - minVal), epsilon);

    qint64 maxInd = imgDataPtr->pixelCount();
    QImage resultImage(imgDataPtr->width(), imgDataPtr->height(), QImage::Format_Grayscale8);

    const float *originalData = imgDataPtr->data();
    uchar * bits = resultImage.bits();

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        bits[i] = (originalData[i] - minVal) * invDelta;
    }

    return resultImage;
}
