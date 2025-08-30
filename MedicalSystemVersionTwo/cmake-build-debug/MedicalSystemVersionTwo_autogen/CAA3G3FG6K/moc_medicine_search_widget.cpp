/****************************************************************************
** Meta object code from reading C++ file 'medicine_search_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/widgets/patient/medicine_search_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'medicine_search_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MedicineDetailDialog_t {
    QByteArrayData data[4];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MedicineDetailDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MedicineDetailDialog_t qt_meta_stringdata_MedicineDetailDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "MedicineDetailDialog"
QT_MOC_LITERAL(1, 21, 17), // "purchaseRequested"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 12) // "medicineName"

    },
    "MedicineDetailDialog\0purchaseRequested\0"
    "\0medicineName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MedicineDetailDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void MedicineDetailDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MedicineDetailDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->purchaseRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MedicineDetailDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MedicineDetailDialog::purchaseRequested)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MedicineDetailDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_MedicineDetailDialog.data,
    qt_meta_data_MedicineDetailDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MedicineDetailDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MedicineDetailDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MedicineDetailDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MedicineDetailDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MedicineDetailDialog::purchaseRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_MedicineSearchWidget_t {
    QByteArrayData data[10];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MedicineSearchWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MedicineSearchWidget_t qt_meta_stringdata_MedicineSearchWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "MedicineSearchWidget"
QT_MOC_LITERAL(1, 21, 13), // "backRequested"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15), // "onSearchClicked"
QT_MOC_LITERAL(4, 52, 17), // "onCategoryChanged"
QT_MOC_LITERAL(5, 70, 15), // "onDetailClicked"
QT_MOC_LITERAL(6, 86, 8), // "Medicine"
QT_MOC_LITERAL(7, 95, 8), // "medicine"
QT_MOC_LITERAL(8, 104, 17), // "onPurchaseClicked"
QT_MOC_LITERAL(9, 122, 22) // "onBatchPurchaseClicked"

    },
    "MedicineSearchWidget\0backRequested\0\0"
    "onSearchClicked\0onCategoryChanged\0"
    "onDetailClicked\0Medicine\0medicine\0"
    "onPurchaseClicked\0onBatchPurchaseClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MedicineSearchWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       8,    1,   50,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

       0        // eod
};

void MedicineSearchWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MedicineSearchWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->onSearchClicked(); break;
        case 2: _t->onCategoryChanged(); break;
        case 3: _t->onDetailClicked((*reinterpret_cast< const Medicine(*)>(_a[1]))); break;
        case 4: _t->onPurchaseClicked((*reinterpret_cast< const Medicine(*)>(_a[1]))); break;
        case 5: _t->onBatchPurchaseClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MedicineSearchWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MedicineSearchWidget::backRequested)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MedicineSearchWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MedicineSearchWidget.data,
    qt_meta_data_MedicineSearchWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MedicineSearchWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MedicineSearchWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MedicineSearchWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MedicineSearchWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MedicineSearchWidget::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
