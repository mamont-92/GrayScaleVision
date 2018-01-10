#ifndef Circle_H
#define Circle_H

#include "Core/AbstractFilter.h"
#include "Core/Params/RealParameter.h"

class Circle : public AbstractFilter
{
public:
    Circle();
    void update();
    RealParameter minPercent, maxPercent;
    DECLARE_READABLE_NAME("Circle")
};
REGISTER_FILTER(Circle, 1, 1)


#endif // ADDWEIGHTED_H
