QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/debug
}
else {
    DESTDIR = $$PWD/release
}


DEFINES += MVVM_MODEL_STATIC_DEFINE \
    MVVM_VIEW_STATIC_DEFINE \
    MVVM_VIEWMODEL_STATIC_DEFINE

INCLUDEPATH += \
$$PWD/source/libmvvm_model \
$$PWD/source/libmvvm_view \
$$PWD/source/libmvvm_viewmodel \
$$PWD/mples/modelinqml \
$$PWD/thirdparty/qcustomplot \
$$PWD/thirdparty/gtest/googletest/googletest/include  \
$$PWD/examples/treeviews \
$$PWD/examples/dragandmove \
$$PWD/autogen/mvvm

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



CONFIG(debug, debug|release) {
    LIBS+= -L"$$PWD/lib/debug" -lqtMvvm
}
else {
    LIBS+= -L"$$PWD/lib/release" -lqtMvvm
}

TEMPLATE = app

SOURCES += \
examples/nodeeditor/nodeeditorcore/connectableitem.cpp \
examples/nodeeditor/nodeeditorcore/connectableitemcontroller.cpp \
examples/nodeeditor/nodeeditorcore/connectableview.cpp \
examples/nodeeditor/nodeeditorcore/graphicsscene.cpp \
examples/nodeeditor/nodeeditorcore/graphicsscenecontroller.cpp \
examples/nodeeditor/nodeeditorcore/graphicsview.cpp \
examples/nodeeditor/nodeeditorcore/mainwindow.cpp \
examples/nodeeditor/nodeeditorcore/modeleditorwidget.cpp \
examples/nodeeditor/nodeeditorcore/nodeconnection.cpp \
examples/nodeeditor/nodeeditorcore/nodecontroller.cpp \
examples/nodeeditor/nodeeditorcore/nodeport.cpp \
examples/nodeeditor/nodeeditorcore/pieceslist.cpp \
examples/nodeeditor/nodeeditorcore/propertywidget.cpp \
examples/nodeeditor/nodeeditorcore/sampleitems.cpp \
examples/nodeeditor/nodeeditorcore/samplemodel.cpp \
examples/nodeeditor/main.cpp \
examples/nodeeditor/nodeeditorcore/sceneutils.cpp

HEADERS += \
examples/nodeeditor/nodeeditorcore/connectableitem.h \
examples/nodeeditor/nodeeditorcore/connectableitemcontroller.h \
examples/nodeeditor/nodeeditorcore/connectableview.h \
examples/nodeeditor/nodeeditorcore/graphicsscene.h \
examples/nodeeditor/nodeeditorcore/graphicsscenecontroller.h \
examples/nodeeditor/nodeeditorcore/graphicsview.h \
examples/nodeeditor/nodeeditorcore/mainwindow.h \
examples/nodeeditor/nodeeditorcore/modeleditorwidget.h \
examples/nodeeditor/nodeeditorcore/nodeconnection.h \
examples/nodeeditor/nodeeditorcore/nodecontroller.h \
examples/nodeeditor/nodeeditorcore/nodeport.h \
examples/nodeeditor/nodeeditorcore/pieceslist.h \
examples/nodeeditor/nodeeditorcore/portinfo.h \
examples/nodeeditor/nodeeditorcore/propertywidget.h \
examples/nodeeditor/nodeeditorcore/sampleitems.h \
examples/nodeeditor/nodeeditorcore/samplemodel.h \
examples/nodeeditor/nodeeditorcore/sceneutils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
