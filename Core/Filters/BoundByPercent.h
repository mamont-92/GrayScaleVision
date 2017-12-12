#ifndef BoundByPercent_H
#define BoundByPercent_H

#include "Core/AbstractFilter.h"
#include "Core/Params/RealParameter.h"

class BoundByPercent : public AbstractFilter
{
public:
    BoundByPercent();
    void update();
    RealParameter minPercent, maxPercent;
    DECLARE_READABLE_NAME("BoundByPercent")
};
REGISTER_FILTER(BoundByPercent, 1, 1)


#endif // ADDWEIGHTED_H
