#ifndef BoundByPercent_H
#define BoundByPercent_H

#include "Core/AbstractFilter.h"

class BoundByPercent : public AbstractFilter
{
public:
    BoundByPercent();
    void update();
    DECLARE_READABLE_NAME("BoundByPercent")
};
REGISTER_FILTER(BoundByPercent, 1, 1)


#endif // ADDWEIGHTED_H
