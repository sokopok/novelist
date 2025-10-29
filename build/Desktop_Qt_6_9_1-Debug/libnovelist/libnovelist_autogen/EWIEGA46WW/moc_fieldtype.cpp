/****************************************************************************
** Meta object code from reading C++ file 'fieldtype.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/fieldtype.h"
#include "nodetype.h"
#include "fieldtype.h"
#include "valuetype.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fieldtype.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9FieldTypeE_t {};
} // unnamed namespace

template <> constexpr inline auto FieldType::qt_create_metaobjectdata<qt_meta_tag_ZN9FieldTypeE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FieldType",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "",
        "elementTypesChanged",
        "valueTypesChanged",
        "valueTypesAdded",
        "first",
        "last",
        "valueTypesRemoved",
        "allowedTypesChanged",
        "minOccursChanged",
        "maxOccursChanged",
        "elementTypes",
        "QList<ElementType*>",
        "valueTypes",
        "QList<ValueType*>",
        "allowedTypes",
        "QList<int>",
        "allowedTypeNames",
        "minOccurs",
        "maxOccurs",
        "valueTypeListModel",
        "ValueTypeListModel*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'elementTypesChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valueTypesChanged'
        QtMocHelpers::SignalData<void()>(8, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valueTypesAdded'
        QtMocHelpers::SignalData<void(int, int)>(9, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Signal 'valueTypesRemoved'
        QtMocHelpers::SignalData<void(int, int)>(12, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Signal 'allowedTypesChanged'
        QtMocHelpers::SignalData<void()>(13, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'minOccursChanged'
        QtMocHelpers::SignalData<void()>(14, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxOccursChanged'
        QtMocHelpers::SignalData<void()>(15, 6, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'elementTypes'
        QtMocHelpers::PropertyData<QList<ElementType*>>(16, 0x80000000 | 17, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 0),
        // property 'valueTypes'
        QtMocHelpers::PropertyData<QList<ValueType*>>(18, 0x80000000 | 19, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 1),
        // property 'allowedTypes'
        QtMocHelpers::PropertyData<QList<int>>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 4),
        // property 'allowedTypeNames'
        QtMocHelpers::PropertyData<QStringList>(22, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'minOccurs'
        QtMocHelpers::PropertyData<int>(23, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
        // property 'maxOccurs'
        QtMocHelpers::PropertyData<int>(24, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 6),
        // property 'valueTypeListModel'
        QtMocHelpers::PropertyData<ValueTypeListModel*>(25, 0x80000000 | 26, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<FieldType, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FieldType::staticMetaObject = { {
    QMetaObject::SuperData::link<NodeType::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9FieldTypeE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9FieldTypeE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9FieldTypeE_t>.metaTypes,
    nullptr
} };

void FieldType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FieldType *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->elementTypesChanged(QPrivateSignal()); break;
        case 1: _t->valueTypesChanged(QPrivateSignal()); break;
        case 2: _t->valueTypesAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])), QPrivateSignal()); break;
        case 3: _t->valueTypesRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])), QPrivateSignal()); break;
        case 4: _t->allowedTypesChanged(QPrivateSignal()); break;
        case 5: _t->minOccursChanged(QPrivateSignal()); break;
        case 6: _t->maxOccursChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(QPrivateSignal)>(_a, &FieldType::elementTypesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(QPrivateSignal)>(_a, &FieldType::valueTypesChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(int , int , QPrivateSignal)>(_a, &FieldType::valueTypesAdded, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(int , int , QPrivateSignal)>(_a, &FieldType::valueTypesRemoved, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(QPrivateSignal)>(_a, &FieldType::allowedTypesChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(QPrivateSignal)>(_a, &FieldType::minOccursChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (FieldType::*)(QPrivateSignal)>(_a, &FieldType::maxOccursChanged, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        case 6:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ValueTypeListModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<ElementType*>*>(_v) = _t->elementTypes(); break;
        case 1: *reinterpret_cast<QList<ValueType*>*>(_v) = _t->valueTypes(); break;
        case 2: *reinterpret_cast<QList<int>*>(_v) = _t->allowedTypes(); break;
        case 3: *reinterpret_cast<QStringList*>(_v) = _t->allowedTypeNames(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->minOccurs(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->maxOccurs(); break;
        case 6: *reinterpret_cast<ValueTypeListModel**>(_v) = _t->valueTypeListModel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setElementTypes(*reinterpret_cast<QList<ElementType*>*>(_v)); break;
        case 1: _t->setValueTypes(*reinterpret_cast<QList<ValueType*>*>(_v)); break;
        case 2: _t->setAllowedTypes(*reinterpret_cast<QList<int>*>(_v)); break;
        case 3: _t->setAllowedTypeNames(*reinterpret_cast<QStringList*>(_v)); break;
        case 4: _t->setMinOccurs(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setMaxOccurs(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *FieldType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldType::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9FieldTypeE_t>.strings))
        return static_cast<void*>(this);
    return NodeType::qt_metacast(_clname);
}

int FieldType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NodeType::qt_metacall(_c, _id, _a);
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
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FieldType::elementTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void FieldType::valueTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void FieldType::valueTypesAdded(int _t1, int _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}

// SIGNAL 3
void FieldType::valueTypesRemoved(int _t1, int _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void FieldType::allowedTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void FieldType::minOccursChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void FieldType::maxOccursChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
