INCLUDEPATH += $${OCV_INCLUDE_PATH}
LIBS += -L$${OCV_LIB_PATH}

CONFIG(release, debug|release) {
    LIBS += -lopencv_core331 \
    -lopencv_imgproc331 \
    -lopencv_photo331 \
    -lopencv_ml331 \
    -lopencv_imgcodecs331 \
    -lopencv_highgui331

} else:CONFIG(debug, debug|release) {
    LIBS += -lopencv_core331d \
    -lopencv_imgproc331d \
    -lopencv_photo331d \
    -lopencv_ml331d \
    -lopencv_imgcodecs331d \
    -lopencv_highgui331d 
}
