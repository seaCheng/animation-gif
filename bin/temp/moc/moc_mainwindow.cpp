/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../animation/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[32];
    char stringdata0[11];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[9];
    char stringdata5[11];
    char stringdata6[15];
    char stringdata7[18];
    char stringdata8[18];
    char stringdata9[10];
    char stringdata10[10];
    char stringdata11[12];
    char stringdata12[12];
    char stringdata13[5];
    char stringdata14[12];
    char stringdata15[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 9),  // "slot_show"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 7),  // "message"
        QT_MOC_LITERAL(30, 8),  // "slot_add"
        QT_MOC_LITERAL(39, 10),  // "slot_clear"
        QT_MOC_LITERAL(50, 14),  // "slot_importGif"
        QT_MOC_LITERAL(65, 17),  // "slot_importVideos"
        QT_MOC_LITERAL(83, 17),  // "slot_FinimportGif"
        QT_MOC_LITERAL(101, 9),  // "slot_save"
        QT_MOC_LITERAL(111, 9),  // "slot_load"
        QT_MOC_LITERAL(121, 11),  // "slot_import"
        QT_MOC_LITERAL(133, 11),  // "type_import"
        QT_MOC_LITERAL(145, 4),  // "type"
        QT_MOC_LITERAL(150, 11),  // "slot_export"
        QT_MOC_LITERAL(162, 24)   // "slot_refreashPicItemView"
    },
    "MainWindow",
    "slot_show",
    "",
    "message",
    "slot_add",
    "slot_clear",
    "slot_importGif",
    "slot_importVideos",
    "slot_FinimportGif",
    "slot_save",
    "slot_load",
    "slot_import",
    "type_import",
    "type",
    "slot_export",
    "slot_refreashPicItemView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x0a,    1 /* Public */,
       4,    0,   83,    2, 0x0a,    3 /* Public */,
       5,    0,   84,    2, 0x0a,    4 /* Public */,
       6,    0,   85,    2, 0x0a,    5 /* Public */,
       7,    0,   86,    2, 0x0a,    6 /* Public */,
       8,    0,   87,    2, 0x0a,    7 /* Public */,
       9,    0,   88,    2, 0x0a,    8 /* Public */,
      10,    0,   89,    2, 0x0a,    9 /* Public */,
      11,    1,   90,    2, 0x0a,   10 /* Public */,
      14,    0,   93,    2, 0x0a,   12 /* Public */,
      15,    0,   94,    2, 0x0a,   13 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slot_show((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->slot_add(); break;
        case 2: _t->slot_clear(); break;
        case 3: _t->slot_importGif(); break;
        case 4: _t->slot_importVideos(); break;
        case 5: _t->slot_FinimportGif(); break;
        case 6: _t->slot_save(); break;
        case 7: _t->slot_load(); break;
        case 8: _t->slot_import((*reinterpret_cast< std::add_pointer_t<type_import>>(_a[1]))); break;
        case 9: _t->slot_export(); break;
        case 10: _t->slot_refreashPicItemView(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< type_import >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<CFramelessWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<type_import, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return CFramelessWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CFramelessWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
