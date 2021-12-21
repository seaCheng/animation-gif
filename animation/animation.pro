QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include  (./../AMLogger/AMLogger.pri);
include  (./../QtSingleApplication/qtsingleapplication.pri);

INCLUDEPATH += \
$$PWD/graphicsComponent \
$$PWD/../AMLogger \
$$PWD/../QtSingleApplication \
$$PWD/viewComponent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphicsComponent/graphicsViewComp.cpp \
    main.cpp \
    mainwindow.cpp \
    viewComponent/aspectRatioPixmapLabel.cpp \
    viewComponent/picScaleComp.cpp \
    viewComponent/picScaleViewComp.cpp

HEADERS += \
    graphicsComponent/graphicsViewComp.h \
    mainwindow.h \
    viewComponent/aspectRatioPixmapLabel.h \
    viewComponent/picScaleComp.h \
    viewComponent/picScaleViewComp.h

FORMS += \
    ui/animationMW.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RC_ICONS = $$PWD/resource/app.ico

macx {
DEFINES += PLUGIN_LIBRARY
QMAKE_INFO_PLIST = macos/Info.plist
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

QMAKE_POST_LINK = \
        rm -rf animation.app/Contents/MacOS/resource && \
        cp -avf resource animation.app/Contents/MacOS/resource
}
