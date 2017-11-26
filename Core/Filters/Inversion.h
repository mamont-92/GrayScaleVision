#ifndef Inversion_H
#define Inversion_H

#include "Core/AbstractFilter.h"

class Inversion : public AbstractFilter
{
public:
    Inversion();

    DECLARE_READABLE_NAME("inversion")
};
REGISTER_FILTER(Inversion)


#endif // ADDWEIGHTED_H
