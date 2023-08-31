/****************************************************************************
** Meta object code from reading C++ file 'utils.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../animation/utils/utils.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'utils.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Utils_t {
    uint offsetsAndSizes[52];
    char stringdata0[6];
    char stringdata1[4];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[11];
    char stringdata5[10];
    char stringdata6[18];
    char stringdata7[9];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[16];
    char stringdata11[22];
    char stringdata12[13];
    char stringdata13[5];
    char stringdata14[20];
    char stringdata15[6];
    char stringdata16[17];
    char stringdata17[11];
    char stringdata18[5];
    char stringdata19[11];
    char stringdata20[6];
    char stringdata21[8];
    char stringdata22[6];
    char stringdata23[8];
    char stringdata24[6];
    char stringdata25[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Utils_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_Utils_t qt_meta_stringdata_Utils = {
    {
        QT_MOC_LITERAL(0, 5),  // "Utils"
        QT_MOC_LITERAL(6, 3),  // "log"
        QT_MOC_LITERAL(10, 0),  // ""
        QT_MOC_LITERAL(11, 3),  // "txt"
        QT_MOC_LITERAL(15, 10),  // "createUuid"
        QT_MOC_LITERAL(26, 9),  // "timestamp"
        QT_MOC_LITERAL(36, 17),  // "canonicalFilePath"
        QT_MOC_LITERAL(54, 8),  // "filePath"
        QT_MOC_LITERAL(63, 8),  // "fileSize"
        QT_MOC_LITERAL(72, 8),  // "fileName"
        QT_MOC_LITERAL(81, 15),  // "currentDateTime"
        QT_MOC_LITERAL(97, 21),  // "currentDateTimesecond"
        QT_MOC_LITERAL(119, 12),  // "jsonValidity"
        QT_MOC_LITERAL(132, 4),  // "json"
        QT_MOC_LITERAL(137, 19),  // "toDateTimeFromMSecs"
        QT_MOC_LITERAL(157, 5),  // "msecs"
        QT_MOC_LITERAL(163, 16),  // "toTimesFromMSecs"
        QT_MOC_LITERAL(180, 10),  // "timingFull"
        QT_MOC_LITERAL(191, 4),  // "secs"
        QT_MOC_LITERAL(196, 10),  // "getFileMd5"
        QT_MOC_LITERAL(207, 5),  // "autoW"
        QT_MOC_LITERAL(213, 7),  // "beforeW"
        QT_MOC_LITERAL(221, 5),  // "autoH"
        QT_MOC_LITERAL(227, 7),  // "beforeH"
        QT_MOC_LITERAL(235, 5),  // "autoF"
        QT_MOC_LITERAL(241, 7)   // "beforeF"
    },
    "Utils",
    "log",
    "",
    "txt",
    "createUuid",
    "timestamp",
    "canonicalFilePath",
    "filePath",
    "fileSize",
    "fileName",
    "currentDateTime",
    "currentDateTimesecond",
    "jsonValidity",
    "json",
    "toDateTimeFromMSecs",
    "msecs",
    "toTimesFromMSecs",
    "timingFull",
    "secs",
    "getFileMd5",
    "autoW",
    "beforeW",
    "autoH",
    "beforeH",
    "autoF",
    "beforeF"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Utils[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  110,    2, 0x06,    1 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  113,    2, 0x02,    3 /* Public */,
       5,    0,  114,    2, 0x02,    4 /* Public */,
       6,    1,  115,    2, 0x02,    5 /* Public */,
       8,    1,  118,    2, 0x02,    7 /* Public */,
       9,    1,  121,    2, 0x02,    9 /* Public */,
      10,    0,  124,    2, 0x02,   11 /* Public */,
      11,    0,  125,    2, 0x02,   12 /* Public */,
      12,    1,  126,    2, 0x02,   13 /* Public */,
      14,    1,  129,    2, 0x02,   15 /* Public */,
      16,    1,  132,    2, 0x02,   17 /* Public */,
      17,    1,  135,    2, 0x02,   19 /* Public */,
      19,    1,  138,    2, 0x02,   21 /* Public */,
      20,    1,  141,    2, 0x02,   23 /* Public */,
      22,    1,  144,    2, 0x02,   25 /* Public */,
      24,    1,  147,    2, 0x02,   27 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // methods: parameters
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::ULong, QMetaType::QString,    7,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString,   13,
    QMetaType::QString, QMetaType::LongLong,   15,
    QMetaType::QString, QMetaType::LongLong,   15,
    QMetaType::QString, QMetaType::Int,   18,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::Int, QMetaType::Int,   21,
    QMetaType::Int, QMetaType::Int,   23,
    QMetaType::Int, QMetaType::Int,   25,

       0        // eod
};

void Utils::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Utils *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->log((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: { QString _r = _t->createUuid();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->timestamp();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->canonicalFilePath((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { ulong _r = _t->fileSize((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< ulong*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->fileName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->currentDateTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->currentDateTimesecond();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->jsonValidity((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { QString _r = _t->toDateTimeFromMSecs((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->toTimesFromMSecs((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->timingFull((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->getFileMd5((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: { int _r = _t->autoW((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: { int _r = _t->autoH((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: { int _r = _t->autoF((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Utils::*)(const QString & );
            if (_t _q_method = &Utils::log; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Utils::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Utils.offsetsAndSizes,
    qt_meta_data_Utils,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Utils_t
, QtPrivate::TypeAndForceComplete<Utils, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>

, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<unsigned long, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *Utils::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Utils::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Utils.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Utils::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Utils::log(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
