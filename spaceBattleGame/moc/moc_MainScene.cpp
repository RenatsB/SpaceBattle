/****************************************************************************
** Meta object code from reading C++ file 'MainScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/MainScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainScene_t {
    QByteArrayData data[22];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainScene_t qt_meta_stringdata_MainScene = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MainScene"
QT_MOC_LITERAL(1, 10, 6), // "select"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "deselect"
QT_MOC_LITERAL(4, 27, 4), // "move"
QT_MOC_LITERAL(5, 32, 5), // "_axis"
QT_MOC_LITERAL(6, 38, 4), // "_val"
QT_MOC_LITERAL(7, 43, 5), // "scale"
QT_MOC_LITERAL(8, 49, 6), // "rotate"
QT_MOC_LITERAL(9, 56, 9), // "changeMat"
QT_MOC_LITERAL(10, 66, 4), // "_cmd"
QT_MOC_LITERAL(11, 71, 9), // "changeGeo"
QT_MOC_LITERAL(12, 81, 8), // "loadFile"
QT_MOC_LITERAL(13, 90, 13), // "receiveSelCmd"
QT_MOC_LITERAL(14, 104, 8), // "_current"
QT_MOC_LITERAL(15, 113, 14), // "receiveFileCmd"
QT_MOC_LITERAL(16, 128, 13), // "receiveModCmd"
QT_MOC_LITERAL(17, 142, 16), // "receiveTableInfo"
QT_MOC_LITERAL(18, 159, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(19, 177, 4), // "_ref"
QT_MOC_LITERAL(20, 182, 9), // "wireframe"
QT_MOC_LITERAL(21, 192, 6) // "_value"

    },
    "MainScene\0select\0\0deselect\0move\0_axis\0"
    "_val\0scale\0rotate\0changeMat\0_cmd\0"
    "changeGeo\0loadFile\0receiveSelCmd\0"
    "_current\0receiveFileCmd\0receiveModCmd\0"
    "receiveTableInfo\0QTableWidgetItem*\0"
    "_ref\0wireframe\0_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    2,   81,    2, 0x0a /* Public */,
       7,    2,   86,    2, 0x0a /* Public */,
       8,    2,   91,    2, 0x0a /* Public */,
       9,    1,   96,    2, 0x0a /* Public */,
      11,    1,   99,    2, 0x0a /* Public */,
      12,    0,  102,    2, 0x0a /* Public */,
      13,    1,  103,    2, 0x0a /* Public */,
      15,    1,  106,    2, 0x0a /* Public */,
      16,    1,  109,    2, 0x0a /* Public */,
      17,    1,  112,    2, 0x0a /* Public */,
      20,    1,  115,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::Float,    5,    6,
    QMetaType::Void, QMetaType::UShort, QMetaType::Float,    5,    6,
    QMetaType::Void, QMetaType::UShort, QMetaType::Float,    5,    6,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::Bool,   21,

       0        // eod
};

void MainScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainScene *_t = static_cast<MainScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->select(); break;
        case 1: _t->deselect(); break;
        case 2: _t->move((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->scale((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->rotate((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->changeMat((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->changeGeo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->loadFile(); break;
        case 8: _t->receiveSelCmd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->receiveFileCmd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->receiveModCmd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->receiveTableInfo((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 12: _t->wireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainScene::staticMetaObject = {
    { &Scene::staticMetaObject, qt_meta_stringdata_MainScene.data,
      qt_meta_data_MainScene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainScene.stringdata0))
        return static_cast<void*>(const_cast< MainScene*>(this));
    return Scene::qt_metacast(_clname);
}

int MainScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Scene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
