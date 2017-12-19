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
        m_oldPath = path.value().toString();
        auto newImg = ImageDataLoader::loadFromFile(m_oldPath);
        if(newImg.isNull() || newImg->isEmpty())
            outSlot("res")->setEmpty();
        else
            outSlot("res")->setWithCopyData(newImg->data(), newImg->size());
    }
}
