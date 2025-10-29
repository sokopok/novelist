/****************************************************************************
** Meta object code from reading C++ file 'imagesresponse.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/imagesresponse.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagesresponse.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai17ImageResponseDataE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ImageResponseData::qt_create_metaobjectdata<qt_meta_tag_ZN2ai17ImageResponseDataE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ImageResponseData",
        "utilityType",
        "ai::UtilityType",
        "extra",
        "empty",
        "valid",
        "b64Json",
        "revisedPrompt",
        "url"
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
        // property 'b64Json'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'revisedPrompt'
        QtMocHelpers::PropertyData<QString>(7, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'url'
        QtMocHelpers::PropertyData<QString>(8, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ImageResponseData, qt_meta_tag_ZN2ai17ImageResponseDataE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ImageResponseData::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai17ImageResponseDataE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai17ImageResponseDataE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai17ImageResponseDataE_t>.metaTypes,
    nullptr
} };

void ai::ImageResponseData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<ImageResponseData *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ai::UtilityType*>(_v) = _t->utilityType(); break;
        case 1: *reinterpret_cast<QJsonObject*>(_v) = _t->extra(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isEmpty(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isValid(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->b64Json(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->revisedPrompt(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->url(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setB64Json(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setRevisedPrompt(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setUrl(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai18ImageResponseUsageE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ImageResponseUsage::qt_create_metaobjectdata<qt_meta_tag_ZN2ai18ImageResponseUsageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ImageResponseUsage",
        "utilityType",
        "ai::UtilityType",
        "extra",
        "empty",
        "valid",
        "inputTokens",
        "imageTokens",
        "textTokens",
        "outputTokens",
        "totalTokens"
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
        // property 'inputTokens'
        QtMocHelpers::PropertyData<int>(6, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'imageTokens'
        QtMocHelpers::PropertyData<int>(7, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'textTokens'
        QtMocHelpers::PropertyData<int>(8, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'outputTokens'
        QtMocHelpers::PropertyData<int>(9, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'totalTokens'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ImageResponseUsage, qt_meta_tag_ZN2ai18ImageResponseUsageE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ImageResponseUsage::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai18ImageResponseUsageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai18ImageResponseUsageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai18ImageResponseUsageE_t>.metaTypes,
    nullptr
} };

void ai::ImageResponseUsage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<ImageResponseUsage *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ai::UtilityType*>(_v) = _t->utilityType(); break;
        case 1: *reinterpret_cast<QJsonObject*>(_v) = _t->extra(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isEmpty(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isValid(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->inputTokens(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->imageTokens(); break;
        case 6: *reinterpret_cast<int*>(_v) = _t->textTokens(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->outputTokens(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->totalTokens(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setInputTokens(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setImageTokens(*reinterpret_cast<int*>(_v)); break;
        case 6: _t->setTextTokens(*reinterpret_cast<int*>(_v)); break;
        case 7: _t->setOutputTokens(*reinterpret_cast<int*>(_v)); break;
        case 8: _t->setTotalTokens(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai14ImagesResponseE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ImagesResponse::qt_create_metaobjectdata<qt_meta_tag_ZN2ai14ImagesResponseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ImagesResponse",
        "QML.Element",
        "ImagesResponse",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "ImagesResponse is created internally"
    };

    QtMocHelpers::UintData qt_methods {
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
    return QtMocHelpers::metaObjectData<ImagesResponse, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::ImagesResponse::staticMetaObject = { {
    QMetaObject::SuperData::link<ai::Response::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai14ImagesResponseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai14ImagesResponseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai14ImagesResponseE_t>.metaTypes,
    nullptr
} };

void ai::ImagesResponse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ImagesResponse *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *ai::ImagesResponse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::ImagesResponse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai14ImagesResponseE_t>.strings))
        return static_cast<void*>(this);
    return ai::Response::qt_metacast(_clname);
}

int ai::ImagesResponse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ai::Response::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
