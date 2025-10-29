/****************************************************************************
** Meta object code from reading C++ file 'fieldstorage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/fieldstorage.h"
#include "nodetype.h"
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
#error "The header file 'fieldstorage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12FieldStorageE_t {};
} // unnamed namespace

template <> constexpr inline auto FieldStorage::qt_create_metaobjectdata<qt_meta_tag_ZN12FieldStorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "FieldStorage",
        "QML.Element",
        "auto",
        "field",
        "Field*",
        "",
        "rowid",
        "createField",
        "FieldType*",
        "nodeType",
        "label",
        "info",
        "icon"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'field'
        QtMocHelpers::MethodData<Field *()>(3, 5, QMC::AccessPublic, 0x80000000 | 4),
        // Method 'field'
        QtMocHelpers::MethodData<Field *(int)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'createField'
        QtMocHelpers::MethodData<Field *(FieldType *, const QString &, const QString &, const QString &)>(7, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'createField'
        QtMocHelpers::MethodData<Field *(FieldType *, const QString &, const QString &)>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
        }}),
        // Method 'createField'
        QtMocHelpers::MethodData<Field *(FieldType *, const QString &)>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 }, { QMetaType::QString, 10 },
        }}),
        // Method 'createField'
        QtMocHelpers::MethodData<Field *(FieldType *)>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Method 'createField'
        QtMocHelpers::MethodData<Field *()>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<FieldStorage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject FieldStorage::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseStorage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12FieldStorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12FieldStorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12FieldStorageE_t>.metaTypes,
    nullptr
} };

void FieldStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FieldStorage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { Field* _r = _t->field();
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        case 1: { Field* _r = _t->field((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        case 2: { Field* _r = _t->createField((*reinterpret_cast< std::add_pointer_t<FieldType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        case 3: { Field* _r = _t->createField((*reinterpret_cast< std::add_pointer_t<FieldType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        case 4: { Field* _r = _t->createField((*reinterpret_cast< std::add_pointer_t<FieldType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        case 5: { Field* _r = _t->createField((*reinterpret_cast< std::add_pointer_t<FieldType*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        case 6: { Field* _r = _t->createField();
            if (_a[0]) *reinterpret_cast< Field**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< FieldType* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< FieldType* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< FieldType* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< FieldType* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *FieldStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FieldStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12FieldStorageE_t>.strings))
        return static_cast<void*>(this);
    return BaseStorage::qt_metacast(_clname);
}

int FieldStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseStorage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
