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
    clearOutSlots();

    ImageDataSpatialPtr inputDataPtr = inSlotLock("src");
    if(inputDataPtr.isNull())
        return;

    if(inputDataPtr->isEmpty())
        return;

    float * inData = inputDataPtr->data();

    ImageDataSpatialPtr resultDataPtr = ImageDataSpatialPtr::create(inputDataPtr->width(), inputDataPtr->height());
    float * outData = resultDataPtr->data();

    float minVal, maxVal;
    inputDataPtr->calcMinMax(minVal, maxVal);

    int width = inputDataPtr->width(), height = inputDataPtr->height();
    int beginInd = 0, endInd = width;
    #pragma omp parallel for
    for(int i = beginInd; i < endInd; ++i){ //copy first row
        outData[i] = inData[i];
    }

    beginInd = (height-1)*width, endInd = height*width;
    #pragma omp parallel for
    for(int i = beginInd; i < endInd; ++i){ //copy last row
        outData[i] = inData[i];
    }

    beginInd = 0, endInd = height*width; int delta = width - 1;
    #pragma omp parallel for
    for(int i = beginInd; i < endInd; i+=width){ //copy first and last row, together because of cash miss in any case
        outData[i] = inData[i];
        outData[i+delta] = inData[i+delta];
    }

    const float * matData = matrix.matValue().data();
    #pragma omp parallel for
    for(int i = 1; i < (height -1); ++i){
        for(int j = 1; j < (width -1); ++j){
            double localSum = inData[(i-1)*width+j-1] * matData[0*3+0];
            localSum+= inData[(i-1)*width+j] * matData[0*3+1];
            localSum+= inData[(i-1)*width+j+1] * matData[0*3+2];

            localSum+= inData[i*width+j-1] * matData[1*3+0];
            localSum+= inData[i*width+j] * matData[1*3+1];
            localSum+= inData[i*width+j+1] * matData[1*3+2];

            localSum+= inData[(i+1)*width+j-1] * matData[2*3+0];
            localSum+= inData[(i+1)*width+j] * matData[2*3+1];
            localSum+= inData[(i+1)*width+j+1] * matData[2*3+2];

            outData[i*width+j] = qBound(minVal, (float)localSum, maxVal);
        }
    }

    setOutSlot("res", resultDataPtr);
}
