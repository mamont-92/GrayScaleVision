#ifndef ADDWEIGHTED_H
#define ADDWEIGHTED_H

#include "Core/AbstractFilter.h"
#include "Core/Params/RealParameter.h"

class AddWeighted : public AbstractFilter
{
public:
    AddWeighted();
    void update();
    RealParameter alpha, beta, gamma;
    DECLARE_READABLE_NAME("add weighted")
};
REGISTER_FILTER(AddWeighted, 2, 1)

#endif // ADDWEIGHTED_H
