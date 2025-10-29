/****************************************************************************
** Meta object code from reading C++ file 'responsesrequest.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/responsesrequest.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'responsesrequest.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai16ResponsesRequestE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ResponsesRequest::qt_create_metaobjectdata<qt_meta_tag_ZN2ai16ResponsesRequestE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ResponsesRequest",
        "QML.Element",
        "responsesRequest",
        "QML.Creatable",
        "true",
        "QML.CreationMethod",
        "construct",
        "setInput",
        "",
        "text",
        "background",
        "input",
        "ai::Input",
        "instructions",
        "previousResponseId",
        "Attribute",
        "BackgroundAttribute",
        "ConversationAttribute",
        "IncludeAttribute",
        "InputAttribute",
        "InstructionsAttribute",
        "MaxOutputTokensAttribute",
        "MaxToolCallsAttribute",
        "MetadataAttribute",
        "ModelAttribute",
        "ParallelToolCallsAttribute",
        "PreviousResponseIdAttribute",
        "PromptAttribute",
        "PromptCacheKeyAttribute",
        "ReasoningAttribute",
        "SafetyIdentifierAttribute",
        "ServiceTierAttribute",
        "StoredAttribute",
        "StreamingAttribute",
        "StreamOptionsAttribute",
        "TemperatureAttribute",
        "TextAttribute",
        "ToolChoiceAttribute",
        "ToolsAttribute",
        "TopLogprobsAttribute",
        "TopPAttribute",
        "TruncationAttribute",
        "NumAttributes",
        "Model",
        "Model_Gpt5",
        "Model_Gpt5Nano",
        "Model_Gpt5Mini",
        "Model_Gpt5Pro",
        "Model_Gpt41",
        "Model_Gpt41Mini",
        "Model_Custom",
        "ServiceTier",
        "ServiceTier_Auto",
        "ServiceTier_Default",
        "ServiceTier_Flex",
        "ServiceTier_Priority",
        "ServiceTier_Custom",
        "Truncation",
        "Truncation_Auto",
        "Truncation_Disabled",
        "Truncation_Custom"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'setInput'
        QtMocHelpers::SlotData<bool(const QString &)>(7, 8, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'background'
        QtMocHelpers::PropertyData<bool>(10, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'input'
        QtMocHelpers::PropertyData<ai::Input>(11, 0x80000000 | 12, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final),
        // property 'instructions'
        QtMocHelpers::PropertyData<QString>(13, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
        // property 'previousResponseId'
        QtMocHelpers::PropertyData<QString>(14, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Attribute'
        QtMocHelpers::EnumData<Attribute>(15, 15, QMC::EnumFlags{}).add({
            {   16, Attribute::BackgroundAttribute },
            {   17, Attribute::ConversationAttribute },
            {   18, Attribute::IncludeAttribute },
            {   19, Attribute::InputAttribute },
            {   20, Attribute::InstructionsAttribute },
            {   21, Attribute::MaxOutputTokensAttribute },
            {   22, Attribute::MaxToolCallsAttribute },
            {   23, Attribute::MetadataAttribute },
            {   24, Attribute::ModelAttribute },
            {   25, Attribute::ParallelToolCallsAttribute },
            {   26, Attribute::PreviousResponseIdAttribute },
            {   27, Attribute::PromptAttribute },
            {   28, Attribute::PromptCacheKeyAttribute },
            {   29, Attribute::ReasoningAttribute },
            {   30, Attribute::SafetyIdentifierAttribute },
            {   31, Attribute::ServiceTierAttribute },
            {   32, Attribute::StoredAttribute },
            {   33, Attribute::StreamingAttribute },
            {   34, Attribute::StreamOptionsAttribute },
            {   35, Attribute::TemperatureAttribute },
            {   36, Attribute::TextAttribute },
            {   37, Attribute::ToolChoiceAttribute },
            {   38, Attribute::ToolsAttribute },
            {   39, Attribute::TopLogprobsAttribute },
            {   40, Attribute::TopPAttribute },
            {   41, Attribute::TruncationAttribute },
            {   42, Attribute::NumAttributes },
        }),
        // enum 'Model'
        QtMocHelpers::EnumData<Model>(43, 43, QMC::EnumFlags{}).add({
            {   44, Model::Model_Gpt5 },
            {   45, Model::Model_Gpt5Nano },
            {   46, Model::Model_Gpt5Mini },
            {   47, Model::Model_Gpt5Pro },
            {   48, Model::Model_Gpt41 },
            {   49, Model::Model_Gpt41Mini },
            {   50, Model::Model_Custom },
        }),
        // enum 'ServiceTier'
        QtMocHelpers::EnumData<ServiceTier>(51, 51, QMC::EnumFlags{}).add({
            {   52, ServiceTier::ServiceTier_Auto },
            {   53, ServiceTier::ServiceTier_Default },
            {   54, ServiceTier::ServiceTier_Flex },
            {   55, ServiceTier::ServiceTier_Priority },
            {   56, ServiceTier::ServiceTier_Custom },
        }),
        // enum 'Truncation'
        QtMocHelpers::EnumData<Truncation>(57, 57, QMC::EnumFlags{}).add({
            {   58, Truncation::Truncation_Auto },
            {   59, Truncation::Truncation_Disabled },
            {   60, Truncation::Truncation_Custom },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<ResponsesRequest, void>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::ResponsesRequest::staticMetaObject = { {
    QtPrivate::MetaObjectForType<Request>::value,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai16ResponsesRequestE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai16ResponsesRequestE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai16ResponsesRequestE_t>.metaTypes,
    nullptr
} };

void ai::ResponsesRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<ResponsesRequest *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = _t->setInput((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->background(); break;
        case 1: *reinterpret_cast<ai::Input*>(_v) = _t->input(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->instructions(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->previousResponseId(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackground(*reinterpret_cast<bool*>(_v)); break;
        case 1: _t->setInput(*reinterpret_cast<ai::Input*>(_v)); break;
        case 2: _t->setInstructions(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setPreviousResponseId(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}
QT_WARNING_POP
