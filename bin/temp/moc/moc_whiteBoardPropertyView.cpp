/****************************************************************************
** Meta object code from reading C++ file 'whiteBoardPropertyView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../animation/tabPropertyTable/whiteBoardProperty/whiteBoardPropertyView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'whiteBoardPropertyView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WhiteBoardPropertyView_t {
    uint offsetsAndSizes[34];
    char stringdata0[23];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[21];
    char stringdata5[16];
    char stringdata6[23];
    char stringdata7[20];
    char stringdata8[21];
    char stringdata9[19];
    char stringdata10[17];
    char stringdata11[7];
    char stringdata12[19];
    char stringdata13[2];
    char stringdata14[16];
    char stringdata15[20];
    char stringdata16[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_WhiteBoardPropertyView_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_WhiteBoardPropertyView_t qt_meta_stringdata_WhiteBoardPropertyView = {
    {
        QT_MOC_LITERAL(0, 22),  // "WhiteBoardPropertyView"
        QT_MOC_LITERAL(23, 17),  // "s_sceneItemInsert"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 11),  // "DiagramType"
        QT_MOC_LITERAL(54, 20),  // "s_whiteBoardProFresh"
        QT_MOC_LITERAL(75, 15),  // "refreashProType"
        QT_MOC_LITERAL(91, 22),  // "s_saveToCurrentPicture"
        QT_MOC_LITERAL(114, 19),  // "s_saveToAllPictures"
        QT_MOC_LITERAL(134, 20),  // "s_clearGraphicsItems"
        QT_MOC_LITERAL(155, 18),  // "buttonGroupClicked"
        QT_MOC_LITERAL(174, 16),  // "QAbstractButton*"
        QT_MOC_LITERAL(191, 6),  // "button"
        QT_MOC_LITERAL(198, 18),  // "currentFontChanged"
        QT_MOC_LITERAL(217, 1),  // "f"
        QT_MOC_LITERAL(219, 15),  // "fontSizeChanged"
        QT_MOC_LITERAL(235, 19),  // "textButtonTriggered"
        QT_MOC_LITERAL(255, 16)   // "textColorChanged"
    },
    "WhiteBoardPropertyView",
    "s_sceneItemInsert",
    "",
    "DiagramType",
    "s_whiteBoardProFresh",
    "refreashProType",
    "s_saveToCurrentPicture",
    "s_saveToAllPictures",
    "s_clearGraphicsItems",
    "buttonGroupClicked",
    "QAbstractButton*",
    "button",
    "currentFontChanged",
    "f",
    "fontSizeChanged",
    "textButtonTriggered",
    "textColorChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WhiteBoardPropertyView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    1,   77,    2, 0x06,    3 /* Public */,
       6,    0,   80,    2, 0x06,    5 /* Public */,
       7,    0,   81,    2, 0x06,    6 /* Public */,
       8,    0,   82,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   83,    2, 0x0a,    8 /* Public */,
      12,    1,   86,    2, 0x0a,   10 /* Public */,
      14,    1,   89,    2, 0x0a,   12 /* Public */,
      15,    0,   92,    2, 0x0a,   14 /* Public */,
      16,    0,   93,    2, 0x0a,   15 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QFont,   13,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WhiteBoardPropertyView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WhiteBoardPropertyView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->s_sceneItemInsert((*reinterpret_cast< std::add_pointer_t<DiagramType>>(_a[1]))); break;
        case 1: _t->s_whiteBoardProFresh((*reinterpret_cast< std::add_pointer_t<refreashProType>>(_a[1]))); break;
        case 2: _t->s_saveToCurrentPicture(); break;
        case 3: _t->s_saveToAllPictures(); break;
        case 4: _t->s_clearGraphicsItems(); break;
        case 5: _t->buttonGroupClicked((*reinterpret_cast< std::add_pointer_t<QAbstractButton*>>(_a[1]))); break;
        case 6: _t->currentFontChanged((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 7: _t->fontSizeChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->textButtonTriggered(); break;
        case 9: _t->textColorChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DiagramType >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< refreashProType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WhiteBoardPropertyView::*)(DiagramType );
            if (_t _q_method = &WhiteBoardPropertyView::s_sceneItemInsert; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WhiteBoardPropertyView::*)(refreashProType );
            if (_t _q_method = &WhiteBoardPropertyView::s_whiteBoardProFresh; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WhiteBoardPropertyView::*)();
            if (_t _q_method = &WhiteBoardPropertyView::s_saveToCurrentPicture; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WhiteBoardPropertyView::*)();
            if (_t _q_method = &WhiteBoardPropertyView::s_saveToAllPictures; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WhiteBoardPropertyView::*)();
            if (_t _q_method = &WhiteBoardPropertyView::s_clearGraphicsItems; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject WhiteBoardPropertyView::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_WhiteBoardPropertyView.offsetsAndSizes,
    qt_meta_data_WhiteBoardPropertyView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_WhiteBoardPropertyView_t
, QtPrivate::TypeAndForceComplete<WhiteBoardPropertyView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DiagramType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<refreashProType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAbstractButton *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QFont &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *WhiteBoardPropertyView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WhiteBoardPropertyView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WhiteBoardPropertyView.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int WhiteBoardPropertyView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void WhiteBoardPropertyView::s_sceneItemInsert(DiagramType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WhiteBoardPropertyView::s_whiteBoardProFresh(refreashProType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WhiteBoardPropertyView::s_saveToCurrentPicture()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WhiteBoardPropertyView::s_saveToAllPictures()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WhiteBoardPropertyView::s_clearGraphicsItems()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
