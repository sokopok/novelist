/****************************************************************************
** Meta object code from reading C++ file 'responsesresponse.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/responsesresponse.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'responsesresponse.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai17ResponsesResponseE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ResponsesResponse::qt_create_metaobjectdata<qt_meta_tag_ZN2ai17ResponsesResponseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ResponsesResponse",
        "QML.Element",
        "ResponsesResponse",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "ResponsesResponse is created internally",
        "textGenerated",
        "",
        "text",
        "imageGenerated",
        "image",
        "backgroundChanged",
        "conversationChanged",
        "inputChanged",
        "reasoningChanged",
        "metadataChanged",
        "modelChanged",
        "streamingChanged",
        "streamOptionsChanged",
        "Attribute",
        "BackgroundAttribute",
        "ConversationAttribute",
        "CreatedAtAttribute",
        "ErrorAttribute",
        "IncompleteDetailsAttribute",
        "InstructionsAttribute",
        "MaxOutputTokensAttribute",
        "MaxToolCallsAttribute",
        "MetadataAttribute",
        "ModelAttribute",
        "ObjectAttribute",
        "OutputAttribute",
        "OutputTextAttribute",
        "ParallelToolCallsAttribute",
        "PreviousResponseIdAttribute",
        "PromptAttribute",
        "PromptCacheKeyAttribute",
        "ReasoningAttribute",
        "SafetyIdentifierAttribute",
        "ServiceTierAttribute",
        "StatusAttribute",
        "TemperatureAttribute",
        "TextAttribute",
        "ToolChoiceAttribute",
        "ToolsAttribute",
        "TopLogprobsAttribute",
        "TopPAttribute",
        "TruncationAttribute",
        "UsageAttribute",
        "NumAttributes",
        "Status",
        "Status_Completed",
        "Status_Failed",
        "Status_InProgress",
        "Status_Cancelled",
        "Status_Queued",
        "Status_Incomplete",
        "Status_Custom"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'textGenerated'
        QtMocHelpers::SignalData<void(const QString &)>(7, 8, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'imageGenerated'
        QtMocHelpers::SignalData<void(const QImage &)>(10, 8, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QImage, 11 },
        }}),
        // Signal 'backgroundChanged'
        QtMocHelpers::SignalData<void()>(12, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'conversationChanged'
        QtMocHelpers::SignalData<void()>(13, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'inputChanged'
        QtMocHelpers::SignalData<void()>(14, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reasoningChanged'
        QtMocHelpers::SignalData<void()>(15, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'metadataChanged'
        QtMocHelpers::SignalData<void()>(16, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'modelChanged'
        QtMocHelpers::SignalData<void()>(17, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'streamingChanged'
        QtMocHelpers::SignalData<void()>(18, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'streamOptionsChanged'
        QtMocHelpers::SignalData<void()>(19, 8, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Attribute'
        QtMocHelpers::EnumData<Attribute>(20, 20, QMC::EnumFlags{}).add({
            {   21, Attribute::BackgroundAttribute },
            {   22, Attribute::ConversationAttribute },
            {   23, Attribute::CreatedAtAttribute },
            {   24, Attribute::ErrorAttribute },
            {   25, Attribute::IncompleteDetailsAttribute },
            {   26, Attribute::InstructionsAttribute },
            {   27, Attribute::MaxOutputTokensAttribute },
            {   28, Attribute::MaxToolCallsAttribute },
            {   29, Attribute::MetadataAttribute },
            {   30, Attribute::ModelAttribute },
            {   31, Attribute::ObjectAttribute },
            {   32, Attribute::OutputAttribute },
            {   33, Attribute::OutputTextAttribute },
            {   34, Attribute::ParallelToolCallsAttribute },
            {   35, Attribute::PreviousResponseIdAttribute },
            {   36, Attribute::PromptAttribute },
            {   37, Attribute::PromptCacheKeyAttribute },
            {   38, Attribute::ReasoningAttribute },
            {   39, Attribute::SafetyIdentifierAttribute },
            {   40, Attribute::ServiceTierAttribute },
            {   41, Attribute::StatusAttribute },
            {   42, Attribute::TemperatureAttribute },
            {   43, Attribute::TextAttribute },
            {   44, Attribute::ToolChoiceAttribute },
            {   45, Attribute::ToolsAttribute },
            {   46, Attribute::TopLogprobsAttribute },
            {   47, Attribute::TopPAttribute },
            {   48, Attribute::TruncationAttribute },
            {   49, Attribute::UsageAttribute },
            {   50, Attribute::NumAttributes },
        }),
        // enum 'Status'
        QtMocHelpers::EnumData<Status>(51, 51, QMC::EnumFlags{}).add({
            {   52, Status::Status_Completed },
            {   53, Status::Status_Failed },
            {   54, Status::Status_InProgress },
            {   55, Status::Status_Cancelled },
            {   56, Status::Status_Queued },
            {   57, Status::Status_Incomplete },
            {   58, Status::Status_Custom },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<ResponsesResponse, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::ResponsesResponse::staticMetaObject = { {
    QMetaObject::SuperData::link<Response::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai17ResponsesResponseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai17ResponsesResponseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai17ResponsesResponseE_t>.metaTypes,
    nullptr
} };

void ai::ResponsesResponse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ResponsesResponse *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->textGenerated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])), QPrivateSignal()); break;
        case 1: _t->imageGenerated((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])), QPrivateSignal()); break;
        case 2: _t->backgroundChanged(QPrivateSignal()); break;
        case 3: _t->conversationChanged(QPrivateSignal()); break;
        case 4: _t->inputChanged(QPrivateSignal()); break;
        case 5: _t->reasoningChanged(QPrivateSignal()); break;
        case 6: _t->metadataChanged(QPrivateSignal()); break;
        case 7: _t->modelChanged(QPrivateSignal()); break;
        case 8: _t->streamingChanged(QPrivateSignal()); break;
        case 9: _t->streamOptionsChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(const QString & , QPrivateSignal)>(_a, &ResponsesResponse::textGenerated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(const QImage & , QPrivateSignal)>(_a, &ResponsesResponse::imageGenerated, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::backgroundChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::conversationChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::inputChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::reasoningChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::metadataChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::modelChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::streamingChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (ResponsesResponse::*)(QPrivateSignal)>(_a, &ResponsesResponse::streamOptionsChanged, 9))
            return;
    }
}

const QMetaObject *ai::ResponsesResponse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::ResponsesResponse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai17ResponsesResponseE_t>.strings))
        return static_cast<void*>(this);
    return Response::qt_metacast(_clname);
}

int ai::ResponsesResponse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Response::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ai::ResponsesResponse::textGenerated(const QString & _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ai::ResponsesResponse::imageGenerated(const QImage & _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void ai::ResponsesResponse::backgroundChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ai::ResponsesResponse::conversationChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ai::ResponsesResponse::inputChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ai::ResponsesResponse::reasoningChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void ai::ResponsesResponse::metadataChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void ai::ResponsesResponse::modelChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void ai::ResponsesResponse::streamingChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void ai::ResponsesResponse::streamOptionsChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}
QT_WARNING_POP
