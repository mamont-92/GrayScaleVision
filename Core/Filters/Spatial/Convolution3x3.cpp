#include "Convolution3x3.h"

float defaultMatData[]={-0.125f, -0.125f, -0.125f,
                        -0.125f,  2.0f  , -0.125f,
                        -0.125f, -0.125f, -0.125f};


Convolution3x3::Convolution3x3() : AbstractFilter(),
    matrix(QMatrix3x3(defaultMatData))
{
    registerInSlot("src", 0);
    registerOutSlot("res", 0);
    registerParameter("matrix", &matrix);
}

void Convolution3x3::update()
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

    outDataPtr->resize(inDataPtr->size());

    float * inRawData = inDataPtr->data();
    float * outRawData = outDataPtr->data();

    float minVal, maxVal;
    inDataPtr->calcMinMax(minVal, maxVal);

    int width = inDataPtr->width(), height = inDataPtr->height();
    int beginInd = 0, endInd = width;
    #pragma omp parallel for
    for(int i = beginInd; i < endInd; ++i){ //copy first row
        outRawData[i] = inRawData[i];
    }

    beginInd = (height-1)*width, endInd = height*width;
    #pragma omp parallel for
    for(int i = beginInd; i < endInd; ++i){ //copy last row
        outRawData[i] = inRawData[i];
    }

    beginInd = 0, endInd = height*width; int delta = width - 1;
    #pragma omp parallel for
    for(int i = beginInd; i < endInd; i+=width){ //copy first and last row, together because of cache miss in any case
        outRawData[i] = inRawData[i];
        outRawData[i+delta] = inRawData[i+delta];
    }

    const float * matRawData = matrix.matValue().data();
    #pragma omp parallel for
    for(int i = 1; i < (height -1); ++i){
        for(int j = 1; j < (width -1); ++j){
            double localSum = inRawData[(i-1)*width+j-1] * matRawData[0*3+0];
            localSum+= inRawData[(i-1)*width+j] * matRawData[0*3+1];
            localSum+= inRawData[(i-1)*width+j+1] * matRawData[0*3+2];

            localSum+= inRawData[i*width+j-1] * matRawData[1*3+0];
            localSum+= inRawData[i*width+j] * matRawData[1*3+1];
            localSum+= inRawData[i*width+j+1] * matRawData[1*3+2];

            localSum+= inRawData[(i+1)*width+j-1] * matRawData[2*3+0];
            localSum+= inRawData[(i+1)*width+j] * matRawData[2*3+1];
            localSum+= inRawData[(i+1)*width+j+1] * matRawData[2*3+2];

            outRawData[i*width+j] = qBound(minVal, (float)localSum, maxVal);
        }
    }

    outSlotPtr->setSpatialChanged();
}
