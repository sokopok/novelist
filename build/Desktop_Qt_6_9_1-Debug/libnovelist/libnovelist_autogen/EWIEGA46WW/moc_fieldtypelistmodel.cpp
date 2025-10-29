/****************************************************************************
** Meta object code from reading C++ file 'fieldtypelistmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/fieldtypelistmodel.h"
#include "elementtype.h"
#include "fieldtype.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fieldtypelistmodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18FieldTypeListModelE_t {};
} // unnamed namespace

template <> constexpr inline auto FieldTypeListModel::qt_create_metaobjectdata<qt_meta_tag_ZN18FieldTypeListModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FieldTypeListModel",
        "QML.Element",
        "auto",
        "fieldTypesChanged",
        "",
        "elementTypeChanged",
        "rowCount",
        "QModelIndex",
        "parent",
        "data",
        "QVariant",
        "index",
        "role",
        "fieldType",
        "FieldType*",
        "fieldTypes",
        "QList<FieldType*>",
        "elementType",
        "ElementType*",
        "Role",
        "FieldTypeRole",
        "NameRole",
        "LabelRole",
        "InfoRole",
        "IconRole",
        "MinOccursRole",
        "MaxOccursRole",
        "AllowesTypesRole",
        "ValueTypesRole",
        "UserRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fieldTypesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'elementTypeChanged'
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
        // Method 'fieldType'
        QtMocHelpers::MethodData<FieldType *(int) const>(13, 4, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'fieldTypes'
        QtMocHelpers::PropertyData<QList<FieldType*>>(15, 0x80000000 | 16, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'elementType'
        QtMocHelpers::PropertyData<ElementType*>(17, 0x80000000 | 18, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 1),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Role'
        QtMocHelpers::EnumData<Role>(19, 19, QMC::EnumFlags{}).add({
            {   20, Role::FieldTypeRole },
            {   21, Role::NameRole },
            {   22, Role::LabelRole },
            {   23, Role::InfoRole },
            {   24, Role::IconRole },
            {   25, Role::MinOccursRole },
            {   26, Role::MaxOccursRole },
            {   27, Role::AllowesTypesRole },
            {   28, Role::ValueTypesRole },
            {   29, Role::UserRole },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FieldTypeListModel, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FieldTypeListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18FieldTypeListModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18FieldTypeListModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18FieldTypeListModelE_t>.metaTypes,
    nullptr
} };

void FieldTypeListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FieldTypeListModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fieldTypesChanged(QPrivateSignal()); break;
        case 1: _t->elementTypeChanged(QPrivateSignal()); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 6: { FieldType* _r = _t->fieldType((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< FieldType**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FieldTypeListModel::*)(QPrivateSignal)>(_a, &FieldTypeListModel::fieldTypesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldTypeListModel::*)(QPrivateSignal)>(_a, &FieldTypeListModel::elementTypeChanged, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<FieldType*>*>(_v) = _t->fieldTypes(); break;
        case 1: *reinterpret_cast<ElementType**>(_v) = _t->elementType(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFieldTypes(*reinterpret_cast<QList<FieldType*>*>(_v)); break;
        case 1: _t->setElementType(*reinterpret_cast<ElementType**>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *FieldTypeListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldTypeListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18FieldTypeListModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int FieldTypeListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void FieldTypeListModel::fieldTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void FieldTypeListModel::elementTypeChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
