#ifndef Convolution3x3_H
#define Convolution3x3_H

#include "Core/AbstractFilter.h"
#include "Core/Params/Matrix3x3Parameter.h"

class Convolution3x3 : public AbstractFilter
{
public:
    Convolution3x3();

    Matrix3x3Parameter matrix;

    void update();
    DECLARE_READABLE_NAME("Convolution 3x3")
};
REGISTER_FILTER(Convolution3x3, 1, 1)


#endif // Convolution3x3_H
