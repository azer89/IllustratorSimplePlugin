/****************************************************************************
** Meta object code from reading C++ file 'myqtui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myqtui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myqtui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyQTUI_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyQTUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyQTUI_t qt_meta_stringdata_MyQTUI = {
    {
QT_MOC_LITERAL(0, 0, 6), // "MyQTUI"
QT_MOC_LITERAL(1, 7, 16), // "QtDisplayMessage"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "msg"
QT_MOC_LITERAL(4, 29, 14), // "LoadFileAction"
QT_MOC_LITERAL(5, 44, 14) // "SaveFileAction"

    },
    "MyQTUI\0QtDisplayMessage\0\0msg\0"
    "LoadFileAction\0SaveFileAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyQTUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyQTUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyQTUI *_t = static_cast<MyQTUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->QtDisplayMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->LoadFileAction(); break;
        case 2: _t->SaveFileAction(); break;
        default: ;
        }
    }
}

const QMetaObject MyQTUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyQTUI.data,
      qt_meta_data_MyQTUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyQTUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyQTUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyQTUI.stringdata0))
        return static_cast<void*>(const_cast< MyQTUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyQTUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
