/****************************************************************************
** Meta object code from reading C++ file 'storage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/storage.h"
#include "nodetype.h"
#include "elementtype.h"
#include "fieldtype.h"
#include "element.h"
#include "field.h"
#include "field.h"
#include "fieldtype.h"
#include "valuetype.h"
#include "element.h"
#include "value.h"
#include "valuelistmodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'storage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7StorageE_t {};
} // unnamed namespace

template <> constexpr inline auto Storage::qt_create_metaobjectdata<qt_meta_tag_ZN7StorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Storage",
        "QML.Element",
        "auto",
        "databaseChanged",
        "",
        "databaseNameChanged",
        "databaseConnectionNameChanged",
        "elementStorage",
        "ElementStorage*",
        "elementTypeStorage",
        "ElementTypeStorage*",
        "fieldStorage",
        "FieldStorage*",
        "fieldTypeStorage",
        "FieldTypeStorage*",
        "valueStorage",
        "ValueStorage*",
        "valueTypeStorage",
        "ValueTypeStorage*",
        "projectStorage",
        "ProjectStorage*",
        "projectTypeStorage",
        "ProjectTypeStorage*",
        "databaseName",
        "databaseConnectionName"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'databaseChanged'
        QtMocHelpers::SignalData<void()>(3, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'databaseNameChanged'
        QtMocHelpers::SignalData<void()>(5, 4, QMC::AccessPublic, QMetaType::Void),
        // Signal 'databaseConnectionNameChanged'
        QtMocHelpers::SignalData<void()>(6, 4, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'elementStorage'
        QtMocHelpers::PropertyData<ElementStorage*>(7, 0x80000000 | 8, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'elementTypeStorage'
        QtMocHelpers::PropertyData<ElementTypeStorage*>(9, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'fieldStorage'
        QtMocHelpers::PropertyData<FieldStorage*>(11, 0x80000000 | 12, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'fieldTypeStorage'
        QtMocHelpers::PropertyData<FieldTypeStorage*>(13, 0x80000000 | 14, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'valueStorage'
        QtMocHelpers::PropertyData<ValueStorage*>(15, 0x80000000 | 16, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'valueTypeStorage'
        QtMocHelpers::PropertyData<ValueTypeStorage*>(17, 0x80000000 | 18, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'projectStorage'
        QtMocHelpers::PropertyData<ProjectStorage*>(19, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'projectTypeStorage'
        QtMocHelpers::PropertyData<ProjectTypeStorage*>(21, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
        // property 'databaseName'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'databaseConnectionName'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<Storage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Storage::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7StorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7StorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7StorageE_t>.metaTypes,
    nullptr
} };

void Storage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Storage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->databaseChanged(QPrivateSignal()); break;
        case 1: _t->databaseNameChanged(QPrivateSignal()); break;
        case 2: _t->databaseConnectionNameChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Storage::*)(QPrivateSignal)>(_a, &Storage::databaseChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storage::*)(QPrivateSignal)>(_a, &Storage::databaseNameChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Storage::*)(QPrivateSignal)>(_a, &Storage::databaseConnectionNameChanged, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ElementStorage* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ElementTypeStorage* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FieldStorage* >(); break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FieldTypeStorage* >(); break;
        case 6:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ProjectStorage* >(); break;
        case 7:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ProjectTypeStorage* >(); break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ValueStorage* >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ValueTypeStorage* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ElementStorage**>(_v) = _t->elementStorage(); break;
        case 1: *reinterpret_cast<ElementTypeStorage**>(_v) = _t->elementTypeStorage(); break;
        case 2: *reinterpret_cast<FieldStorage**>(_v) = _t->fieldStorage(); break;
        case 3: *reinterpret_cast<FieldTypeStorage**>(_v) = _t->fieldTypeStorage(); break;
        case 4: *reinterpret_cast<ValueStorage**>(_v) = _t->valueStorage(); break;
        case 5: *reinterpret_cast<ValueTypeStorage**>(_v) = _t->valueTypeStorage(); break;
        case 6: *reinterpret_cast<ProjectStorage**>(_v) = _t->projectStorage(); break;
        case 7: *reinterpret_cast<ProjectTypeStorage**>(_v) = _t->projectTypeStorage(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->databaseName(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->databaseConnectionName(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 8: _t->setDatabaseName(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setDatabaseConnectionName(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Storage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Storage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7StorageE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Storage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Storage::databaseChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Storage::databaseNameChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Storage::databaseConnectionNameChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
