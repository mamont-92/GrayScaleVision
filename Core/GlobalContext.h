#ifndef GLOBALCONTEXT_H
#define GLOBALCONTEXT_H

#include "FilterProcessor.h"
#include "RasterImageProvider.h"

class GlobalContext // no singleton for FilterProcessor because of going to do many tabs with many managers
{
public:
    static GlobalContext& instance(){
        static GlobalContext _instance;
        return _instance;
    }
    FilterProcessor * filterManager();
    RasterImageProvider * imageProvider(); // TO DO: add const
private:
    GlobalContext();
    GlobalContext(GlobalContext const&);
    void operator=(GlobalContext const&);

    FilterProcessor * m_filterManager; // pointers because of destroing singleton before app destroing
    RasterImageProvider * m_imageProvider;
};

#endif // GLOBALCONTEXT_H
