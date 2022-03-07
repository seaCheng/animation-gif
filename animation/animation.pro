QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../bin

CONFIG += c++17

include  (./../AMLogger/AMLogger.pri);
include  (./../gifdec/gifdec.pri);

include  (./../qt-mvvm/qt-mvvms.pri);

include  (./../BurstLinker/BurstLinker.pri);
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
INCLUDEPATH += \
$$PWD/graphicsComponent \
$$PWD/../AMLogger \
$$PWD/../gifdec \
$$PWD/../lib/SDL/include \
$$PWD/../QtSingleApplication \
$$PWD/viewComponent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphicsComponent/graphicsViewComp.cpp \
    main.cpp \
    mainwindow.cpp \
    modelController.cpp \
    pictureItem.cpp \
    pictureItemcontroller.cpp \
    pictureModel.cpp \
    viewComponent/aspectRatioPixmapLabel.cpp \
    viewComponent/picScaleComp.cpp \
    viewComponent/picScaleViewComp.cpp

HEADERS += \
    graphicsComponent/graphicsViewComp.h \
    mainwindow.h \
    modelController.h \
    pictureItem.h \
    pictureItemcontroller.h \
    pictureModel.h \
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
        rm -rf ./../bin/animation.app/Contents/MacOS/resource && \
        cp -avf ./resource ./../bin/animation.app/Contents/MacOS/resource && \
        mkdir -p ./../bin/animation.app/Contents/Frameworks && \
        rm -rf ./../bin/animation.app/Contents/Frameworks/SDL2.framework && \
        cp -avf ./../lib/SDL/lib/SDL2.framework  ./../bin/animation.app/Contents/Frameworks
}

