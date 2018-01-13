#ifndef Power_H
#define Power_H

#include "Core/AbstractFilter.h"
#include "Core/Params/RealParameter.h"

class Power : public AbstractFilter
{
public:
    Power();
    void update();
    RealParameter power;
    DECLARE_READABLE_NAME("Power")
};
REGISTER_FILTER(Power, 1, 1)


#endif // Power_H
