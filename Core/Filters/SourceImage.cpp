#include "SourceImage.h"
#include "core/ImageData/ImageDataLoader.h"
#include <QDebug>

SourceImage::SourceImage() : AbstractFilter()
{
    qDebug() << "Constructor SourceImage";
    registerOutSlot("res", 0);
    registerParameter("path", &path);
    //setFileName("D:\\Work\\NAUCHPRIBOR\\temp\\1.tif");
    //setFileName("C:\\Work\\scan\\1.tif");
}


void SourceImage::update()
{
    qDebug() << "SourceImage::update";
    if(m_oldPath != path.value().toString()){
        qDebug() << "SourceImage::LOAD";
        m_oldPath = path.value().toString();
        setOutSlot("res", ImageDataLoader::loadFromFile(m_oldPath));
    }
}
