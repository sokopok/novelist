/****************************************************************************
** Meta object code from reading C++ file 'response.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/response.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'response.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN2ai8ResponseE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Response::qt_create_metaobjectdata<qt_meta_tag_ZN2ai8ResponseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Response",
        "QML.Element",
        "Response",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "Response is created internally",
        "requestSent",
        "",
        "readyRead",
        "finished",
        "errorOccurred",
        "ai::Error",
        "error",
        "idChanged",
        "runningChanged",
        "finishedChanged",
        "id",
        "isRunning",
        "isFinished",
        "client",
        "Client*",
        "request",
        "Request",
        "Attribute",
        "IdAttribute",
        "NumAttributes"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requestSent'
        QtMocHelpers::SignalData<void()>(7, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'readyRead'
        QtMocHelpers::SignalData<void()>(9, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'finished'
        QtMocHelpers::SignalData<void()>(10, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const ai::Error &)>(11, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Signal 'idChanged'
        QtMocHelpers::SignalData<void()>(14, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'runningChanged'
        QtMocHelpers::SignalData<void()>(15, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'finishedChanged'
        QtMocHelpers::SignalData<void()>(16, 8, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 4),
        // property 'isRunning'
        QtMocHelpers::PropertyData<bool>(18, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 5),
        // property 'isFinished'
        QtMocHelpers::PropertyData<bool>(19, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final, 6),
        // property 'client'
        QtMocHelpers::PropertyData<Client*>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'request'
        QtMocHelpers::PropertyData<Request>(22, 0x80000000 | 23, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Attribute'
        QtMocHelpers::EnumData<Attribute>(24, 24, QMC::EnumFlags{}).add({
            {   25, Attribute::IdAttribute },
            {   26, Attribute::NumAttributes },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Response, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::Response::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai8ResponseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai8ResponseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai8ResponseE_t>.metaTypes,
    nullptr
} };

void ai::Response::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Response *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requestSent(QPrivateSignal()); break;
        case 1: _t->readyRead(QPrivateSignal()); break;
        case 2: _t->finished(QPrivateSignal()); break;
        case 3: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<ai::Error>>(_a[1])), QPrivateSignal()); break;
        case 4: _t->idChanged(QPrivateSignal()); break;
        case 5: _t->runningChanged(QPrivateSignal()); break;
        case 6: _t->finishedChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Response::*)(QPrivateSignal)>(_a, &Response::requestSent, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Response::*)(QPrivateSignal)>(_a, &Response::readyRead, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Response::*)(QPrivateSignal)>(_a, &Response::finished, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Response::*)(const ai::Error & , QPrivateSignal)>(_a, &Response::errorOccurred, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Response::*)(QPrivateSignal)>(_a, &Response::idChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Response::*)(QPrivateSignal)>(_a, &Response::runningChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Response::*)(QPrivateSignal)>(_a, &Response::finishedChanged, 6))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isRunning(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isFinished(); break;
        case 3: *reinterpret_cast<Client**>(_v) = _t->client(); break;
        case 4: *reinterpret_cast<Request*>(_v) = _t->request(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ai::Response::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::Response::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai8ResponseE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ai::Response::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ai::Response::requestSent(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ai::Response::readyRead(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ai::Response::finished(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ai::Response::errorOccurred(const ai::Error & _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void ai::Response::idChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ai::Response::runningChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void ai::Response::finishedChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
