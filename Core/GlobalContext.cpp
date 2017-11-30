#include "GlobalContext.h"

GlobalContext::GlobalContext()
{
    m_filterManager = new FilterManagerBackend;
    m_imageProvider = new RasterImageProvider;
}

FilterManagerBackend * GlobalContext::filterManager()
{
    return m_filterManager;
}

RasterImageProvider * GlobalContext::imageProvider()
{
    return m_imageProvider;
}



