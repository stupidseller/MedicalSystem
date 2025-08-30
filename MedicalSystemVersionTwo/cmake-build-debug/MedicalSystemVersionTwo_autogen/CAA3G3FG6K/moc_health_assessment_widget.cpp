/****************************************************************************
** Meta object code from reading C++ file 'health_assessment_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/widgets/patient/health_assessment_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'health_assessment_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HealthAssessmentWidget_t {
    QByteArrayData data[6];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HealthAssessmentWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HealthAssessmentWidget_t qt_meta_stringdata_HealthAssessmentWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "HealthAssessmentWidget"
QT_MOC_LITERAL(1, 23, 13), // "backRequested"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 15), // "onSubmitClicked"
QT_MOC_LITERAL(4, 54, 15), // "onRetakeClicked"
QT_MOC_LITERAL(5, 70, 15) // "onAnswerChanged"

    },
    "HealthAssessmentWidget\0backRequested\0"
    "\0onSubmitClicked\0onRetakeClicked\0"
    "onAnswerChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HealthAssessmentWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HealthAssessmentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HealthAssessmentWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->onSubmitClicked(); break;
        case 2: _t->onRetakeClicked(); break;
        case 3: _t->onAnswerChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HealthAssessmentWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HealthAssessmentWidget::backRequested)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HealthAssessmentWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_HealthAssessmentWidget.data,
    qt_meta_data_HealthAssessmentWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HealthAssessmentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HealthAssessmentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HealthAssessmentWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HealthAssessmentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void HealthAssessmentWidget::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
