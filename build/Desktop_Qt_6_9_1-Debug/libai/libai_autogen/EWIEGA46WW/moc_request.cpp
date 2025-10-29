/****************************************************************************
** Meta object code from reading C++ file 'request.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/request.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'request.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai7RequestE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Request::qt_create_metaobjectdata<qt_meta_tag_ZN2ai7RequestE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Request",
        "QML.Element",
        "request",
        "QML.Creatable",
        "true",
        "QML.CreationMethod",
        "construct",
        "url",
        "id",
        "apiKey",
        "Attribute",
        "IdAttribute",
        "ApiKeyAttribute",
        "UrlAttribute",
        "NumAttributes",
        "Error",
        "NoError",
        "NetworkError",
        "SslError"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'url'
        QtMocHelpers::PropertyData<QUrl>(7, QMetaType::QUrl, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'id'
        QtMocHelpers::PropertyData<QString>(8, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'apiKey'
        QtMocHelpers::PropertyData<QByteArray>(9, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Attribute'
        QtMocHelpers::EnumData<Attribute>(10, 10, QMC::EnumFlags{}).add({
            {   11, Attribute::IdAttribute },
            {   12, Attribute::ApiKeyAttribute },
            {   13, Attribute::UrlAttribute },
            {   14, Attribute::NumAttributes },
        }),
        // enum 'Error'
        QtMocHelpers::EnumData<Error>(15, 15, QMC::EnumFlags{}).add({
            {   16, Error::NoError },
            {   17, Error::NetworkError },
            {   18, Error::SslError },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Request, void>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::Request::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QNetworkRequest>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai7RequestE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai7RequestE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai7RequestE_t>.metaTypes,
    nullptr
} };

void ai::Request::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Request *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QUrl*>(_v) = _t->url(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->id(); break;
        case 2: *reinterpret_cast<QByteArray*>(_v) = _t->apiKey(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUrl(*reinterpret_cast<QUrl*>(_v)); break;
        case 1: _t->setId(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setApiKey(*reinterpret_cast<QByteArray*>(_v)); break;
        default: break;
        }
    }
}
QT_WARNING_POP
