/****************************************************************************
** Meta object code from reading C++ file 'value.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/value.h"
#include "nodetype.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'value.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5ValueE_t {};
} // unnamed namespace

template <> constexpr inline auto Value::qt_create_metaobjectdata<qt_meta_tag_ZN5ValueE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Value",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "",
        "fieldsChanged",
        "valueChanged",
        "valueTypeChanged",
        "indexIn",
        "Field*",
        "field",
        "fields",
        "QList<Field*>",
        "value",
        "QVariant",
        "valueType",
        "Type",
        "Type_Unknown",
        "Type_String",
        "Type_Int",
        "Type_Float",
        "Type_Double",
        "Type_Bool",
        "Type_Date",
        "Type_Time",
        "Type_DateTime",
        "Type_Node",
        "Type_NodeList"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fieldsChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valueChanged'
        QtMocHelpers::SignalData<void()>(8, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valueTypeChanged'
        QtMocHelpers::SignalData<void()>(9, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'indexIn'
        QtMocHelpers::MethodData<int(Field *) const>(10, 6, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 11, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'fields'
        QtMocHelpers::PropertyData<QList<Field*>>(13, 0x80000000 | 14, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'value'
        QtMocHelpers::PropertyData<QVariant>(15, 0x80000000 | 16, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 1),
        // property 'valueType'
        QtMocHelpers::PropertyData<int>(17, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 2),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Type'
        QtMocHelpers::EnumData<Type>(18, 18, QMC::EnumFlags{}).add({
            {   19, Type::Type_Unknown },
            {   20, Type::Type_String },
            {   21, Type::Type_Int },
            {   22, Type::Type_Float },
            {   23, Type::Type_Double },
            {   24, Type::Type_Bool },
            {   25, Type::Type_Date },
            {   26, Type::Type_Time },
            {   27, Type::Type_DateTime },
            {   28, Type::Type_Node },
            {   29, Type::Type_NodeList },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Value, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Value::staticMetaObject = { {
    QMetaObject::SuperData::link<Node::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5ValueE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5ValueE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5ValueE_t>.metaTypes,
    nullptr
} };

void Value::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Value *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fieldsChanged(QPrivateSignal()); break;
        case 1: _t->valueChanged(QPrivateSignal()); break;
        case 2: _t->valueTypeChanged(QPrivateSignal()); break;
        case 3: { int _r = _t->indexIn((*reinterpret_cast< std::add_pointer_t<Field*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Value::*)(QPrivateSignal)>(_a, &Value::fieldsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Value::*)(QPrivateSignal)>(_a, &Value::valueChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Value::*)(QPrivateSignal)>(_a, &Value::valueTypeChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<Field*>*>(_v) = _t->fields(); break;
        case 1: *reinterpret_cast<QVariant*>(_v) = _t->value(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->valueType(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFields(*reinterpret_cast<QList<Field*>*>(_v)); break;
        case 1: _t->setValue(*reinterpret_cast<QVariant*>(_v)); break;
        case 2: _t->setValueType(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Value::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Value::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5ValueE_t>.strings))
        return static_cast<void*>(this);
    return Node::qt_metacast(_clname);
}

int Value::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Node::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Value::fieldsChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Value::valueChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Value::valueTypeChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
