/****************************************************************************
** Meta object code from reading C++ file 'valuelistmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/valuelistmodel.h"
#include "nodetype.h"
#include "fieldtype.h"
#include "valuetype.h"
#include "element.h"
#include "value.h"
#include "valuelistmodel.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'valuelistmodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14ValueListModelE_t {};
} // unnamed namespace

template <> constexpr inline auto ValueListModel::qt_create_metaobjectdata<qt_meta_tag_ZN14ValueListModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ValueListModel",
        "QML.Element",
        "auto",
        "valuesChanged",
        "",
        "fieldChanged",
        "rowCount",
        "QModelIndex",
        "parent",
        "data",
        "QVariant",
        "index",
        "role",
        "value",
        "Value*",
        "values",
        "QList<Value*>",
        "field",
        "Field*",
        "Role",
        "ValueRole",
        "NameRole",
        "LabelRole",
        "InfoRole",
        "IconRole",
        "ValueTypeRole",
        "ValueValueRole",
        "UserRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'valuesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fieldChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'rowCount'
        QtMocHelpers::MethodData<int(const QModelIndex &) const>(6, 4, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Method 'rowCount'
        QtMocHelpers::MethodData<int() const>(6, 4, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Int),
        // Method 'data'
        QtMocHelpers::MethodData<QVariant(const QModelIndex &, int) const>(9, 4, QMC::AccessPublic, 0x80000000 | 10, {{
            { 0x80000000 | 7, 11 }, { QMetaType::Int, 12 },
        }}),
        // Method 'data'
        QtMocHelpers::MethodData<QVariant(const QModelIndex &) const>(9, 4, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 10, {{
            { 0x80000000 | 7, 11 },
        }}),
        // Method 'value'
        QtMocHelpers::MethodData<Value *(int) const>(13, 4, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'values'
        QtMocHelpers::PropertyData<QList<Value*>>(15, 0x80000000 | 16, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'field'
        QtMocHelpers::PropertyData<Field*>(17, 0x80000000 | 18, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 1),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Role'
        QtMocHelpers::EnumData<Role>(19, 19, QMC::EnumFlags{}).add({
            {   20, Role::ValueRole },
            {   21, Role::NameRole },
            {   22, Role::LabelRole },
            {   23, Role::InfoRole },
            {   24, Role::IconRole },
            {   25, Role::ValueTypeRole },
            {   26, Role::ValueValueRole },
            {   27, Role::UserRole },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<ValueListModel, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ValueListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ValueListModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ValueListModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ValueListModelE_t>.metaTypes,
    nullptr
} };

void ValueListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ValueListModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->valuesChanged(QPrivateSignal()); break;
        case 1: _t->fieldChanged(QPrivateSignal()); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 6: { Value* _r = _t->value((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Value**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ValueListModel::*)(QPrivateSignal)>(_a, &ValueListModel::valuesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ValueListModel::*)(QPrivateSignal)>(_a, &ValueListModel::fieldChanged, 1))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Field* >(); break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<Value*> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<Value*>*>(_v) = _t->values(); break;
        case 1: *reinterpret_cast<Field**>(_v) = _t->field(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setValues(*reinterpret_cast<QList<Value*>*>(_v)); break;
        case 1: _t->setField(*reinterpret_cast<Field**>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ValueListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ValueListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ValueListModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int ValueListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ValueListModel::valuesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ValueListModel::fieldChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
