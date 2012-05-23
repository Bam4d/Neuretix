/****************************************************************************
** Meta object code from reading C++ file 'CNNControl.h'
**
** Created: Wed May 23 14:00:55 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CNNControl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CNNControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CNNControl[] = {

 // content:
       5,       // revision
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

const QMetaObject CNNControl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CNNControl,
      qt_meta_data_CNNControl, 0 }
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
        switch (_id) {
        case 0: LoadNetwork(); break;
        case 1: SaveNetwork(); break;
        case 2: LoadGenomeToMind(); break;
        case 3: LoadGenomeToTWMind(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
