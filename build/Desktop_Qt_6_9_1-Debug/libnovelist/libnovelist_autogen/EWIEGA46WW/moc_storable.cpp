/****************************************************************************
** Meta object code from reading C++ file 'storable.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/storable.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'storable.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8StorableE_t {};
} // unnamed namespace

template <> constexpr inline auto Storable::qt_create_metaobjectdata<qt_meta_tag_ZN8StorableE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Storable",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "Storable is a base class",
        "rowidChanged",
        "",
        "typeChanged",
        "storageChanged",
        "modifiedChanged",
        "createdByChanged",
        "updatedByChanged",
        "createdAtChanged",
        "updatedAtChanged",
        "reloaded",
        "saved",
        "recycled",
        "versionChanged",
        "rowid",
        "type",
        "modified",
        "createdBy",
        "updatedBy",
        "createdAt",
        "updatedAt",
        "version",
        "Type",
        "Type_Unknown",
        "Type_Storable",
        "Type_Node",
        "Type_Field",
        "Type_Element",
        "Type_Value",
        "Type_Project",
        "Type_NodeType",
        "Type_FieldType",
        "Type_ElementType",
        "Type_ValueType",
        "Type_ProjectType",
        "Flag",
        "NoFlag",
        "Flag_Modified",
        "Flag_Saving",
        "Flag_Loading"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'rowidChanged'
        QtMocHelpers::SignalData<void()>(7, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'typeChanged'
        QtMocHelpers::SignalData<void()>(9, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'storageChanged'
        QtMocHelpers::SignalData<void()>(10, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'modifiedChanged'
        QtMocHelpers::SignalData<void()>(11, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'createdByChanged'
        QtMocHelpers::SignalData<void()>(12, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'updatedByChanged'
        QtMocHelpers::SignalData<void()>(13, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'createdAtChanged'
        QtMocHelpers::SignalData<void()>(14, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'updatedAtChanged'
        QtMocHelpers::SignalData<void()>(15, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reloaded'
        QtMocHelpers::SignalData<void()>(16, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'saved'
        QtMocHelpers::SignalData<void()>(17, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'recycled'
        QtMocHelpers::SignalData<void()>(18, 8, QMC::AccessPublic, QMetaType::Void),
        // Signal 'versionChanged'
        QtMocHelpers::SignalData<void()>(19, 8, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'rowid'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Final, 0),
        // property 'type'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Final, 1),
        // property 'modified'
        QtMocHelpers::PropertyData<bool>(22, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 3),
        // property 'createdBy'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 4),
        // property 'updatedBy'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 5),
        // property 'createdAt'
        QtMocHelpers::PropertyData<QDateTime>(25, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 6),
        // property 'updatedAt'
        QtMocHelpers::PropertyData<QDateTime>(26, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 7),
        // property 'version'
        QtMocHelpers::PropertyData<int>(27, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 11),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Type'
        QtMocHelpers::EnumData<Type>(28, 28, QMC::EnumFlags{}).add({
            {   29, Type::Type_Unknown },
            {   30, Type::Type_Storable },
            {   31, Type::Type_Node },
            {   32, Type::Type_Field },
            {   33, Type::Type_Element },
            {   34, Type::Type_Value },
            {   35, Type::Type_Project },
            {   36, Type::Type_NodeType },
            {   37, Type::Type_FieldType },
            {   38, Type::Type_ElementType },
            {   39, Type::Type_ValueType },
            {   40, Type::Type_ProjectType },
        }),
        // enum 'Flag'
        QtMocHelpers::EnumData<Flag>(41, 41, QMC::EnumFlags{}).add({
            {   42, Flag::NoFlag },
            {   43, Flag::Flag_Modified },
            {   44, Flag::Flag_Saving },
            {   45, Flag::Flag_Loading },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Storable, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Storable::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8StorableE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8StorableE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8StorableE_t>.metaTypes,
    nullptr
} };

void Storable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Storable *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->rowidChanged(QPrivateSignal()); break;
        case 1: _t->typeChanged(QPrivateSignal()); break;
        case 2: _t->storageChanged(QPrivateSignal()); break;
        case 3: _t->modifiedChanged(QPrivateSignal()); break;
        case 4: _t->createdByChanged(QPrivateSignal()); break;
        case 5: _t->updatedByChanged(QPrivateSignal()); break;
        case 6: _t->createdAtChanged(QPrivateSignal()); break;
        case 7: _t->updatedAtChanged(QPrivateSignal()); break;
        case 8: _t->reloaded(QPrivateSignal()); break;
        case 9: _t->saved(QPrivateSignal()); break;
        case 10: _t->recycled(QPrivateSignal()); break;
        case 11: _t->versionChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::rowidChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::typeChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::storageChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::modifiedChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::createdByChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::updatedByChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::createdAtChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::updatedAtChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::reloaded, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::saved, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::recycled, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storable::*)(QPrivateSignal)>(_a, &Storable::versionChanged, 11))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->rowid(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->type(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isModified(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->createdBy(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->updatedBy(); break;
        case 5: *reinterpret_cast<QDateTime*>(_v) = _t->createdAt(); break;
        case 6: *reinterpret_cast<QDateTime*>(_v) = _t->updatedAt(); break;
        case 7: *reinterpret_cast<int*>(_v) = _t->version(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setModified(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setCreatedBy(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setUpdatedBy(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setCreatedAt(*reinterpret_cast<QDateTime*>(_v)); break;
        case 6: _t->setUpdatedAt(*reinterpret_cast<QDateTime*>(_v)); break;
        case 7: _t->setVersion(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Storable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Storable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8StorableE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ErrorHandler"))
        return static_cast< ErrorHandler*>(this);
    if (!strcmp(_clname, "Jsonable"))
        return static_cast< Jsonable*>(this);
    return QObject::qt_metacast(_clname);
}

int Storable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Storable::rowidChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Storable::typeChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Storable::storageChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Storable::modifiedChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Storable::createdByChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Storable::updatedByChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Storable::createdAtChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void Storable::updatedAtChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void Storable::reloaded(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void Storable::saved(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void Storable::recycled(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void Storable::versionChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}
QT_WARNING_POP
