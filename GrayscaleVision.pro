#-------------------------------------------------
#
# Project created by QtCreator 2017-11-10T14:47:36
#
#-------------------------------------------------

QT       += core gui quickwidgets qml quick concurrent
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GrayscaleVision
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(dependencies.pri)
include(OpenCV.pri)
include(OpenMP.pri)



SOURCES += main.cpp \
    Core/FilterCreator.cpp \
    Core/AbstractFilter.cpp \
    Core/Filters/Spatial/AddWeighted.cpp \
    Core/Filters/Spatial/Inversion.cpp \
    Core/ImageData/ImageDataSpatial.cpp \
    Core/Filters/Spatial/SourceImage.cpp \
    Core/ImageData/ImageDataLoader.cpp \
    Core/ImageData/ImageDataRasterizer.cpp \
    Core/RasterImageProvider.cpp \
    Core/GlobalContext.cpp \
    Core/Filters/Spatial/CLAHE.cpp \
    Core/Filters/Spatial/BoundByPercent.cpp \
    Core/Params/IntegerParameter.cpp \
    Core/AbstractParameter.cpp \
    Core/Filters/Spatial/Power.cpp \
    Core/Params/StringParameter.cpp \
    Core/Params/Matrix3x3Parameter.cpp \
    Core/Filters/Spatial/Convolution3x3.cpp \
    Core/Filters/Spatial/BilateralBlur.cpp \
    Core/Params/RealParameter.cpp \
    Core/Filters/Spatial/Laplacian.cpp \
    FileIO/JsonFileIO.cpp \
    Core/FilterProcessor.cpp \
    Core/FilterProcessorGate.cpp \
    Core/Commands.cpp \
    Core/CommandCallBackAcceptor.cpp \
    Core/ImageData/ImageDataFrequency.cpp \
    Core/ImageData/ImageDataConvertor.cpp \
    Core/Filters/Frequency/MultByConstInRad.cpp \
    Core/Filters/Frequency/MultByInterpolatedValueInRad.cpp \
    Core/Slot.cpp

HEADERS  += \
    Core/FilterCreator.h \
    Core/AbstractFilter.h \
    Core/Filters/Spatial/AddWeighted.h \
    Core/Filters/Spatial/Inversion.h \
    Core/BaseFilters.h \
    Core/ImageData/ImageDataSpatial.h \
    Core/Filters/Spatial/SourceImage.h \
    Core/ImageData/ImageDataLoader.h \
    Core/ImageData/ImageDataRasterizer.h \
    Core/RasterImageProvider.h \
    Core/GlobalContext.h \
    Core/Filters/Spatial/CLAHE.h \
    Core/Filters/Spatial/BoundByPercent.h \
    Core/Params/IntegerParameter.h \
    Core/AbstractParameter.h \
    Core/Filters/Spatial/Power.h \
    Core/Params/StringParameter.h \
    Core/Params/Matrix3x3Parameter.h \
    Core/Filters/Spatial/Convolution3x3.h \
    Core/Filters/Spatial/BilateralBlur.h \
    Core/Params/RealParameter.h \
    Core/Filters/Spatial/Laplacian.h \
    FileIO/JsonFileIO.h \
    Core/FilterProcessorGate.h \
    Core/FilterProcessor.h \
    Core/Commands.h \
    Core/CommandCallBackAcceptor.h \
    Core/ImageData/ImageDataFrequency.h \
    Core/ImageData/ImageDataConvertor.h \
    Core/Filters/Frequency/MultByConstInRad.h \
    Core/Filters/Frequency/MultByInterpolatedValueInRad.h \
    Core/Slot.h \
    Core/Filters/FrequencyAll.h \
    Core/Filters/SpatialAll.h

FORMS    +=

RESOURCES += \
    main.qrc

DISTFILES += \
    README.md
