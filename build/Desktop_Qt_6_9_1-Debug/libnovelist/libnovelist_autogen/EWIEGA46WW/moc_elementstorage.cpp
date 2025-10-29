/****************************************************************************
** Meta object code from reading C++ file 'elementstorage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/elementstorage.h"
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
#error "The header file 'elementstorage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14ElementStorageE_t {};
} // unnamed namespace

template <> constexpr inline auto ElementStorage::qt_create_metaobjectdata<qt_meta_tag_ZN14ElementStorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ElementStorage",
        "QML.Element",
        "auto",
        "element",
        "Element*",
        "",
        "rowid",
        "createElement",
        "ElementType*",
        "nodeType",
        "label",
        "info",
        "icon"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'element'
        QtMocHelpers::MethodData<Element *()>(3, 5, QMC::AccessPublic, 0x80000000 | 4),
        // Method 'element'
        QtMocHelpers::MethodData<Element *(int)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'createElement'
        QtMocHelpers::MethodData<Element *(ElementType *, const QString &, const QString &, const QString &)>(7, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 }, { QMetaType::QString, 12 },
        }}),
        // Method 'createElement'
        QtMocHelpers::MethodData<Element *(ElementType *, const QString &, const QString &)>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
        }}),
        // Method 'createElement'
        QtMocHelpers::MethodData<Element *(ElementType *, const QString &)>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 }, { QMetaType::QString, 10 },
        }}),
        // Method 'createElement'
        QtMocHelpers::MethodData<Element *(ElementType *)>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Method 'createElement'
        QtMocHelpers::MethodData<Element *()>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<ElementStorage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ElementStorage::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseStorage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ElementStorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ElementStorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ElementStorageE_t>.metaTypes,
    nullptr
} };

void ElementStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ElementStorage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { Element* _r = _t->element();
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
        case 1: { Element* _r = _t->element((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
        case 2: { Element* _r = _t->createElement((*reinterpret_cast< std::add_pointer_t<ElementType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])));
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
        case 3: { Element* _r = _t->createElement((*reinterpret_cast< std::add_pointer_t<ElementType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
        case 4: { Element* _r = _t->createElement((*reinterpret_cast< std::add_pointer_t<ElementType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
        case 5: { Element* _r = _t->createElement((*reinterpret_cast< std::add_pointer_t<ElementType*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
        case 6: { Element* _r = _t->createElement();
            if (_a[0]) *reinterpret_cast< Element**>(_a[0]) = std::move(_r); }  break;
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
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ElementType* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ElementType* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ElementType* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ElementType* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *ElementStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElementStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ElementStorageE_t>.strings))
        return static_cast<void*>(this);
    return BaseStorage::qt_metacast(_clname);
}

int ElementStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
