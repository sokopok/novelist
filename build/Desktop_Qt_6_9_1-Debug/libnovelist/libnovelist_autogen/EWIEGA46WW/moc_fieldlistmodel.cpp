/****************************************************************************
** Meta object code from reading C++ file 'fieldlistmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/fieldlistmodel.h"
#include "element.h"
#include "field.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fieldlistmodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14FieldListModelE_t {};
} // unnamed namespace

template <> constexpr inline auto FieldListModel::qt_create_metaobjectdata<qt_meta_tag_ZN14FieldListModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FieldListModel",
        "QML.Element",
        "auto",
        "fieldsChanged",
        "",
        "elementChanged",
        "rowCount",
        "QModelIndex",
        "parent",
        "data",
        "QVariant",
        "index",
        "role",
        "field",
        "Field*",
        "fields",
        "QList<Field*>",
        "element",
        "Element*",
        "Role",
        "FieldRole",
        "NameRole",
        "LabelRole",
        "InfoRole",
        "IconRole",
        "MinOccursRole",
        "MaxOccursRole",
        "AllowesTypesRole",
        "ValuesRole",
        "UserRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fieldsChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'elementChanged'
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
        // Method 'field'
        QtMocHelpers::MethodData<Field *(int) const>(13, 4, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'fields'
        QtMocHelpers::PropertyData<QList<Field*>>(15, 0x80000000 | 16, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'element'
        QtMocHelpers::PropertyData<Element*>(17, 0x80000000 | 18, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 1),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Role'
        QtMocHelpers::EnumData<Role>(19, 19, QMC::EnumFlags{}).add({
            {   20, Role::FieldRole },
            {   21, Role::NameRole },
            {   22, Role::LabelRole },
            {   23, Role::InfoRole },
            {   24, Role::IconRole },
            {   25, Role::MinOccursRole },
            {   26, Role::MaxOccursRole },
            {   27, Role::AllowesTypesRole },
            {   28, Role::ValuesRole },
            {   29, Role::UserRole },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FieldListModel, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FieldListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14FieldListModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14FieldListModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14FieldListModelE_t>.metaTypes,
    nullptr
} };

void FieldListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FieldListModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fieldsChanged(QPrivateSignal()); break;
        case 1: _t->elementChanged(QPrivateSignal()); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 6: { Field* _r = _t->field((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FieldListModel::*)(QPrivateSignal)>(_a, &FieldListModel::fieldsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldListModel::*)(QPrivateSignal)>(_a, &FieldListModel::elementChanged, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<Field*>*>(_v) = _t->fields(); break;
        case 1: *reinterpret_cast<Element**>(_v) = _t->element(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFields(*reinterpret_cast<QList<Field*>*>(_v)); break;
        case 1: _t->setElement(*reinterpret_cast<Element**>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *FieldListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14FieldListModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int FieldListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void FieldListModel::fieldsChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void FieldListModel::elementChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
