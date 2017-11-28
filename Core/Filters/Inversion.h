#ifndef Inversion_H
#define Inversion_H

#include "Core/AbstractFilter.h"

class Inversion : public AbstractFilter
{
public:
    Inversion();
    void update();
    DECLARE_READABLE_NAME("inversion")
};
REGISTER_FILTER(Inversion, 1, 1)


#endif // ADDWEIGHTED_H
