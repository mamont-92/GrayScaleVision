#include "ImageDataRasterizer.h"
#include <QDebug>

#include "opencv2/opencv.hpp"

const QMap<QString, int> ImageDataRasterizer::m_rasterModes = {
    {QString("Grayscale"), -1},
    {QString("Autumn"), 1},
    {QString("Bone"), 10},
    {QString("Cool"), 7},
    {QString("Hot"), 3},
    {QString("Hsv"), 2},
    {QString("Jet"), 4},
    {QString("Ocean"), 11},
    {QString("Pink"), 5},
    {QString("Rainbow"), 9},
    {QString("Spring"), 8},
    {QString("Summer"), 6},
    {QString("Winter"), 0}
};


QStringList ImageDataRasterizer::availableRasterModes()
{
    return m_rasterModes.keys();
}


QImage ImageDataRasterizer::ImageDataToQImage(const ImageDataSpatial & imgDataPtr, QString colorMode){

    if(imgDataPtr.isEmpty())
        return QImage();

    float minVal, maxVal;
    imgDataPtr.calcMinMax(minVal, maxVal);
    const float epsilon = 0.00000001f;
    float invDelta = 255.0 / qMax((maxVal - minVal), epsilon);

    qint64 maxInd = imgDataPtr.pixelCount();

    int rasterMode = m_rasterModes.value(colorMode, -1);
    if(rasterMode >= 0){
        cv::Mat srcMat(imgDataPtr.height(), imgDataPtr.width(), CV_32FC1, const_cast<float*>(imgDataPtr.data()) ), convMat, colorMat;
        srcMat.convertTo(convMat, CV_8UC1, invDelta, -invDelta*minVal);
        cv::applyColorMap(convMat, colorMat, rasterMode);
        QImage colorImage;
        switch(colorMat.channels()){
        case 3:
            colorImage = QImage(imgDataPtr.width(), imgDataPtr.height(), QImage::Format_RGB888);
            break;
        case 4:
            colorImage = QImage(imgDataPtr.width(), imgDataPtr.height(), QImage::Format_RGBA8888);
            break;
        default:
            qDebug() << "Error: can't raster image";
        }
        memcpy(colorImage.bits(), colorMat.data, colorMat.channels() * imgDataPtr.width() * imgDataPtr.height());
        return colorImage;
    }
    else{
        QImage grayImage(imgDataPtr.width(), imgDataPtr.height(), QImage::Format_Grayscale8);

        const float *originalData = imgDataPtr.data();
        uchar * bits = grayImage.bits();

        #pragma omp parallel for
        for(int i = 0; i < maxInd; ++i){
            bits[i] = (originalData[i] - minVal) * invDelta;
        }
        return grayImage;
    }

    return QImage();
}
