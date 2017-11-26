#ifndef ADDWEIGHTED_H
#define ADDWEIGHTED_H

#include "Core/AbstractFilter.h"

class AddWeighted : public AbstractFilter
{
public:
    AddWeighted();
    DECLARE_READABLE_NAME("add weighted")
};
REGISTER_FILTER(AddWeighted)

#endif // ADDWEIGHTED_H
