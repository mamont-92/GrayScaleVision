#include "SourceImage.h"
#include "core/ImageData/ImageDataLoader.h"
#include <QDebug>

SourceImage::SourceImage() : AbstractFilter()
{
    qDebug() << "Constructor SourceImage";
    registerOutSlot("res", 0);
    setFileName("D:\\Work\\NAUCHPRIBOR\\temp\\1.tif");
}


QString SourceImage::fileName() const
{
    return m_fileName;
}

void SourceImage::setFileName(QString _fileName)
{
    m_fileName = _fileName;
    setOutSlot("res", ImageDataLoader::loadFromFile(m_fileName));
}

void SourceImage::update()
{
    qDebug() << "SourceImage::update";
}
