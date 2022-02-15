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
$$PWD/examples/flateditor \
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
examples/flateditor/flateditorcore/demowidget.cpp \
examples/flateditor/flateditorcore/mainwindow.cpp \
examples/flateditor/flateditorcore/sampleitems.cpp \
examples/flateditor/main.cpp \
examples/flateditor/flateditorcore/samplemodel.cpp

HEADERS += \
examples/flateditor/flateditorcore/demowidget.h \
examples/flateditor/flateditorcore/mainwindow.h \
examples/flateditor/flateditorcore/sampleitems.h \
examples/flateditor/flateditorcore/samplemodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
