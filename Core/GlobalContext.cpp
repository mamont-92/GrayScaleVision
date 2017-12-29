#include "GlobalContext.h"

GlobalContext::GlobalContext()
{
    m_filterManager = new FilterProcessor;
    m_imageProvider = new RasterImageProvider;
}

FilterProcessor * GlobalContext::filterManager()
{
    return m_filterManager;
}

RasterImageProvider * GlobalContext::imageProvider()
{
    return m_imageProvider;
}



