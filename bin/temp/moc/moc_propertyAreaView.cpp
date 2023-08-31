/****************************************************************************
** Meta object code from reading C++ file 'propertyAreaView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../animation/tabPropertyTable/propertyAreaView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'propertyAreaView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PropertyAreaView_t {
    uint offsetsAndSizes[20];
    char stringdata0[17];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[15];
    char stringdata5[18];
    char stringdata6[12];
    char stringdata7[23];
    char stringdata8[20];
    char stringdata9[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PropertyAreaView_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_PropertyAreaView_t qt_meta_stringdata_PropertyAreaView = {
    {
        QT_MOC_LITERAL(0, 16),  // "PropertyAreaView"
        QT_MOC_LITERAL(17, 20),  // "s_whiteBoardProFresh"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 15),  // "refreashProType"
        QT_MOC_LITERAL(55, 14),  // "s_commproFresh"
        QT_MOC_LITERAL(70, 17),  // "s_sceneItemInsert"
        QT_MOC_LITERAL(88, 11),  // "DiagramType"
        QT_MOC_LITERAL(100, 22),  // "s_saveToCurrentPicture"
        QT_MOC_LITERAL(123, 19),  // "s_saveToAllPictures"
        QT_MOC_LITERAL(143, 20)   // "s_clearGraphicsItems"
    },
    "PropertyAreaView",
    "s_whiteBoardProFresh",
    "",
    "refreashProType",
    "s_commproFresh",
    "s_sceneItemInsert",
    "DiagramType",
    "s_saveToCurrentPicture",
    "s_saveToAllPictures",
    "s_clearGraphicsItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PropertyAreaView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    0,   53,    2, 0x06,    3 /* Public */,
       5,    1,   54,    2, 0x06,    4 /* Public */,
       7,    0,   57,    2, 0x06,    6 /* Public */,
       8,    0,   58,    2, 0x06,    7 /* Public */,
       9,    0,   59,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PropertyAreaView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PropertyAreaView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->s_whiteBoardProFresh((*reinterpret_cast< std::add_pointer_t<refreashProType>>(_a[1]))); break;
        case 1: _t->s_commproFresh(); break;
        case 2: _t->s_sceneItemInsert((*reinterpret_cast< std::add_pointer_t<DiagramType>>(_a[1]))); break;
        case 3: _t->s_saveToCurrentPicture(); break;
        case 4: _t->s_saveToAllPictures(); break;
        case 5: _t->s_clearGraphicsItems(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< refreashProType >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DiagramType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PropertyAreaView::*)(refreashProType );
            if (_t _q_method = &PropertyAreaView::s_whiteBoardProFresh; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PropertyAreaView::*)();
            if (_t _q_method = &PropertyAreaView::s_commproFresh; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PropertyAreaView::*)(DiagramType );
            if (_t _q_method = &PropertyAreaView::s_sceneItemInsert; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PropertyAreaView::*)();
            if (_t _q_method = &PropertyAreaView::s_saveToCurrentPicture; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PropertyAreaView::*)();
            if (_t _q_method = &PropertyAreaView::s_saveToAllPictures; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PropertyAreaView::*)();
            if (_t _q_method = &PropertyAreaView::s_clearGraphicsItems; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject PropertyAreaView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PropertyAreaView.offsetsAndSizes,
    qt_meta_data_PropertyAreaView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PropertyAreaView_t
, QtPrivate::TypeAndForceComplete<PropertyAreaView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<refreashProType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DiagramType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *PropertyAreaView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PropertyAreaView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PropertyAreaView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PropertyAreaView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PropertyAreaView::s_whiteBoardProFresh(refreashProType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PropertyAreaView::s_commproFresh()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PropertyAreaView::s_sceneItemInsert(DiagramType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PropertyAreaView::s_saveToCurrentPicture()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PropertyAreaView::s_saveToAllPictures()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PropertyAreaView::s_clearGraphicsItems()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
