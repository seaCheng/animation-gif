QT       += core gui core5compat
QT += openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../bin
UI_DIR = $$PWD/../bin/temp/ui
MOC_DIR = $$PWD/../bin/temp/moc
OBJECTS_DIR = $$PWD/../bin/temp/obj

CONFIG += c++17

include  (./../AMLogger/AMLogger.pri);
include  (./../gifdec/gifdec.pri);

include  (./../qt-mvvm/qt-mvvms.pri);

include  (./../gifOpe/gifOpe.pri);
include  (./../QtSingleApplication/qtsingleapplication.pri);


INCLUDEPATH += \
$$PWD/../qt-mvvm/source/libmvvm_model \
$$PWD/../qt-mvvm/source/libmvvm_view \
$$PWD/../qt-mvvm/source/libmvvm_viewmodel \
$$PWD/../qt-mvvm/autogen/mvvm

CONFIG(debug, debug|release) {
    #LIBS+= -L"$$PWD/../lib/debug" -lqtMvvm
}
else {
    #LIBS+= -L"$$PWD/../lib/release" -lqtMvvm
}

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
$$PWD/viewComponent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
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
    viewComponent/aspectRatioPixmapLabel.cpp \
    titleBar/framelesswindow.cpp \
    viewComponent/picScaleComp.cpp \
    viewComponent/picScaleViewComp.cpp

HEADERS += \
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
    titleBar/OSXHideTitleBar.h \
    titleBar/framelesswindow.h \
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
    LIBS += -framework Cocoa

    SOURCES += \
    titleBar/OSXHideTitleBar.mm \
    titleBar/framelesswindow.mm \

}
macx {
DEFINES += PLUGIN_LIBRARY
QMAKE_INFO_PLIST = macos/Info.plist
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14

QMAKE_POST_LINK = \
        rm -rf ./../bin/animation.app/Contents/MacOS/resource && \
        cp -avf ./../bin/resource ./../bin/animation.app/Contents/MacOS/resource && \
        mkdir -p ./../bin/animation.app/Contents/Frameworks && \
        rm -rf ./../bin/animation.app/Contents/Frameworks/SDL2.framework && \
        cp -avf ./../lib/SDL/lib/SDL2.framework  ./../bin/animation.app/Contents/Frameworks
}
