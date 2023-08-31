/****************************************************************************
** Meta object code from reading C++ file 'booleditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../qt-mvvm/source/libmvvm_viewmodel/mvvm/editors/booleditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'booleditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelView__BoolEditor_t {
    uint offsetsAndSizes[8];
    char stringdata0[22];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ModelView__BoolEditor_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ModelView__BoolEditor_t qt_meta_stringdata_ModelView__BoolEditor = {
    {
        QT_MOC_LITERAL(0, 21),  // "ModelView::BoolEditor"
        QT_MOC_LITERAL(22, 16),  // "onCheckBoxChange"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 5)   // "value"
    },
    "ModelView::BoolEditor",
    "onCheckBoxChange",
    "",
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelView__BoolEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void ModelView::BoolEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BoolEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onCheckBoxChange((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ModelView::BoolEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<CustomEditor::staticMetaObject>(),
    qt_meta_stringdata_ModelView__BoolEditor.offsetsAndSizes,
    qt_meta_data_ModelView__BoolEditor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ModelView__BoolEditor_t
, QtPrivate::TypeAndForceComplete<BoolEditor, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *ModelView::BoolEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelView::BoolEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelView__BoolEditor.stringdata0))
        return static_cast<void*>(this);
    return CustomEditor::qt_metacast(_clname);
}

int ModelView::BoolEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
