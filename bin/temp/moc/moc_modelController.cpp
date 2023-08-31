/****************************************************************************
** Meta object code from reading C++ file 'modelController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../animation/modelController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelController_t {
    uint offsetsAndSizes[24];
    char stringdata0[16];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[5];
    char stringdata5[18];
    char stringdata6[7];
    char stringdata7[18];
    char stringdata8[13];
    char stringdata9[16];
    char stringdata10[21];
    char stringdata11[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ModelController_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ModelController_t qt_meta_stringdata_ModelController = {
    {
        QT_MOC_LITERAL(0, 15),  // "ModelController"
        QT_MOC_LITERAL(16, 12),  // "s_insertItem"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 23),  // "ModelView::SessionItem*"
        QT_MOC_LITERAL(54, 4),  // "item"
        QT_MOC_LITERAL(59, 17),  // "ModelView::TagRow"
        QT_MOC_LITERAL(77, 6),  // "tagrow"
        QT_MOC_LITERAL(84, 17),  // "s_aboutremoveItem"
        QT_MOC_LITERAL(102, 12),  // "s_removeItem"
        QT_MOC_LITERAL(115, 15),  // "slot_insertItem"
        QT_MOC_LITERAL(131, 20),  // "slot_aboutremoveItem"
        QT_MOC_LITERAL(152, 15)   // "slot_removeItem"
    },
    "ModelController",
    "s_insertItem",
    "",
    "ModelView::SessionItem*",
    "item",
    "ModelView::TagRow",
    "tagrow",
    "s_aboutremoveItem",
    "s_removeItem",
    "slot_insertItem",
    "slot_aboutremoveItem",
    "slot_removeItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   50,    2, 0x06,    1 /* Public */,
       7,    2,   55,    2, 0x06,    4 /* Public */,
       8,    2,   60,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    2,   65,    2, 0x08,   10 /* Private */,
      10,    2,   70,    2, 0x08,   13 /* Private */,
      11,    2,   75,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void ModelController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModelController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->s_insertItem((*reinterpret_cast< std::add_pointer_t<ModelView::SessionItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ModelView::TagRow>>(_a[2]))); break;
        case 1: _t->s_aboutremoveItem((*reinterpret_cast< std::add_pointer_t<ModelView::SessionItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ModelView::TagRow>>(_a[2]))); break;
        case 2: _t->s_removeItem((*reinterpret_cast< std::add_pointer_t<ModelView::SessionItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ModelView::TagRow>>(_a[2]))); break;
        case 3: _t->slot_insertItem((*reinterpret_cast< std::add_pointer_t<ModelView::SessionItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ModelView::TagRow>>(_a[2]))); break;
        case 4: _t->slot_aboutremoveItem((*reinterpret_cast< std::add_pointer_t<ModelView::SessionItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ModelView::TagRow>>(_a[2]))); break;
        case 5: _t->slot_removeItem((*reinterpret_cast< std::add_pointer_t<ModelView::SessionItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ModelView::TagRow>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ModelController::*)(ModelView::SessionItem * , ModelView::TagRow );
            if (_t _q_method = &ModelController::s_insertItem; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ModelController::*)(ModelView::SessionItem * , ModelView::TagRow );
            if (_t _q_method = &ModelController::s_aboutremoveItem; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ModelController::*)(ModelView::SessionItem * , ModelView::TagRow );
            if (_t _q_method = &ModelController::s_removeItem; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ModelController::staticMetaObject = { {
    QMetaObject::SuperData::link<ModelView::ModelListener<PictureModel>::staticMetaObject>(),
    qt_meta_stringdata_ModelController.offsetsAndSizes,
    qt_meta_data_ModelController,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ModelController_t
, QtPrivate::TypeAndForceComplete<ModelController, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::SessionItem *, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::TagRow, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::SessionItem *, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::TagRow, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::SessionItem *, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::TagRow, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::SessionItem *, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::TagRow, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::SessionItem *, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::TagRow, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::SessionItem *, std::false_type>, QtPrivate::TypeAndForceComplete<ModelView::TagRow, std::false_type>


>,
    nullptr
} };


const QMetaObject *ModelController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelController.stringdata0))
        return static_cast<void*>(this);
    return ModelView::ModelListener<PictureModel>::qt_metacast(_clname);
}

int ModelController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ModelView::ModelListener<PictureModel>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ModelController::s_insertItem(ModelView::SessionItem * _t1, ModelView::TagRow _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModelController::s_aboutremoveItem(ModelView::SessionItem * _t1, ModelView::TagRow _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModelController::s_removeItem(ModelView::SessionItem * _t1, ModelView::TagRow _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
