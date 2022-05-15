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
    main.cpp \
    spotwidget.cpp \
    system/CMatrix.cpp \
    system/Image_Plane.cpp \
    system/Object_Plane.cpp \
    system/SMatrix.cpp \
    system/Standard.cpp \
    system/system.cpp \
    window/Layout2D/Layout2D.cpp \
    window/Layout2D/Paint2D.cpp \
    window/LensDataEditor/LensDataEditor.cpp \
    window/LensDataEditor/SurfaceProperties.cpp \
    window/MainWindow/MainWindow.cpp

HEADERS += \
    spotwidget.h \
    system/CMatrix.h \
    system/Image_Plane.h \
    system/Object_Plane.h \
    system/SMatrix.h \
    system/Standard.h \
    system/system.h \
    window/Layout2D/Layout2D.h \
    window/Layout2D/Paint2D.h \
    window/LensDataEditor/LensDataEditor.h \
    window/LensDataEditor/SurfaceProperties.h \
    window/MainWindow/MainWindow.h

FORMS += \
    spotwidget.ui \
    window/Layout2D/Layout2D.ui \
    window/LensDataEditor/LensDataEditor.ui \
    window/LensDataEditor/SurfaceProperties.ui \
    window/MainWindow/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
