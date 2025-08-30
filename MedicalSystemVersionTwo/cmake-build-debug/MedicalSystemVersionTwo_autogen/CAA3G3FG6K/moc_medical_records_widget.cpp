/****************************************************************************
** Meta object code from reading C++ file 'medical_records_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/widgets/patient/medical_records_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'medical_records_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MedicalRecordsWidget_t {
    QByteArrayData data[11];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MedicalRecordsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MedicalRecordsWidget_t qt_meta_stringdata_MedicalRecordsWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "MedicalRecordsWidget"
QT_MOC_LITERAL(1, 21, 14), // "onRecordsReply"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 52, 5), // "reply"
QT_MOC_LITERAL(5, 58, 22), // "onCaseSelectionChanged"
QT_MOC_LITERAL(6, 81, 14), // "QItemSelection"
QT_MOC_LITERAL(7, 96, 8), // "selected"
QT_MOC_LITERAL(8, 105, 10), // "deselected"
QT_MOC_LITERAL(9, 116, 30), // "onPrescriptionSelectionChanged"
QT_MOC_LITERAL(10, 147, 24) // "onOrdersSelectionChanged"

    },
    "MedicalRecordsWidget\0onRecordsReply\0"
    "\0QNetworkReply*\0reply\0onCaseSelectionChanged\0"
    "QItemSelection\0selected\0deselected\0"
    "onPrescriptionSelectionChanged\0"
    "onOrdersSelectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MedicalRecordsWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       5,    2,   37,    2, 0x08 /* Private */,
       9,    2,   42,    2, 0x08 /* Private */,
      10,    2,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,

       0        // eod
};

void MedicalRecordsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MedicalRecordsWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onRecordsReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->onCaseSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 2: _t->onPrescriptionSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 3: _t->onOrdersSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MedicalRecordsWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MedicalRecordsWidget.data,
    qt_meta_data_MedicalRecordsWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MedicalRecordsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MedicalRecordsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MedicalRecordsWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MedicalRecordsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
