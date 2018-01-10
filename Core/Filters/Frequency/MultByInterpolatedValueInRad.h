#ifndef MultByInterpolatedValueInRad_H
#define MultByInterpolatedValueInRad_H

#include "Core/AbstractFilter.h"
#include "Core/Params/RealParameter.h"
#include "Core/Params/IntegerParameter.h"

class MultByInterpolatedValueInRad : public AbstractFilter
{
public:
    MultByInterpolatedValueInRad();
    void update();
    RealParameter value1, value2;
    IntegerParameter radius;
    DECLARE_READABLE_NAME("Mult by interpolated value")
};
REGISTER_FILTER(MultByInterpolatedValueInRad, 1, 1)


#endif // ADDWEIGHTED_H
