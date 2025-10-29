/****************************************************************************
** Meta object code from reading C++ file 'responsesresponseutils.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/responsesresponseutils.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'responsesresponseutils.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai15ReasoningOutputE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ReasoningOutput::qt_create_metaobjectdata<qt_meta_tag_ZN2ai15ReasoningOutputE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ReasoningOutput",
        "status",
        "Status",
        "statusAsString",
        "Status_InProgress",
        "Status_Incomplete",
        "Status_Completed",
        "Status_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'status'
        QtMocHelpers::PropertyData<Status>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'statusAsString'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Status'
        QtMocHelpers::EnumData<Status>(2, 2, QMC::EnumFlags{}).add({
            {    4, Status::Status_InProgress },
            {    5, Status::Status_Incomplete },
            {    6, Status::Status_Completed },
            {    7, Status::Status_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<ReasoningOutput, qt_meta_tag_ZN2ai15ReasoningOutputE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ReasoningOutput::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15ReasoningOutputE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15ReasoningOutputE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai15ReasoningOutputE_t>.metaTypes,
    nullptr
} };

void ai::ReasoningOutput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<ReasoningOutput *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<Status*>(_v) = _t->status(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->statusAsString(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setStatus(*reinterpret_cast<Status*>(_v)); break;
        case 1: _t->setStatus(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai19ImageGenerationCallE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ImageGenerationCall::qt_create_metaobjectdata<qt_meta_tag_ZN2ai19ImageGenerationCallE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ImageGenerationCall",
        "id",
        "status",
        "Status",
        "result",
        "Status_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'status'
        QtMocHelpers::PropertyData<Status>(2, 0x80000000 | 3, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'result'
        QtMocHelpers::PropertyData<QImage>(4, QMetaType::QImage, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Status'
        QtMocHelpers::EnumData<Status>(3, 3, QMC::EnumFlags{}).add({
            {    5, Status::Status_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<ImageGenerationCall, qt_meta_tag_ZN2ai19ImageGenerationCallE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ImageGenerationCall::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai19ImageGenerationCallE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai19ImageGenerationCallE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai19ImageGenerationCallE_t>.metaTypes,
    nullptr
} };

void ai::ImageGenerationCall::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<ImageGenerationCall *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<Status*>(_v) = _t->status(); break;
        case 2: *reinterpret_cast<QImage*>(_v) = _t->result(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setStatus(*reinterpret_cast<Status*>(_v)); break;
        case 2: _t->setResult(*reinterpret_cast<QImage*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai10OutputTextE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::OutputText::qt_create_metaobjectdata<qt_meta_tag_ZN2ai10OutputTextE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::OutputText",
        "text"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'text'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OutputText, qt_meta_tag_ZN2ai10OutputTextE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::OutputText::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10OutputTextE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10OutputTextE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai10OutputTextE_t>.metaTypes,
    nullptr
} };

void ai::OutputText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<OutputText *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->text(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai20OutputMessageContentE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::OutputMessageContent::qt_create_metaobjectdata<qt_meta_tag_ZN2ai20OutputMessageContentE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::OutputMessageContent",
        "text",
        "OutputText",
        "refusal",
        "Refusal"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'text'
        QtMocHelpers::PropertyData<OutputText>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'refusal'
        QtMocHelpers::PropertyData<Refusal>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OutputMessageContent, qt_meta_tag_ZN2ai20OutputMessageContentE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::OutputMessageContent::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai20OutputMessageContentE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai20OutputMessageContentE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai20OutputMessageContentE_t>.metaTypes,
    nullptr
} };

void ai::OutputMessageContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<OutputMessageContent *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<OutputText*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast<Refusal*>(_v) = _t->refusal(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast<OutputText*>(_v)); break;
        case 1: _t->setRefusal(*reinterpret_cast<Refusal*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai13OutputMessageE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::OutputMessage::qt_create_metaobjectdata<qt_meta_tag_ZN2ai13OutputMessageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::OutputMessage",
        "content",
        "QList<OutputMessageContent>"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'content'
        QtMocHelpers::PropertyData<QList<OutputMessageContent>>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OutputMessage, qt_meta_tag_ZN2ai13OutputMessageE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::OutputMessage::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Message>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13OutputMessageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13OutputMessageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai13OutputMessageE_t>.metaTypes,
    nullptr
} };

void ai::OutputMessage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<OutputMessage *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<OutputMessageContent>*>(_v) = _t->content(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setContent(*reinterpret_cast<QList<OutputMessageContent>*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai10OutputItemE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::OutputItem::qt_create_metaobjectdata<qt_meta_tag_ZN2ai10OutputItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::OutputItem",
        "message",
        "OutputMessage",
        "imageGenerationCall",
        "ImageGenerationCall",
        "reasoning",
        "ReasoningOutput"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'message'
        QtMocHelpers::PropertyData<OutputMessage>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'imageGenerationCall'
        QtMocHelpers::PropertyData<ImageGenerationCall>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'reasoning'
        QtMocHelpers::PropertyData<ReasoningOutput>(5, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<OutputItem, qt_meta_tag_ZN2ai10OutputItemE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::OutputItem::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10OutputItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10OutputItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai10OutputItemE_t>.metaTypes,
    nullptr
} };

void ai::OutputItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<OutputItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<OutputMessage*>(_v) = _t->message(); break;
        case 1: *reinterpret_cast<ImageGenerationCall*>(_v) = _t->imageGenerationCall(); break;
        case 2: *reinterpret_cast<ReasoningOutput*>(_v) = _t->reasoning(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMessage(*reinterpret_cast<OutputMessage*>(_v)); break;
        case 1: _t->setImageGenerationCall(*reinterpret_cast<ImageGenerationCall*>(_v)); break;
        case 2: _t->setReasoning(*reinterpret_cast<ReasoningOutput*>(_v)); break;
        default: break;
        }
    }
}
QT_WARNING_POP
