/****************************************************************************
** Meta object code from reading C++ file 'online_payment_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/widgets/patient/online_payment_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'online_payment_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OnlinePaymentWidget_t {
    QByteArrayData data[7];
    char stringdata0[125];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OnlinePaymentWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OnlinePaymentWidget_t qt_meta_stringdata_OnlinePaymentWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "OnlinePaymentWidget"
QT_MOC_LITERAL(1, 20, 13), // "backRequested"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 16), // "paymentCompleted"
QT_MOC_LITERAL(4, 52, 23), // "onConfirmPaymentClicked"
QT_MOC_LITERAL(5, 76, 24), // "onPaymentProcessFinished"
QT_MOC_LITERAL(6, 101, 23) // "updatePaymentStatusText"

    },
    "OnlinePaymentWidget\0backRequested\0\0"
    "paymentCompleted\0onConfirmPaymentClicked\0"
    "onPaymentProcessFinished\0"
    "updatePaymentStatusText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OnlinePaymentWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OnlinePaymentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OnlinePaymentWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->paymentCompleted(); break;
        case 2: _t->onConfirmPaymentClicked(); break;
        case 3: _t->onPaymentProcessFinished(); break;
        case 4: _t->updatePaymentStatusText(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OnlinePaymentWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlinePaymentWidget::backRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OnlinePaymentWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OnlinePaymentWidget::paymentCompleted)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject OnlinePaymentWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_OnlinePaymentWidget.data,
    qt_meta_data_OnlinePaymentWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OnlinePaymentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OnlinePaymentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OnlinePaymentWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OnlinePaymentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void OnlinePaymentWidget::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OnlinePaymentWidget::paymentCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
