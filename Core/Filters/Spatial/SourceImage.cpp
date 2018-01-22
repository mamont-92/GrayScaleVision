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

        auto outSlotPtr = outSlot("res");
        auto outDataPtr = outSlotPtr->asSpatialData();

        if(newImg.isEmpty())
            outDataPtr->setEmpty();
        else
            outDataPtr->setDataWithCopy(newImg.data(), newImg.size());

        outSlotPtr->setSpatialChanged();
    }
}
