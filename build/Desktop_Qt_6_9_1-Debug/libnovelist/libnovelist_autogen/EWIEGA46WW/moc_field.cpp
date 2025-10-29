/****************************************************************************
** Meta object code from reading C++ file 'field.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/field.h"
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
#error "The header file 'field.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5FieldE_t {};
} // unnamed namespace

template <> constexpr inline auto Field::qt_create_metaobjectdata<qt_meta_tag_ZN5FieldE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Field",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "",
        "elementsChanged",
        "valuesChanged",
        "valuesAdded",
        "first",
        "last",
        "valuesRemoved",
        "allowedTypesChanged",
        "minOccursChanged",
        "maxOccursChanged",
        "indexIn",
        "Element*",
        "element",
        "elements",
        "QList<Element*>",
        "values",
        "QList<Value*>",
        "allowedTypes",
        "QList<int>",
        "allowedTypeNames",
        "minOccurs",
        "maxOccurs",
        "valueListModel",
        "ValueListModel*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'elementsChanged'
        QtMocHelpers::SignalData<void()>(7, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valuesChanged'
        QtMocHelpers::SignalData<void()>(8, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'valuesAdded'
        QtMocHelpers::SignalData<void(int, int)>(9, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Signal 'valuesRemoved'
        QtMocHelpers::SignalData<void(int, int)>(12, 6, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Signal 'allowedTypesChanged'
        QtMocHelpers::SignalData<void()>(13, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'minOccursChanged'
        QtMocHelpers::SignalData<void()>(14, 6, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maxOccursChanged'
        QtMocHelpers::SignalData<void()>(15, 6, QMC::AccessPublic, QMetaType::Void),
        // Method 'indexIn'
        QtMocHelpers::MethodData<int(Element *) const>(16, 6, QMC::AccessPublic, QMetaType::Int, {{
            { 0x80000000 | 17, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'elements'
        QtMocHelpers::PropertyData<QList<Element*>>(19, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'values'
        QtMocHelpers::PropertyData<QList<Value*>>(21, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 1),
        // property 'allowedTypes'
        QtMocHelpers::PropertyData<QList<int>>(23, 0x80000000 | 24, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 4),
        // property 'allowedTypeNames'
        QtMocHelpers::PropertyData<QStringList>(25, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 4),
        // property 'minOccurs'
        QtMocHelpers::PropertyData<int>(26, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 5),
        // property 'maxOccurs'
        QtMocHelpers::PropertyData<int>(27, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 6),
        // property 'valueListModel'
        QtMocHelpers::PropertyData<ValueListModel*>(28, 0x80000000 | 29, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Field, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Field::staticMetaObject = { {
    QMetaObject::SuperData::link<Node::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5FieldE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5FieldE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5FieldE_t>.metaTypes,
    nullptr
} };

void Field::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Field *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->elementsChanged(QPrivateSignal()); break;
        case 1: _t->valuesChanged(QPrivateSignal()); break;
        case 2: _t->valuesAdded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])), QPrivateSignal()); break;
        case 3: _t->valuesRemoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])), QPrivateSignal()); break;
        case 4: _t->allowedTypesChanged(QPrivateSignal()); break;
        case 5: _t->minOccursChanged(QPrivateSignal()); break;
        case 6: _t->maxOccursChanged(QPrivateSignal()); break;
        case 7: { int _r = _t->indexIn((*reinterpret_cast< std::add_pointer_t<Element*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Field::*)(QPrivateSignal)>(_a, &Field::elementsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Field::*)(QPrivateSignal)>(_a, &Field::valuesChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Field::*)(int , int , QPrivateSignal)>(_a, &Field::valuesAdded, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Field::*)(int , int , QPrivateSignal)>(_a, &Field::valuesRemoved, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Field::*)(QPrivateSignal)>(_a, &Field::allowedTypesChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Field::*)(QPrivateSignal)>(_a, &Field::minOccursChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Field::*)(QPrivateSignal)>(_a, &Field::maxOccursChanged, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<Element*>*>(_v) = _t->elements(); break;
        case 1: *reinterpret_cast<QList<Value*>*>(_v) = _t->values(); break;
        case 2: *reinterpret_cast<QList<int>*>(_v) = _t->allowedTypes(); break;
        case 3: *reinterpret_cast<QStringList*>(_v) = _t->allowedTypeNames(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->minOccurs(); break;
        case 5: *reinterpret_cast<int*>(_v) = _t->maxOccurs(); break;
        case 6: *reinterpret_cast<ValueListModel**>(_v) = _t->valueListModel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setElements(*reinterpret_cast<QList<Element*>*>(_v)); break;
        case 1: _t->setValues(*reinterpret_cast<QList<Value*>*>(_v)); break;
        case 2: _t->setAllowedTypes(*reinterpret_cast<QList<int>*>(_v)); break;
        case 3: _t->setAllowedTypeNames(*reinterpret_cast<QStringList*>(_v)); break;
        case 4: _t->setMinOccurs(*reinterpret_cast<int*>(_v)); break;
        case 5: _t->setMaxOccurs(*reinterpret_cast<int*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Field::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Field::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5FieldE_t>.strings))
        return static_cast<void*>(this);
    return Node::qt_metacast(_clname);
}

int Field::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Node::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
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
void Field::elementsChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Field::valuesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Field::valuesAdded(int _t1, int _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}

// SIGNAL 3
void Field::valuesRemoved(int _t1, int _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void Field::allowedTypesChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Field::minOccursChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Field::maxOccursChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
