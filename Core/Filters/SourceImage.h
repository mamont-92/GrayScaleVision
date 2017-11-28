#ifndef SourceImage_H
#define SourceImage_H

#include "Core/AbstractFilter.h"

class SourceImage : public AbstractFilter
{
public:
    SourceImage();
    void update();
    DECLARE_READABLE_NAME("SourceImage")
};
REGISTER_FILTER(SourceImage, 0, 1)


#endif // SourceImage_H
