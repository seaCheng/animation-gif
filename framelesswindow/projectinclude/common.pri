
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = framelesswindow
#TEMPLATE = lib
#CONFIG += staticlib

HEADERS += \
    $$PWD/../framelesswindow.h

win32{
	SOURCES += \
                $$PWD/../framelesswindow.cpp
}
macx{
    OBJECTIVE_SOURCES += \
                $$PWD/../framelesswindow.mm
}

macx{
    LIBS += -framework Cocoa
}
