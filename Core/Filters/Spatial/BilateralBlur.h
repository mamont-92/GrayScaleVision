#ifndef BilateralBlur_H
#define BilateralBlur_H

#include "Core/AbstractFilter.h"
#include "Core/Params/IntegerParameter.h"

class BilateralBlur : public AbstractFilter
{
public:
    BilateralBlur();
    IntegerParameter sigmaIntensity, sigmaSpace;
    void update();
    DECLARE_READABLE_NAME("BilateralBlur")
};
REGISTER_FILTER(BilateralBlur, 1, 1)


#endif // BilateralBlur_H
