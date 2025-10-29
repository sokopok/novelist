/****************************************************************************
** Meta object code from reading C++ file 'elementtype.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/elementtype.h"
#include "elementtype.h"
#include "fieldtype.h"
#include "nodetype.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elementtype.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11ElementTypeE_t {};
} // unnamed namespace

template <> constexpr inline auto ElementType::qt_create_metaobjectdata<qt_meta_tag_ZN11ElementTypeE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ElementType",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "",
        "fieldTypesChanged",
        "fieldTypesAdded",
        "first",
        "last",
        "fieldTypesRemoved",
        "fieldTypes",
        "QList<FieldType*>",
        "fieldTypeListModel",
        "FieldTypeListModel*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fieldTypesChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'fieldTypesAdded'
        QtMocHelpers::SignalData<void(int, int)>(8, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 }, { QMetaType::Int, 10 },
        }}),
        // Signal 'fieldTypesRemoved'
        QtMocHelpers::SignalData<void(int, int)>(11, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 }, { QMetaType::Int, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'fieldTypes'
        QtMocHelpers::PropertyData<QList<FieldType*>>(12, 0x80000000 | 13, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'fieldTypeListModel'
        QtMocHelpers::PropertyData<FieldTypeListModel*>(14, 0x80000000 | 15, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<ElementType, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ElementType::staticMetaObject = { {
    QMetaObject::SuperData::link<NodeType::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ElementTypeE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ElementTypeE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11ElementTypeE_t>.metaTypes,
    nullptr
} };

void ElementType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ElementType *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fieldTypesChanged(QPrivateSignal()); break;
        case 1: _t->fieldTypesAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])), QPrivateSignal()); break;
        case 2: _t->fieldTypesRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])), QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ElementType::*)(QPrivateSignal)>(_a, &ElementType::fieldTypesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ElementType::*)(int , int , QPrivateSignal)>(_a, &ElementType::fieldTypesAdded, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ElementType::*)(int , int , QPrivateSignal)>(_a, &ElementType::fieldTypesRemoved, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FieldTypeListModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<FieldType*>*>(_v) = _t->fieldTypes(); break;
        case 1: *reinterpret_cast<FieldTypeListModel**>(_v) = _t->fieldTypeListModel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFieldTypes(*reinterpret_cast<QList<FieldType*>*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ElementType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementType::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ElementTypeE_t>.strings))
        return static_cast<void*>(this);
    return NodeType::qt_metacast(_clname);
}

int ElementType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NodeType::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
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
void ElementType::fieldTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ElementType::fieldTypesAdded(int _t1, int _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void ElementType::fieldTypesRemoved(int _t1, int _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
