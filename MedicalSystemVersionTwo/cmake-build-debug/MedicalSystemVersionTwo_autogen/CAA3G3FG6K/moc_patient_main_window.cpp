/****************************************************************************
** Meta object code from reading C++ file 'patient_main_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/widgets/patient/patient_main_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patient_main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PatientMainWindow_t {
    QByteArrayData data[13];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PatientMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PatientMainWindow_t qt_meta_stringdata_PatientMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PatientMainWindow"
QT_MOC_LITERAL(1, 18, 15), // "logoutRequested"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "updateDateTime"
QT_MOC_LITERAL(4, 50, 12), // "showUserMenu"
QT_MOC_LITERAL(5, 63, 17), // "onLogoutTriggered"
QT_MOC_LITERAL(6, 81, 17), // "showProfileWidget"
QT_MOC_LITERAL(7, 99, 28), // "showAppointmentBookingWidget"
QT_MOC_LITERAL(8, 128, 20), // "showDoctorInfoWidget"
QT_MOC_LITERAL(9, 149, 23), // "showCommunicationWidget"
QT_MOC_LITERAL(10, 173, 26), // "showHealthAssessmentWidget"
QT_MOC_LITERAL(11, 200, 24), // "showMedicineSearchWidget"
QT_MOC_LITERAL(12, 225, 23) // "showOnlinePaymentWidget"

    },
    "PatientMainWindow\0logoutRequested\0\0"
    "updateDateTime\0showUserMenu\0"
    "onLogoutTriggered\0showProfileWidget\0"
    "showAppointmentBookingWidget\0"
    "showDoctorInfoWidget\0showCommunicationWidget\0"
    "showHealthAssessmentWidget\0"
    "showMedicineSearchWidget\0"
    "showOnlinePaymentWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PatientMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PatientMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatientMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logoutRequested(); break;
        case 1: _t->updateDateTime(); break;
        case 2: _t->showUserMenu(); break;
        case 3: _t->onLogoutTriggered(); break;
        case 4: _t->showProfileWidget(); break;
        case 5: _t->showAppointmentBookingWidget(); break;
        case 6: _t->showDoctorInfoWidget(); break;
        case 7: _t->showCommunicationWidget(); break;
        case 8: _t->showHealthAssessmentWidget(); break;
        case 9: _t->showMedicineSearchWidget(); break;
        case 10: _t->showOnlinePaymentWidget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PatientMainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PatientMainWindow::logoutRequested)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PatientMainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_PatientMainWindow.data,
    qt_meta_data_PatientMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PatientMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PatientMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PatientMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PatientMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PatientMainWindow::logoutRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
