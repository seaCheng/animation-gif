/****************************************************************************
** Meta object code from reading C++ file 'integereditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../qt-mvvm/source/libmvvm_viewmodel/mvvm/editors/integereditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'integereditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelView__IntegerEditor_t {
    uint offsetsAndSizes[6];
    char stringdata0[25];
    char stringdata1[18];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ModelView__IntegerEditor_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ModelView__IntegerEditor_t qt_meta_stringdata_ModelView__IntegerEditor = {
    {
        QT_MOC_LITERAL(0, 24),  // "ModelView::IntegerEditor"
        QT_MOC_LITERAL(25, 17),  // "onEditingFinished"
        QT_MOC_LITERAL(43, 0)   // ""
    },
    "ModelView::IntegerEditor",
    "onEditingFinished",
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelView__IntegerEditor[] = {

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
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ModelView::IntegerEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegerEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEditingFinished(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject ModelView::IntegerEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<CustomEditor::staticMetaObject>(),
    qt_meta_stringdata_ModelView__IntegerEditor.offsetsAndSizes,
    qt_meta_data_ModelView__IntegerEditor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ModelView__IntegerEditor_t
, QtPrivate::TypeAndForceComplete<IntegerEditor, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ModelView::IntegerEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelView::IntegerEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelView__IntegerEditor.stringdata0))
        return static_cast<void*>(this);
    return CustomEditor::qt_metacast(_clname);
}

int ModelView::IntegerEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
