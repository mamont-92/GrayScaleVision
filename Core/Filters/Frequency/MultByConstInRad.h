#ifndef MultByConstInRad_H
#define MultByConstInRad_H

#include "Core/AbstractFilter.h"
#include "Core/Params/RealParameter.h"
#include "Core/Params/IntegerParameter.h"

class MultByConstInRad : public AbstractFilter
{
public:
    MultByConstInRad();
    void update();
    RealParameter multiplier;
    IntegerParameter radius;
    DECLARE_READABLE_NAME("Mult by const")
};
REGISTER_FILTER(MultByConstInRad, 1, 1)


#endif // ADDWEIGHTED_H
