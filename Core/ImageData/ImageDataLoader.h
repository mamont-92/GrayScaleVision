#ifndef IMAGEDATALOADER_H
#define IMAGEDATALOADER_H

#include "ImageDataSpatial.h"
#include <QString>

class ImageDataLoader
{
public:
static ImageDataSpatial loadFromFile(QString fileName);
};

#endif // IMAGEDATALOADER_H
