#ifndef Laplacian_H
#define Laplacian_H

#include "Core/AbstractFilter.h"
#include "Core/Params/IntegerParameter.h"

class Laplacian : public AbstractFilter
{
public:
    Laplacian();

    IntegerParameter kernelSize;

    void update();

    DECLARE_READABLE_NAME("Laplacian")
};
REGISTER_FILTER(Laplacian, 1, 1)


#endif // Laplacian_H
