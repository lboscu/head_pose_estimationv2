QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    facepointdlib.cpp \
    main.cpp \
    mainwindow.cpp \
    qmatopengl.cpp

HEADERS += \
    facepointdlib.h \
    mainwindow.h \
    qmatopengl.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

################################################################################################################
#opencv配置

INCLUDEPATH += "D:\Program Files\opencv3_lib\opencv_mingw32_with_contrib\include"

LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_aruco341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_bgsegm341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_bioinspired341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_calib3d341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_ccalib341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_core341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_datasets341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_dnn_objdetect341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_dnn341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_dpm341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_face341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_features2d341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_flann341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_fuzzy341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_hfs341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_highgui341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_img_hash341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_imgcodecs341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_imgproc341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_line_descriptor341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_ml341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_objdetect341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_optflow341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_phase_unwrapping341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_photo341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_plot341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_reg341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_rgbd341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_saliency341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_shape341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_stereo341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_stitching341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_structured_light341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_superres341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_surface_matching341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_text341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_tracking341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_video341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_videoio341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_videostab341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_xfeatures2d341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_ximgproc341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_xobjdetect341.dll"
LIBS += "D:/Program Files/opencv3_lib/opencv_mingw32_with_contrib/x86/mingw/bin/libopencv_xphoto341.dll"
######################################################################################################################
RESOURCES += \
    res.qrc

######################################################################################################################
#dlib配置
SOURCES += "D:\Program Files\opencv_Dlib\dlib_uncmake\dlib-19.17\dlib\all\source.cpp"
LIBS += -lwsock32  -lws2_32 -limm32  -luser32 -lgdi32 -lcomctl32 -lwinmm

INCLUDEPATH += "D:\Program Files\opencv_Dlib\dlib_uncmake\dlib-19.17"

######################################################################################################################
# 使用 system时，隐藏窗口

