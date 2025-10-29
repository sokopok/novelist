/****************************************************************************
** Meta object code from reading C++ file 'responsesrequestutils.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/responsesrequestutils.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'responsesrequestutils.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai4BaseE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Base::qt_create_metaobjectdata<qt_meta_tag_ZN2ai4BaseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Base",
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
    return QtMocHelpers::metaObjectData<Base, qt_meta_tag_ZN2ai4BaseE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Base::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai4BaseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai4BaseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai4BaseE_t>.metaTypes,
    nullptr
} };

void ai::Base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Base *>(_o);
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
struct qt_meta_tag_ZN2ai6AiBaseE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::AiBase::qt_create_metaobjectdata<qt_meta_tag_ZN2ai6AiBaseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::AiBase",
        "QML.Element",
        "AiBase",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "AiBase is an abstract base class",
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
        QtMocHelpers::PropertyData<ai::UtilityType>(7, 0x80000000 | 8, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'extra'
        QtMocHelpers::PropertyData<QJsonObject>(9, QMetaType::QJsonObject, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'empty'
        QtMocHelpers::PropertyData<bool>(10, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'valid'
        QtMocHelpers::PropertyData<bool>(11, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<AiBase, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::AiBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6AiBaseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6AiBaseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai6AiBaseE_t>.metaTypes,
    nullptr
} };

void ai::AiBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AiBase *>(_o);
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

const QMetaObject *ai::AiBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::AiBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6AiBaseE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ai::AiBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN2ai12ConversationE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Conversation::qt_create_metaobjectdata<qt_meta_tag_ZN2ai12ConversationE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Conversation",
        "id"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Conversation, qt_meta_tag_ZN2ai12ConversationE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Conversation::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai12ConversationE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai12ConversationE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai12ConversationE_t>.metaTypes,
    nullptr
} };

void ai::Conversation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Conversation *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
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
namespace {
struct qt_meta_tag_ZN2ai7MessageE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Message::qt_create_metaobjectdata<qt_meta_tag_ZN2ai7MessageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Message",
        "id",
        "role",
        "Role",
        "roleAsString",
        "status",
        "Status",
        "statusAsString",
        "Status_InProgress",
        "Status_Completed",
        "Status_Incomplete",
        "Status_Custom",
        "Role_System",
        "Role_Assistant",
        "Role_User",
        "Role_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'role'
        QtMocHelpers::PropertyData<Role>(2, 0x80000000 | 3, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'roleAsString'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final),
        // property 'status'
        QtMocHelpers::PropertyData<Status>(5, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'statusAsString'
        QtMocHelpers::PropertyData<QString>(7, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Status'
        QtMocHelpers::EnumData<Status>(6, 6, QMC::EnumFlags{}).add({
            {    8, Status::Status_InProgress },
            {    9, Status::Status_Completed },
            {   10, Status::Status_Incomplete },
            {   11, Status::Status_Custom },
        }),
        // enum 'Role'
        QtMocHelpers::EnumData<Role>(3, 3, QMC::EnumFlags{}).add({
            {   12, Role::Role_System },
            {   13, Role::Role_Assistant },
            {   14, Role::Role_User },
            {   15, Role::Role_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<Message, qt_meta_tag_ZN2ai7MessageE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Message::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai7MessageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai7MessageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai7MessageE_t>.metaTypes,
    nullptr
} };

void ai::Message::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Message *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<Role*>(_v) = _t->role(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->roleAsString(); break;
        case 3: *reinterpret_cast<Status*>(_v) = _t->status(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->statusAsString(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setRole(*reinterpret_cast<Role*>(_v)); break;
        case 2: _t->setRole(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setStatus(*reinterpret_cast<Status*>(_v)); break;
        case 4: _t->setStatus(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai11IncludeListE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::IncludeList::qt_create_metaobjectdata<qt_meta_tag_ZN2ai11IncludeListE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::IncludeList",
        "Include",
        "NoInclude",
        "IncludeWebSearchCallActionSources",
        "IncludeCodeInterpreterCallOutputs",
        "IncludeMessageInputImageImageUrl",
        "IncludeMessageOutputTextLogProbs",
        "IncludeReasoningEncryptedContent",
        "IncludeComputerCallOutputImageUrl",
        "IncludeFileSearchCallResults"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Include'
        QtMocHelpers::EnumData<Include>(1, 1, QMC::EnumFlags{}).add({
            {    2, Include::NoInclude },
            {    3, Include::IncludeWebSearchCallActionSources },
            {    4, Include::IncludeCodeInterpreterCallOutputs },
            {    5, Include::IncludeMessageInputImageImageUrl },
            {    6, Include::IncludeMessageOutputTextLogProbs },
            {    7, Include::IncludeReasoningEncryptedContent },
            {    8, Include::IncludeComputerCallOutputImageUrl },
            {    9, Include::IncludeFileSearchCallResults },
        }),
    };
    return QtMocHelpers::metaObjectData<IncludeList, qt_meta_tag_ZN2ai11IncludeListE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::IncludeList::staticMetaObject = { {
    QtPrivate::MetaObjectForType<StringList>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai11IncludeListE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai11IncludeListE_t>.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai11IncludeListE_t>.metaTypes,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN2ai9InputTextE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputText::qt_create_metaobjectdata<qt_meta_tag_ZN2ai9InputTextE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputText",
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
    return QtMocHelpers::metaObjectData<InputText, qt_meta_tag_ZN2ai9InputTextE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputText::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9InputTextE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9InputTextE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai9InputTextE_t>.metaTypes,
    nullptr
} };

void ai::InputText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputText *>(_o);
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
struct qt_meta_tag_ZN2ai10InputImageE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputImage::qt_create_metaobjectdata<qt_meta_tag_ZN2ai10InputImageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputImage",
        "detail",
        "Detail",
        "detailAsString",
        "fileId",
        "imageUrl",
        "Detail_Auto",
        "Detail_Low",
        "Detail_High",
        "Detail_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'detail'
        QtMocHelpers::PropertyData<Detail>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'detailAsString'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final),
        // property 'fileId'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'imageUrl'
        QtMocHelpers::PropertyData<QUrl>(5, QMetaType::QUrl, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Detail'
        QtMocHelpers::EnumData<Detail>(2, 2, QMC::EnumFlags{}).add({
            {    6, Detail::Detail_Auto },
            {    7, Detail::Detail_Low },
            {    8, Detail::Detail_High },
            {    9, Detail::Detail_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<InputImage, qt_meta_tag_ZN2ai10InputImageE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputImage::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10InputImageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10InputImageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai10InputImageE_t>.metaTypes,
    nullptr
} };

void ai::InputImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputImage *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<Detail*>(_v) = _t->detail(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->detailAsString(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->fileId(); break;
        case 3: *reinterpret_cast<QUrl*>(_v) = _t->imageUrl(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDetail(*reinterpret_cast<Detail*>(_v)); break;
        case 1: _t->setDetail(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setFileId(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setImageUrl(*reinterpret_cast<QUrl*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai9InputFileE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputFile::qt_create_metaobjectdata<qt_meta_tag_ZN2ai9InputFileE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputFile",
        "fileId",
        "fileUrl",
        "fileData",
        "filename"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'fileId'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'fileUrl'
        QtMocHelpers::PropertyData<QUrl>(2, QMetaType::QUrl, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'fileData'
        QtMocHelpers::PropertyData<QByteArray>(3, QMetaType::QByteArray, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'filename'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InputFile, qt_meta_tag_ZN2ai9InputFileE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputFile::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9InputFileE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9InputFileE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai9InputFileE_t>.metaTypes,
    nullptr
} };

void ai::InputFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputFile *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->fileId(); break;
        case 1: *reinterpret_cast<QUrl*>(_v) = _t->fileUrl(); break;
        case 2: *reinterpret_cast<QByteArray*>(_v) = _t->fileData(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->filename(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFileId(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setFileUrl(*reinterpret_cast<QUrl*>(_v)); break;
        case 2: _t->setFileData(*reinterpret_cast<QByteArray*>(_v)); break;
        case 3: _t->setFilename(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai10InputAudioE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputAudio::qt_create_metaobjectdata<qt_meta_tag_ZN2ai10InputAudioE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputAudio",
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
    return QtMocHelpers::metaObjectData<InputAudio, qt_meta_tag_ZN2ai10InputAudioE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputAudio::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10InputAudioE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai10InputAudioE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai10InputAudioE_t>.metaTypes,
    nullptr
} };

void ai::InputAudio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputAudio *>(_o);
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
struct qt_meta_tag_ZN2ai19InputMessageContentE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputMessageContent::qt_create_metaobjectdata<qt_meta_tag_ZN2ai19InputMessageContentE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputMessageContent",
        "isText",
        "isImage",
        "isFile",
        "text",
        "InputText",
        "image",
        "InputImage",
        "file",
        "InputFile"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isText'
        QtMocHelpers::PropertyData<bool>(1, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'isImage'
        QtMocHelpers::PropertyData<bool>(2, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'isFile'
        QtMocHelpers::PropertyData<bool>(3, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'text'
        QtMocHelpers::PropertyData<InputText>(4, 0x80000000 | 5, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'image'
        QtMocHelpers::PropertyData<InputImage>(6, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'file'
        QtMocHelpers::PropertyData<InputFile>(8, 0x80000000 | 9, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InputMessageContent, qt_meta_tag_ZN2ai19InputMessageContentE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputMessageContent::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai19InputMessageContentE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai19InputMessageContentE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai19InputMessageContentE_t>.metaTypes,
    nullptr
} };

void ai::InputMessageContent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputMessageContent *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isText(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isImage(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isFile(); break;
        case 3: *reinterpret_cast<InputText*>(_v) = _t->text(); break;
        case 4: *reinterpret_cast<InputImage*>(_v) = _t->image(); break;
        case 5: *reinterpret_cast<InputFile*>(_v) = _t->file(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 3: _t->setText(*reinterpret_cast<InputText*>(_v)); break;
        case 4: _t->setImage(*reinterpret_cast<InputImage*>(_v)); break;
        case 5: _t->setFile(*reinterpret_cast<InputFile*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai12InputMessageE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputMessage::qt_create_metaobjectdata<qt_meta_tag_ZN2ai12InputMessageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputMessage",
        "content",
        "QList<InputMessageContent>"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'content'
        QtMocHelpers::PropertyData<QList<InputMessageContent>>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InputMessage, qt_meta_tag_ZN2ai12InputMessageE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputMessage::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Message>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai12InputMessageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai12InputMessageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai12InputMessageE_t>.metaTypes,
    nullptr
} };

void ai::InputMessage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputMessage *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<InputMessageContent>*>(_v) = _t->content(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setContent(*reinterpret_cast<QList<InputMessageContent>*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai13ItemReferenceE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ItemReference::qt_create_metaobjectdata<qt_meta_tag_ZN2ai13ItemReferenceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ItemReference",
        "id"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ItemReference, qt_meta_tag_ZN2ai13ItemReferenceE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ItemReference::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13ItemReferenceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13ItemReferenceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai13ItemReferenceE_t>.metaTypes,
    nullptr
} };

void ai::ItemReference::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<ItemReference *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
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
namespace {
struct qt_meta_tag_ZN2ai15AiItemReferenceE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::AiItemReference::qt_create_metaobjectdata<qt_meta_tag_ZN2ai15AiItemReferenceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::AiItemReference",
        "QML.Element",
        "AiItemReference",
        "id"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<AiItemReference, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::AiItemReference::staticMetaObject = { {
    QMetaObject::SuperData::link<AiBase::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15AiItemReferenceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15AiItemReferenceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai15AiItemReferenceE_t>.metaTypes,
    nullptr
} };

void ai::AiItemReference::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AiItemReference *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->id(); break;
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

const QMetaObject *ai::AiItemReference::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::AiItemReference::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15AiItemReferenceE_t>.strings))
        return static_cast<void*>(this);
    return AiBase::qt_metacast(_clname);
}

int ai::AiItemReference::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AiBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
namespace {
struct qt_meta_tag_ZN2ai9InputItemE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::InputItem::qt_create_metaobjectdata<qt_meta_tag_ZN2ai9InputItemE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::InputItem",
        "isMessage",
        "isItemReference",
        "message",
        "InputMessage",
        "itemReference",
        "ItemReference"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isMessage'
        QtMocHelpers::PropertyData<bool>(1, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'isItemReference'
        QtMocHelpers::PropertyData<bool>(2, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Final),
        // property 'message'
        QtMocHelpers::PropertyData<InputMessage>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'itemReference'
        QtMocHelpers::PropertyData<ItemReference>(5, 0x80000000 | 6, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InputItem, qt_meta_tag_ZN2ai9InputItemE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::InputItem::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9InputItemE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9InputItemE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai9InputItemE_t>.metaTypes,
    nullptr
} };

void ai::InputItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<InputItem *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isMessage(); break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isItemReference(); break;
        case 2: *reinterpret_cast<InputMessage*>(_v) = _t->message(); break;
        case 3: *reinterpret_cast<ItemReference*>(_v) = _t->itemReference(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setMessage(*reinterpret_cast<InputMessage*>(_v)); break;
        case 3: _t->setItemReference(*reinterpret_cast<ItemReference*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai5InputE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Input::qt_create_metaobjectdata<qt_meta_tag_ZN2ai5InputE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Input",
        "QML.Element",
        "aiInput",
        "items",
        "QList<InputItem>"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'items'
        QtMocHelpers::PropertyData<QList<InputItem>>(3, 0x80000000 | 4, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<Input, void>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::Input::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai5InputE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai5InputE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai5InputE_t>.metaTypes,
    nullptr
} };

void ai::Input::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Input *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<InputItem>*>(_v) = _t->items(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setItems(*reinterpret_cast<QList<InputItem>*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai6PromptE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Prompt::qt_create_metaobjectdata<qt_meta_tag_ZN2ai6PromptE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Prompt",
        "variables",
        "QVariantMap",
        "id",
        "version"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'variables'
        QtMocHelpers::PropertyData<QVariantMap>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'id'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'version'
        QtMocHelpers::PropertyData<QString>(4, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Prompt, qt_meta_tag_ZN2ai6PromptE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Prompt::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6PromptE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai6PromptE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai6PromptE_t>.metaTypes,
    nullptr
} };

void ai::Prompt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Prompt *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantMap*>(_v) = _t->variables(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->id(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->version(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVariables(*reinterpret_cast<QVariantMap*>(_v)); break;
        case 1: _t->setId(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setVersion(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai9ReasoningE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Reasoning::qt_create_metaobjectdata<qt_meta_tag_ZN2ai9ReasoningE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Reasoning",
        "effort",
        "Effort",
        "effortAsString",
        "summary",
        "Summary",
        "summaryAsString",
        "Effort_Minimal",
        "Effort_Low",
        "Effort_Medium",
        "Effort_High",
        "Effort_Custom",
        "Summary_Auto",
        "Summary_Concise",
        "Summary_Detailed",
        "Summary_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'effort'
        QtMocHelpers::PropertyData<Effort>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'effortAsString'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable),
        // property 'summary'
        QtMocHelpers::PropertyData<Summary>(4, 0x80000000 | 5, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'summaryAsString'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Effort'
        QtMocHelpers::EnumData<Effort>(2, 2, QMC::EnumFlags{}).add({
            {    7, Effort::Effort_Minimal },
            {    8, Effort::Effort_Low },
            {    9, Effort::Effort_Medium },
            {   10, Effort::Effort_High },
            {   11, Effort::Effort_Custom },
        }),
        // enum 'Summary'
        QtMocHelpers::EnumData<Summary>(5, 5, QMC::EnumFlags{}).add({
            {   12, Summary::Summary_Auto },
            {   13, Summary::Summary_Concise },
            {   14, Summary::Summary_Detailed },
            {   15, Summary::Summary_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<Reasoning, qt_meta_tag_ZN2ai9ReasoningE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Reasoning::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9ReasoningE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai9ReasoningE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai9ReasoningE_t>.metaTypes,
    nullptr
} };

void ai::Reasoning::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Reasoning *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<Effort*>(_v) = _t->effort(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->effortAsString(); break;
        case 2: *reinterpret_cast<Summary*>(_v) = _t->summary(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->summaryAsString(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEffort(*reinterpret_cast<Effort*>(_v)); break;
        case 1: _t->setEffort(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setSummary(*reinterpret_cast<Summary*>(_v)); break;
        case 3: _t->setSummary(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai7RefusalE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Refusal::qt_create_metaobjectdata<qt_meta_tag_ZN2ai7RefusalE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Refusal",
        "refusal"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'refusal'
        QtMocHelpers::PropertyData<QString>(1, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Refusal, qt_meta_tag_ZN2ai7RefusalE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Refusal::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai7RefusalE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai7RefusalE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai7RefusalE_t>.metaTypes,
    nullptr
} };

void ai::Refusal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Refusal *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->refusal(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRefusal(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai13StreamOptionsE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::StreamOptions::qt_create_metaobjectdata<qt_meta_tag_ZN2ai13StreamOptionsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::StreamOptions",
        "includeObfuscation"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'includeObfuscation'
        QtMocHelpers::PropertyData<bool>(1, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<StreamOptions, qt_meta_tag_ZN2ai13StreamOptionsE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::StreamOptions::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13StreamOptionsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai13StreamOptionsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai13StreamOptionsE_t>.metaTypes,
    nullptr
} };

void ai::StreamOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<StreamOptions *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->includeObfuscation(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIncludeObfuscation(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}
namespace {
struct qt_meta_tag_ZN2ai19ImageGenerationToolE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ImageGenerationTool::qt_create_metaobjectdata<qt_meta_tag_ZN2ai19ImageGenerationToolE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ImageGenerationTool",
        "Background",
        "Background_Auto",
        "Background_Transparent",
        "Background_Opaque",
        "Background_Custom",
        "InputFidelity",
        "InputFidelity_High",
        "InputFidelity_Low",
        "InputFidelity_Custom",
        "OutputFormat",
        "OutputFormat_Png",
        "OutputFormat_Jpeg",
        "OutputFormat_Webp",
        "OutputFormat_Custom",
        "Model",
        "Model_DallE2",
        "Model_DallE3",
        "Model_GptImage1",
        "Model_Custom",
        "Moderation",
        "Moderation_Auto",
        "Moderation_Low",
        "Moderation_Custom",
        "Quality",
        "Quality_Auto",
        "Quality_Low",
        "Quality_Medium",
        "Quality_High",
        "Quality_Custom",
        "Size",
        "Size_Auto",
        "Size_1024x1024",
        "Size_1024x1536",
        "Size_1536x1024",
        "Size_Custom"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Background'
        QtMocHelpers::EnumData<Background>(1, 1, QMC::EnumFlags{}).add({
            {    2, Background::Background_Auto },
            {    3, Background::Background_Transparent },
            {    4, Background::Background_Opaque },
            {    5, Background::Background_Custom },
        }),
        // enum 'InputFidelity'
        QtMocHelpers::EnumData<InputFidelity>(6, 6, QMC::EnumFlags{}).add({
            {    7, InputFidelity::InputFidelity_High },
            {    8, InputFidelity::InputFidelity_Low },
            {    9, InputFidelity::InputFidelity_Custom },
        }),
        // enum 'OutputFormat'
        QtMocHelpers::EnumData<OutputFormat>(10, 10, QMC::EnumFlags{}).add({
            {   11, OutputFormat::OutputFormat_Png },
            {   12, OutputFormat::OutputFormat_Jpeg },
            {   13, OutputFormat::OutputFormat_Webp },
            {   14, OutputFormat::OutputFormat_Custom },
        }),
        // enum 'Model'
        QtMocHelpers::EnumData<Model>(15, 15, QMC::EnumFlags{}).add({
            {   16, Model::Model_DallE2 },
            {   17, Model::Model_DallE3 },
            {   18, Model::Model_GptImage1 },
            {   19, Model::Model_Custom },
        }),
        // enum 'Moderation'
        QtMocHelpers::EnumData<Moderation>(20, 20, QMC::EnumFlags{}).add({
            {   21, Moderation::Moderation_Auto },
            {   22, Moderation::Moderation_Low },
            {   23, Moderation::Moderation_Custom },
        }),
        // enum 'Quality'
        QtMocHelpers::EnumData<Quality>(24, 24, QMC::EnumFlags{}).add({
            {   25, Quality::Quality_Auto },
            {   26, Quality::Quality_Low },
            {   27, Quality::Quality_Medium },
            {   28, Quality::Quality_High },
            {   29, Quality::Quality_Custom },
        }),
        // enum 'Size'
        QtMocHelpers::EnumData<Size>(30, 30, QMC::EnumFlags{}).add({
            {   31, Size::Size_Auto },
            {   32, Size::Size_1024x1024 },
            {   33, Size::Size_1024x1536 },
            {   34, Size::Size_1536x1024 },
            {   35, Size::Size_Custom },
        }),
    };
    return QtMocHelpers::metaObjectData<ImageGenerationTool, qt_meta_tag_ZN2ai19ImageGenerationToolE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::ImageGenerationTool::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai19ImageGenerationToolE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai19ImageGenerationToolE_t>.data,
    nullptr,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai19ImageGenerationToolE_t>.metaTypes,
    nullptr
} };

namespace {
struct qt_meta_tag_ZN2ai4ToolE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::Tool::qt_create_metaobjectdata<qt_meta_tag_ZN2ai4ToolE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::Tool",
        "imageGeneration",
        "ImageGenerationTool"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'imageGeneration'
        QtMocHelpers::PropertyData<ImageGenerationTool>(1, 0x80000000 | 2, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Tool, qt_meta_tag_ZN2ai4ToolE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ai::Tool::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Base>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai4ToolE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai4ToolE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai4ToolE_t>.metaTypes,
    nullptr
} };

void ai::Tool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Tool *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ImageGenerationTool*>(_v) = _t->imageGeneration(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setImageGeneration(*reinterpret_cast<ImageGenerationTool*>(_v)); break;
        default: break;
        }
    }
}
QT_WARNING_POP
