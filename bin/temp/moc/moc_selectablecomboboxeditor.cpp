/****************************************************************************
** Meta object code from reading C++ file 'selectablecomboboxeditor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../qt-mvvm/source/libmvvm_viewmodel/mvvm/editors/selectablecomboboxeditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectablecomboboxeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelView__SelectableComboBoxEditor_t {
    uint offsetsAndSizes[14];
    char stringdata0[36];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[11];
    char stringdata5[14];
    char stringdata6[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ModelView__SelectableComboBoxEditor_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ModelView__SelectableComboBoxEditor_t qt_meta_stringdata_ModelView__SelectableComboBoxEditor = {
    {
        QT_MOC_LITERAL(0, 35),  // "ModelView::SelectableComboBox..."
        QT_MOC_LITERAL(36, 18),  // "onModelDataChanged"
        QT_MOC_LITERAL(55, 0),  // ""
        QT_MOC_LITERAL(56, 11),  // "QModelIndex"
        QT_MOC_LITERAL(68, 10),  // "QList<int>"
        QT_MOC_LITERAL(79, 13),  // "onClickedList"
        QT_MOC_LITERAL(93, 5)   // "index"
    },
    "ModelView::SelectableComboBoxEditor",
    "onModelDataChanged",
    "",
    "QModelIndex",
    "QList<int>",
    "onClickedList",
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelView__SelectableComboBoxEditor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   26,    2, 0x09,    1 /* Protected */,
       5,    1,   33,    2, 0x09,    5 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 4,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 3,    6,

       0        // eod
};

void ModelView::SelectableComboBoxEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectableComboBoxEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onModelDataChanged((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QList<int>>>(_a[3]))); break;
        case 1: _t->onClickedList((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<int> >(); break;
            }
            break;
        }
    }
}

const QMetaObject ModelView::SelectableComboBoxEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<CustomEditor::staticMetaObject>(),
    qt_meta_stringdata_ModelView__SelectableComboBoxEditor.offsetsAndSizes,
    qt_meta_data_ModelView__SelectableComboBoxEditor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ModelView__SelectableComboBoxEditor_t
, QtPrivate::TypeAndForceComplete<SelectableComboBoxEditor, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<const QVector<int> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>


>,
    nullptr
} };


const QMetaObject *ModelView::SelectableComboBoxEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelView::SelectableComboBoxEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelView__SelectableComboBoxEditor.stringdata0))
        return static_cast<void*>(this);
    return CustomEditor::qt_metacast(_clname);
}

int ModelView::SelectableComboBoxEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CustomEditor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
