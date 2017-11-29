#ifndef GLOBALCONTEXT_H
#define GLOBALCONTEXT_H

#include "FilterManagerBackend.h"
#include "RasterImageProvider.h"

class GlobalContext // no singleton for FilterManagerBackend because of going to do many tabs with many managers
{
public:
    static GlobalContext& instance(){
        static GlobalContext _instance;
        return _instance;
    }
    FilterManagerBackend * filterManager();
    RasterImageProvider * imageProvider(); // TO DO: add const
private:
    GlobalContext();
    GlobalContext(GlobalContext const&);
    void operator=(GlobalContext const&);

    FilterManagerBackend * m_filterManager;
    RasterImageProvider * m_imageProvider;
};

#endif // GLOBALCONTEXT_H
