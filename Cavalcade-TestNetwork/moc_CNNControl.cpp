/****************************************************************************
** Meta object code from reading C++ file 'CNNControl.h'
**
** Created: Sun Jan 27 15:16:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CNNControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CNNControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CNNControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      40,   11,   11,   11, 0x0a,
      59,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CNNControl[] = {
    "CNNControl\0\0LoadNetwork()\0SaveNetwork()\0"
    "LoadGenomeToMind()\0LoadGenomeToTWMind()\0"
};

void CNNControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CNNControl *_t = static_cast<CNNControl *>(_o);
        switch (_id) {
        case 0: _t->LoadNetwork(); break;
        case 1: _t->SaveNetwork(); break;
        case 2: _t->LoadGenomeToMind(); break;
        case 3: _t->LoadGenomeToTWMind(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CNNControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CNNControl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CNNControl,
      qt_meta_data_CNNControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CNNControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CNNControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CNNControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CNNControl))
        return static_cast<void*>(const_cast< CNNControl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CNNControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
