#include "SourceImage.h"
#include <QDebug>

SourceImage::SourceImage() : AbstractFilter()
{
    qDebug() << "Constructor SourceImage";
    registerOutSlot("res", 0);
}

void SourceImage::update()
{
    qDebug() << "SourceImage::update";
}
