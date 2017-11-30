#ifndef CLAHE_H
#define CLAHE_H

#include "Core/AbstractFilter.h"

class CLAHE : public AbstractFilter
{
public:
    CLAHE();
    void update();
    DECLARE_READABLE_NAME("CLAHE")
};
REGISTER_FILTER(CLAHE, 1, 1)


#endif // CLAHE_H
