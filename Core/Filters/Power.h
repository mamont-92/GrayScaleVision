#ifndef Power_H
#define Power_H

#include "Core/AbstractFilter.h"

class Power : public AbstractFilter
{
public:
    Power();
    void update();
    DECLARE_READABLE_NAME("power")
};
REGISTER_FILTER(Power, 1, 1)


#endif // Power_H
