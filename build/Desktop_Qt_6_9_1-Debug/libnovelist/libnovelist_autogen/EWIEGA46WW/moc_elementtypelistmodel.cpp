/****************************************************************************
** Meta object code from reading C++ file 'elementtypelistmodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/elementtypelistmodel.h"
#include "elementtype.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementtypelistmodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20ElementTypeListModelE_t {};
} // unnamed namespace

template <> constexpr inline auto ElementTypeListModel::qt_create_metaobjectdata<qt_meta_tag_ZN20ElementTypeListModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ElementTypeListModel",
        "QML.Element",
        "auto",
        "elementTypesChanged",
        "",
        "rowCount",
        "QModelIndex",
        "parent",
        "data",
        "QVariant",
        "index",
        "role",
        "elementType",
        "ElementType*",
        "elementTypes",
        "QList<ElementType*>",
        "Role",
        "ElementTypeRole",
        "NameRole",
        "LabelRole",
        "InfoRole",
        "IconRole",
        "MinOccursRole",
        "MaxOccursRole",
        "AllowesTypesRole",
        "FieldTypesRole",
        "UserRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'elementTypesChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Method 'rowCount'
        QtMocHelpers::MethodData<int(const QModelIndex &) const>(5, 4, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Method 'rowCount'
        QtMocHelpers::MethodData<int() const>(5, 4, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Int),
        // Method 'data'
        QtMocHelpers::MethodData<QVariant(const QModelIndex &, int) const>(8, 4, QMC::AccessPublic, 0x80000000 | 9, {{
            { 0x80000000 | 6, 10 }, { QMetaType::Int, 11 },
        }}),
        // Method 'data'
        QtMocHelpers::MethodData<QVariant(const QModelIndex &) const>(8, 4, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 9, {{
            { 0x80000000 | 6, 10 },
        }}),
        // Method 'elementType'
        QtMocHelpers::MethodData<ElementType *(int) const>(12, 4, QMC::AccessPublic, 0x80000000 | 13, {{
            { QMetaType::Int, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'elementTypes'
        QtMocHelpers::PropertyData<QList<ElementType*>>(14, 0x80000000 | 15, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Role'
        QtMocHelpers::EnumData<Role>(16, 16, QMC::EnumFlags{}).add({
            {   17, Role::ElementTypeRole },
            {   18, Role::NameRole },
            {   19, Role::LabelRole },
            {   20, Role::InfoRole },
            {   21, Role::IconRole },
            {   22, Role::MinOccursRole },
            {   23, Role::MaxOccursRole },
            {   24, Role::AllowesTypesRole },
            {   25, Role::FieldTypesRole },
            {   26, Role::UserRole },
        }),
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<ElementTypeListModel, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ElementTypeListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ElementTypeListModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ElementTypeListModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20ElementTypeListModelE_t>.metaTypes,
    nullptr
} };

void ElementTypeListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ElementTypeListModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->elementTypesChanged(QPrivateSignal()); break;
        case 1: { int _r = _t->rowCount((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { ElementType* _r = _t->elementType((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< ElementType**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ElementTypeListModel::*)(QPrivateSignal)>(_a, &ElementTypeListModel::elementTypesChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<ElementType*>*>(_v) = _t->elementTypes(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setElementTypes(*reinterpret_cast<QList<ElementType*>*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ElementTypeListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementTypeListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ElementTypeListModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int ElementTypeListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ElementTypeListModel::elementTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
