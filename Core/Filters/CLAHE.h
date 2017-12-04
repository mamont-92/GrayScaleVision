#ifndef CLAHE_H
#define CLAHE_H

#include "Core/AbstractFilter.h"
#include "Core/Params/IntegerParameter.h"

class CLAHE : public AbstractFilter
{
public:
    CLAHE();
    IntegerParameter clipCount, tileSize;
    void update();
    DECLARE_READABLE_NAME("CLAHE")
};
REGISTER_FILTER(CLAHE, 1, 1)


#endif // CLAHE_H
