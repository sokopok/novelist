/****************************************************************************
** Meta object code from reading C++ file 'responseutils.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/responseutils.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'responseutils.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai5EmptyE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Empty::qt_create_metaobjectdata<qt_meta_tag_ZN2ai5EmptyE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Empty",
        "utilityType",
        "ai::UtilityType",
        "extra",
        "empty",
        "valid"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'utilityType'
        QtMocHelpers::PropertyData<ai::UtilityType>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'extra'
        QtMocHelpers::PropertyData<QJsonObject>(3, QMetaType::QJsonObject, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'empty'
        QtMocHelpers::PropertyData<bool>(4, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'valid'
        QtMocHelpers::PropertyData<bool>(5, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Empty, qt_meta_tag_ZN2ai5EmptyE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Empty::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai5EmptyE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai5EmptyE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai5EmptyE_t>.metaTypes,
    nullptr
} };

void ai::Empty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Empty *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ai::UtilityType*>(_v) = _t->utilityType(); break;
        case 1: *reinterpret_cast<QJsonObject*>(_v) = _t->extra(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isEmpty(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isValid(); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai5ErrorE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Error::qt_create_metaobjectdata<qt_meta_tag_ZN2ai5ErrorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Error",
        "utilityType",
        "ai::UtilityType",
        "extra",
        "empty",
        "valid",
        "type",
        "Type",
        "code",
        "Code",
        "message",
        "param",
        "NoError",
        "UnknownError",
        "InternalError",
        "NetworkError",
        "SslError",
        "MissingRequiredParameter",
        "NoErrorType",
        "UnknownErrorType",
        "InternalErrorType",
        "NetworkErrorType",
        "InvalidRequestErrorType"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'utilityType'
        QtMocHelpers::PropertyData<ai::UtilityType>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'extra'
        QtMocHelpers::PropertyData<QJsonObject>(3, QMetaType::QJsonObject, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'empty'
        QtMocHelpers::PropertyData<bool>(4, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'valid'
        QtMocHelpers::PropertyData<bool>(5, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'type'
        QtMocHelpers::PropertyData<Type>(6, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'code'
        QtMocHelpers::PropertyData<Code>(8, 0x80000000 | 9, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'message'
        QtMocHelpers::PropertyData<QString>(10, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'param'
        QtMocHelpers::PropertyData<QString>(11, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Code'
        QtMocHelpers::EnumData<Code>(9, 9, QMC::EnumFlags{}).add({
            {   12, Code::NoError },
            {   13, Code::UnknownError },
            {   14, Code::InternalError },
            {   15, Code::NetworkError },
            {   16, Code::SslError },
            {   17, Code::MissingRequiredParameter },
        }),
        // enum 'Type'
        QtMocHelpers::EnumData<Type>(7, 7, QMC::EnumFlags{}).add({
            {   18, Type::NoErrorType },
            {   19, Type::UnknownErrorType },
            {   20, Type::InternalErrorType },
            {   21, Type::NetworkErrorType },
            {   22, Type::InvalidRequestErrorType },
        }),
    };
    return QtMocHelpers::metaObjectData<Error, qt_meta_tag_ZN2ai5ErrorE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Error::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai5ErrorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai5ErrorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai5ErrorE_t>.metaTypes,
    nullptr
} };

void ai::Error::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Error *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ai::UtilityType*>(_v) = _t->utilityType(); break;
        case 1: *reinterpret_cast<QJsonObject*>(_v) = _t->extra(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isEmpty(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isValid(); break;
        case 4: *reinterpret_cast<Type*>(_v) = _t->type(); break;
        case 5: *reinterpret_cast<Code*>(_v) = _t->code(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->message(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->param(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setType(*reinterpret_cast<Type*>(_v)); break;
        case 5: _t->setCode(*reinterpret_cast<Code*>(_v)); break;
        case 6: _t->setMessage(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setParam(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
QT_WARNING_POP
