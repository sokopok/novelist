/****************************************************************************
** Meta object code from reading C++ file 'valuetypestorage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/valuetypestorage.h"
#include "nodetype.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'valuetypestorage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16ValueTypeStorageE_t {};
} // unnamed namespace

template <> constexpr inline auto ValueTypeStorage::qt_create_metaobjectdata<qt_meta_tag_ZN16ValueTypeStorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ValueTypeStorage",
        "QML.Element",
        "auto",
        "valueType",
        "ValueType*",
        "",
        "rowid",
        "name",
        "createValueType",
        "label",
        "info",
        "icon"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'valueType'
        QtMocHelpers::MethodData<ValueType *()>(3, 5, QMC::AccessPublic, 0x80000000 | 4),
        // Method 'valueType'
        QtMocHelpers::MethodData<ValueType *(int)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'valueType'
        QtMocHelpers::MethodData<ValueType *(const QString &)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'createValueType'
        QtMocHelpers::MethodData<ValueType *(const QString &, const QString &, const QString &, const QString &)>(8, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
        }}),
        // Method 'createValueType'
        QtMocHelpers::MethodData<ValueType *(const QString &, const QString &, const QString &)>(8, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Method 'createValueType'
        QtMocHelpers::MethodData<ValueType *(const QString &, const QString &)>(8, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 9 },
        }}),
        // Method 'createValueType'
        QtMocHelpers::MethodData<ValueType *(const QString &)>(8, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { QMetaType::QString, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<ValueTypeStorage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ValueTypeStorage::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseTypeStorage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ValueTypeStorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ValueTypeStorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16ValueTypeStorageE_t>.metaTypes,
    nullptr
} };

void ValueTypeStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ValueTypeStorage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { ValueType* _r = _t->valueType();
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        case 1: { ValueType* _r = _t->valueType((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        case 2: { ValueType* _r = _t->valueType((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        case 3: { ValueType* _r = _t->createValueType((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        case 4: { ValueType* _r = _t->createValueType((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        case 5: { ValueType* _r = _t->createValueType((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        case 6: { ValueType* _r = _t->createValueType((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< ValueType**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *ValueTypeStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ValueTypeStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ValueTypeStorageE_t>.strings))
        return static_cast<void*>(this);
    return BaseTypeStorage::qt_metacast(_clname);
}

int ValueTypeStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTypeStorage::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
