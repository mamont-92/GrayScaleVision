#ifndef SourceImage_H
#define SourceImage_H

#include "Core/AbstractFilter.h"
#include "Core/Params/StringParameter.h"

class SourceImage : public AbstractFilter
{
public:
    SourceImage();    
    StringParameter path;

    void update();
    DECLARE_READABLE_NAME("SourceImage")
private:
    QString m_oldPath;
};
REGISTER_FILTER(SourceImage, 0, 1)


#endif // SourceImage_H
