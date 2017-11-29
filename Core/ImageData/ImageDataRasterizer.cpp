#include "ImageDataRasterizer.h"

#include "opencv2/opencv.hpp"

QImage ImageDataRasterizer::ImageDataToQImage(const ImageDataSpatial & imgData){
    ImageDataSpatial tempData = imgData;

    float minVal, maxVal;
    tempData.calcMinMax(minVal, maxVal);
    const float epsilon = 0.00000001f;
    float invDelta = 255.0 / qMax((maxVal - minVal), epsilon);

    qint64 maxInd = tempData.pixelCount();
    QImage resultImage(tempData.width(), tempData.height(), QImage::Format_Grayscale8);

    const float *originalData = tempData.data();
    uchar * bits = resultImage.bits();

    #pragma omp parallel for
    for(int i = 0; i < maxInd; ++i){
        bits[i] = (originalData[i] - minVal) * invDelta;
    }

    return resultImage;
}
