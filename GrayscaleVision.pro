#-------------------------------------------------
#
# Project created by QtCreator 2017-11-10T14:47:36
#
#-------------------------------------------------

QT       += core gui quickwidgets qml quick
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


SOURCES += main.cpp \
    Core/FilterManagerBackend.cpp \
    Core/FilterCreator.cpp \
    Core/AbstractFilter.cpp \
    Core/Filters/AddWeighted.cpp \
    Core/Filters/Inversion.cpp \
    Core/ImageData/ImageDataSpatial.cpp \
    Core/Filters/SourceImage.cpp \
    Core/ImageData/ImageDataLoader.cpp \
    Core/ImageData/ImageDataRasterizer.cpp

HEADERS  += \
    Core/FilterManagerBackend.h \
    Core/FilterCreator.h \
    Core/AbstractFilter.h \
    Core/Filters/AddWeighted.h \
    Core/Filters/Inversion.h \
    Core/BaseFilters.h \
    Core/ImageData/ImageDataSpatial.h \
    Core/Filters/SourceImage.h \
    Core/ImageData/ImageDataLoader.h \
    Core/ImageData/ImageDataRasterizer.h

FORMS    +=

RESOURCES += \
    main.qrc
