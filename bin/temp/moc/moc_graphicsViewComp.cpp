/****************************************************************************
** Meta object code from reading C++ file 'graphicsViewComp.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../animation/mainAreaComponent/graphicsViewComp.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicsViewComp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicsViewComp_t {
    uint offsetsAndSizes[2];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GraphicsViewComp_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_GraphicsViewComp_t qt_meta_stringdata_GraphicsViewComp = {
    {
        QT_MOC_LITERAL(0, 16)   // "GraphicsViewComp"
    },
    "GraphicsViewComp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsViewComp[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void GraphicsViewComp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject GraphicsViewComp::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_GraphicsViewComp.offsetsAndSizes,
    qt_meta_data_GraphicsViewComp,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GraphicsViewComp_t
, QtPrivate::TypeAndForceComplete<GraphicsViewComp, std::true_type>



>,
    nullptr
} };


const QMetaObject *GraphicsViewComp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsViewComp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsViewComp.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicsViewComp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PicGraphicsScene_t {
    uint offsetsAndSizes[26];
    char stringdata0[17];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[5];
    char stringdata5[13];
    char stringdata6[19];
    char stringdata7[13];
    char stringdata8[15];
    char stringdata9[10];
    char stringdata10[11];
    char stringdata11[16];
    char stringdata12[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PicGraphicsScene_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_PicGraphicsScene_t qt_meta_stringdata_PicGraphicsScene = {
    {
        QT_MOC_LITERAL(0, 16),  // "PicGraphicsScene"
        QT_MOC_LITERAL(17, 12),  // "itemInserted"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 12),  // "DiagramItem*"
        QT_MOC_LITERAL(44, 4),  // "item"
        QT_MOC_LITERAL(49, 12),  // "textInserted"
        QT_MOC_LITERAL(62, 18),  // "QGraphicsTextItem*"
        QT_MOC_LITERAL(81, 12),  // "itemSelected"
        QT_MOC_LITERAL(94, 14),  // "QGraphicsItem*"
        QT_MOC_LITERAL(109, 9),  // "s_modeRef"
        QT_MOC_LITERAL(119, 10),  // "InsertMode"
        QT_MOC_LITERAL(130, 15),  // "editorLostFocus"
        QT_MOC_LITERAL(146, 16)   // "DiagramTextItem*"
    },
    "PicGraphicsScene",
    "itemInserted",
    "",
    "DiagramItem*",
    "item",
    "textInserted",
    "QGraphicsTextItem*",
    "itemSelected",
    "QGraphicsItem*",
    "s_modeRef",
    "InsertMode",
    "editorLostFocus",
    "DiagramTextItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PicGraphicsScene[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    1,   47,    2, 0x06,    3 /* Public */,
       7,    1,   50,    2, 0x06,    5 /* Public */,
       9,    1,   53,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   56,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, 0x80000000 | 10,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,    4,

       0        // eod
};

void PicGraphicsScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PicGraphicsScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->itemInserted((*reinterpret_cast< std::add_pointer_t<DiagramItem*>>(_a[1]))); break;
        case 1: _t->textInserted((*reinterpret_cast< std::add_pointer_t<QGraphicsTextItem*>>(_a[1]))); break;
        case 2: _t->itemSelected((*reinterpret_cast< std::add_pointer_t<QGraphicsItem*>>(_a[1]))); break;
        case 3: _t->s_modeRef((*reinterpret_cast< std::add_pointer_t<InsertMode>>(_a[1]))); break;
        case 4: _t->editorLostFocus((*reinterpret_cast< std::add_pointer_t<DiagramTextItem*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< InsertMode >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PicGraphicsScene::*)(DiagramItem * );
            if (_t _q_method = &PicGraphicsScene::itemInserted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PicGraphicsScene::*)(QGraphicsTextItem * );
            if (_t _q_method = &PicGraphicsScene::textInserted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PicGraphicsScene::*)(QGraphicsItem * );
            if (_t _q_method = &PicGraphicsScene::itemSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PicGraphicsScene::*)(InsertMode );
            if (_t _q_method = &PicGraphicsScene::s_modeRef; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject PicGraphicsScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_PicGraphicsScene.offsetsAndSizes,
    qt_meta_data_PicGraphicsScene,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PicGraphicsScene_t
, QtPrivate::TypeAndForceComplete<PicGraphicsScene, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DiagramItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QGraphicsTextItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QGraphicsItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<InsertMode, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DiagramTextItem *, std::false_type>


>,
    nullptr
} };


const QMetaObject *PicGraphicsScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PicGraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PicGraphicsScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int PicGraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PicGraphicsScene::itemInserted(DiagramItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PicGraphicsScene::textInserted(QGraphicsTextItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PicGraphicsScene::itemSelected(QGraphicsItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PicGraphicsScene::s_modeRef(InsertMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
