/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/client.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai6ClientE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Client::qt_create_metaobjectdata<qt_meta_tag_ZN2ai6ClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Client",
        "QML.Element",
        "Client",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "Client is a base class",
        "apiKeyChanged",
        "",
        "apiUrlChanged",
        "errorOccurred",
        "ai::Error",
        "error",
        "responseErrorOccurred",
        "ai::Response*",
        "response",
        "responseRequestSent",
        "responseReadyRead",
        "responseFinished",
        "responseTextGenerated",
        "text",
        "responseImageGenerated",
        "image",
        "tokenProviderChanged",
        "networkAccessManagerChanged"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'apiKeyChanged'
        QtMocHelpers::SignalData<void()>(7, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'apiUrlChanged'
        QtMocHelpers::SignalData<void()>(9, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const ai::Error &)>(10, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Signal 'responseErrorOccurred'
        QtMocHelpers::SignalData<void(ai::Response *, const ai::Error &)>(13, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { 0x80000000 | 11, 12 },
        }}),
        // Signal 'responseRequestSent'
        QtMocHelpers::SignalData<void(ai::Response *)>(16, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Signal 'responseReadyRead'
        QtMocHelpers::SignalData<void(ai::Response *)>(17, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Signal 'responseFinished'
        QtMocHelpers::SignalData<void(ai::Response *)>(18, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Signal 'responseTextGenerated'
        QtMocHelpers::SignalData<void(ai::Response *, const QString &)>(19, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { QMetaType::QString, 20 },
        }}),
        // Signal 'responseImageGenerated'
        QtMocHelpers::SignalData<void(ai::Response *, const QImage &)>(21, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { QMetaType::QImage, 22 },
        }}),
        // Signal 'tokenProviderChanged'
        QtMocHelpers::SignalData<void()>(23, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'networkAccessManagerChanged'
        QtMocHelpers::SignalData<void()>(24, 8, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Client, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6ClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6ClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai6ClientE_t>.metaTypes,
    nullptr
} };

void ai::Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Client *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->apiKeyChanged(QPrivateSignal()); break;
        case 1: _t->apiUrlChanged(QPrivateSignal()); break;
        case 2: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<ai::Error>>(_a[1])), QPrivateSignal()); break;
        case 3: _t->responseErrorOccurred((*reinterpret_cast< std::add_pointer_t<ai::Response*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ai::Error>>(_a[2])), QPrivateSignal()); break;
        case 4: _t->responseRequestSent((*reinterpret_cast< std::add_pointer_t<ai::Response*>>(_a[1])), QPrivateSignal()); break;
        case 5: _t->responseReadyRead((*reinterpret_cast< std::add_pointer_t<ai::Response*>>(_a[1])), QPrivateSignal()); break;
        case 6: _t->responseFinished((*reinterpret_cast< std::add_pointer_t<ai::Response*>>(_a[1])), QPrivateSignal()); break;
        case 7: _t->responseTextGenerated((*reinterpret_cast< std::add_pointer_t<ai::Response*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])), QPrivateSignal()); break;
        case 8: _t->responseImageGenerated((*reinterpret_cast< std::add_pointer_t<ai::Response*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QImage>>(_a[2])), QPrivateSignal()); break;
        case 9: _t->tokenProviderChanged(QPrivateSignal()); break;
        case 10: _t->networkAccessManagerChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ai::Response* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ai::Response* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ai::Response* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ai::Response* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ai::Response* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ai::Response* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Client::*)(QPrivateSignal)>(_a, &Client::apiKeyChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(QPrivateSignal)>(_a, &Client::apiUrlChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(const ai::Error & , QPrivateSignal)>(_a, &Client::errorOccurred, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(ai::Response * , const ai::Error & , QPrivateSignal)>(_a, &Client::responseErrorOccurred, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(ai::Response * , QPrivateSignal)>(_a, &Client::responseRequestSent, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(ai::Response * , QPrivateSignal)>(_a, &Client::responseReadyRead, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(ai::Response * , QPrivateSignal)>(_a, &Client::responseFinished, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(ai::Response * , const QString & , QPrivateSignal)>(_a, &Client::responseTextGenerated, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(ai::Response * , const QImage & , QPrivateSignal)>(_a, &Client::responseImageGenerated, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(QPrivateSignal)>(_a, &Client::tokenProviderChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Client::*)(QPrivateSignal)>(_a, &Client::networkAccessManagerChanged, 10))
            return;
    }
}

const QMetaObject *ai::Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6ClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ai::Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ai::Client::apiKeyChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ai::Client::apiUrlChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ai::Client::errorOccurred(const ai::Error & _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void ai::Client::responseErrorOccurred(ai::Response * _t1, const ai::Error & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void ai::Client::responseRequestSent(ai::Response * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void ai::Client::responseReadyRead(ai::Response * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void ai::Client::responseFinished(ai::Response * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void ai::Client::responseTextGenerated(ai::Response * _t1, const QString & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2, _t3);
}

// SIGNAL 8
void ai::Client::responseImageGenerated(ai::Response * _t1, const QImage & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2, _t3);
}

// SIGNAL 9
void ai::Client::tokenProviderChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void ai::Client::networkAccessManagerChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}
QT_WARNING_POP
