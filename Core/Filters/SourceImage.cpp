#include "SourceImage.h"
#include "core/ImageData/ImageDataLoader.h"
#include <QDebug>

SourceImage::SourceImage() : AbstractFilter()
{
    registerOutSlot("res", 0);
    registerParameter("path", &path);
}


void SourceImage::update()
{
    if(m_oldPath != path.value().toString()){
        clearOutSlots();
        m_oldPath = path.value().toString();
        setOutSlot("res", ImageDataLoader::loadFromFile(m_oldPath));
    }
}
