#include "ImageDataLoader.h"
#include "opencv2/opencv.hpp"

using namespace cv;

ImageDataSpatial ImageDataLoader::loadFromFile(QString fileName){
    Mat floatImg, scrImage = imread(fileName.toStdString(), CV_LOAD_IMAGE_ANYDEPTH );
    scrImage.convertTo(floatImg, CV_32FC1);
    ImageDataSpatial imgData(floatImg.cols, floatImg.rows);
    memcpy(imgData.data(), floatImg.data, sizeof(float)*qMin((qint32)floatImg.cols*floatImg.rows, (qint32)imgData.pixelCount()));
    return imgData;
}
