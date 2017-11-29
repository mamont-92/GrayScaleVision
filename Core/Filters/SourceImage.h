#ifndef SourceImage_H
#define SourceImage_H

#include "Core/AbstractFilter.h"

class SourceImage : public AbstractFilter
{
public:
    SourceImage();
    QString fileName() const;
    void setFileName(QString _fileName);

    void update();
    DECLARE_READABLE_NAME("SourceImage")
private:
    QString m_fileName;
};
REGISTER_FILTER(SourceImage, 0, 1)


#endif // SourceImage_H
