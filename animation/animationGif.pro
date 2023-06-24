QT       += core gui core5compat
QT += openglwidgets
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../bin
UI_DIR = $$PWD/../bin/temp/ui
MOC_DIR = $$PWD/../bin/temp/moc
OBJECTS_DIR = $$PWD/../bin/temp/obj

TARGET = animationGif
TEMPLATE = app

CONFIG += c++17

include (./../framelesswindow/projectinclude/common.pri)
include  (./../AMLogger/AMLogger.pri);
include  (./../gifdec/gifdec.pri);

include  (./../qt-mvvm/qt-mvvms.pri);

include  (./../gifOpe/gifOpe.pri);
include  (./../QtSingleApplication/qtsingleapplication.pri);

TR_EXCLUDE += $$PWD/../qt-mvvm/source/libmvvm_model/*
TR_EXCLUDE += $$PWD/../qt-mvvm/source/libmvvm_view/*
TR_EXCLUDE += $$PWD/../qt-mvvm/source/libmvvm_viewmodel/*
TR_EXCLUDE += $$PWD/../qt-mvvm/autogen/mvvm/*

INCLUDEPATH += \
$$PWD/../qt-mvvm/source/libmvvm_model \
$$PWD/../qt-mvvm/source/libmvvm_view \
$$PWD/../qt-mvvm/source/libmvvm_viewmodel \
$$PWD/../qt-mvvm/autogen/mvvm

INCLUDEPATH += $$PWD/../framelesswindow
DEPENDPATH += $$PWD/../framelesswindow

win32{
    LIBS+= -L"$$PWD/../lib/SDL/lib/x64" -lSDL2
}

macx {
   LIBS += -F"$$PWD/../lib/SDL/lib" -framework SDL2
}

macx {
   LIBS += -L$$PWD/../lib/ImageMaick/Mac/lib -lMagick++-7.Q16HDRI -lMagickCore-7.Q16HDRI

   INCLUDEPATH += \
   $$PWD/../lib/ImageMaick/Mac/include/ImageMagick-7
}


win32{

LIBS += -L$$PWD/../lib/ImageMaick/Win/lib -lCORE_RL_Magick++_ -lCORE_RL_MagickCore_

INCLUDEPATH += \
$$PWD/../lib/ImageMaick/Win/include
}

TR_EXCLUDE += $$PWD/../lib/ImageMaick/Win/include/*
TR_EXCLUDE += $$PWD/../lib/SDL/include/*
TR_EXCLUDE += $$PWD/../AMLogger/*

INCLUDEPATH += \
$$PWD/mainAreaComponent \
$$PWD/mainAreaComponent/scaleButton \
$$PWD/../AMLogger \
$$PWD/../gifdec \
$$PWD/../lib/SDL/include \
$$PWD/../QtSingleApplication \
$$PWD/tabPropertyTable \
$$PWD/tabPropertyTable/commonProperty \
$$PWD/tabPropertyTable/whiteBoardProperty \
$$PWD/titleBar   \
$$PWD/utils   \
$$PWD/VideoLoad   \
$$PWD/viewComponent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    VideoLoad/videoplayer.cpp \
    mainAreaComponent/emptyAreaView.cpp \
    mainAreaComponent/graphicsViewComp.cpp \
    mainAreaComponent/mainAreaView.cpp \
    mainAreaComponent/scaleButton/sacleButtonView.cpp \
    mainLaunch.cpp \
    mainwindow.cpp \
    modelController.cpp \
    pictureItem.cpp \
    pictureItemcontroller.cpp \
    pictureModel.cpp \
    tabPropertyTable/commonProperty/commonPropertyView.cpp \
    tabPropertyTable/commonProperty/gifSizeOp.cpp \
    tabPropertyTable/propertyAreaView.cpp \
    tabPropertyTable/whiteBoardProperty/arrow.cpp \
    tabPropertyTable/whiteBoardProperty/diagramitem.cpp \
    tabPropertyTable/whiteBoardProperty/diagramtextitem.cpp \
    tabPropertyTable/whiteBoardProperty/uiCanvasItemBase.cpp \
    tabPropertyTable/whiteBoardProperty/whiteBoardPropertyView.cpp \
    titleBar/QTitleBar.cpp \
    utils/dpi.cpp \
    utils/utils.cpp \
    viewComponent/aspectRatioPixmapLabel.cpp \
    viewComponent/picScaleComp.cpp \
    viewComponent/picScaleViewComp.cpp

HEADERS += \
    VideoLoad/videoplayer.h \
    mainAreaComponent/emptyAreaView.h \
    mainAreaComponent/graphicsViewComp.h \
    mainAreaComponent/mainAreaView.h \
    mainAreaComponent/scaleButton/sacleButtonView.h \
    mainwindow.h \
    modelController.h \
    pictureItem.h \
    pictureItemcontroller.h \
    pictureModel.h \
    tabPropertyTable/commonProperty/commonPropertyView.h \
    tabPropertyTable/commonProperty/gifSizeOp.h \
    tabPropertyTable/propertyAreaView.h \
    tabPropertyTable/whiteBoardProperty/arrow.h \
    tabPropertyTable/whiteBoardProperty/diagramitem.h \
    tabPropertyTable/whiteBoardProperty/diagramtextitem.h \
    tabPropertyTable/whiteBoardProperty/uiCanvasItemBase.h \
    tabPropertyTable/whiteBoardProperty/whiteBoardPropertyView.h \ 
    titleBar/QTitleBar.h \
    utils/dpi.h \
    utils/utils.h \
    viewComponent/aspectRatioPixmapLabel.h \
    viewComponent/picScaleComp.h \
    viewComponent/picScaleViewComp.h

FORMS += \
    ui/animationMW.ui \
    ui/titleBar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RC_ICONS = $$PWD/resource/app.ico


QMAKE_INFO_PLIST = $$PWD/macos/Info.plist

macx {
DEFINES += PLUGIN_LIBRARY

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

QMAKE_POST_LINK = \
        rm -rf ./../bin/animationGif.app/Contents/MacOS/resource && \
        cp -avf ./../bin/resource ./../bin/animationGif.app/Contents/MacOS/resource && \
        mkdir -p ./../bin/animationGif.app/Contents/Frameworks && \
        rm -rf ./../bin/animationGif.app/Contents/Frameworks/SDL2.framework && \
        cp -avf ./../lib/SDL/lib/SDL2.framework  ./../bin/animationGif.app/Contents/Frameworks
}

VERSION = 1.0.0

TRANSLATIONS += \
    $$PWD/language/animationGif_ch.ts \
    $$PWD/language/animationGif_en_US.ts


