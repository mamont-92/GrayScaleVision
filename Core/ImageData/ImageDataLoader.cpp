#include "ImageDataLoader.h"
#include <QDebug>
#include "opencv2/opencv.hpp"

using namespace cv;

ImageDataSpatial ImageDataLoader::loadFromFile(QString fileName){
    Mat floatImg, scrImage = imread(fileName.toStdString(), CV_LOAD_IMAGE_ANYDEPTH );
    scrImage.convertTo(floatImg, CV_32FC1);
    ImageDataSpatial imgData(floatImg.cols, floatImg.rows);
    memcpy(reinterpret_cast<uchar*>(imgData.data()), floatImg.data, sizeof(float)*floatImg.cols*floatImg.rows);
    return imgData;
}
