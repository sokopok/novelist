/****************************************************************************
** Meta object code from reading C++ file 'projectstorage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/projectstorage.h"
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
#error "The header file 'projectstorage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14ProjectStorageE_t {};
} // unnamed namespace

template <> constexpr inline auto ProjectStorage::qt_create_metaobjectdata<qt_meta_tag_ZN14ProjectStorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ProjectStorage",
        "QML.Element",
        "auto",
        "project",
        "Project*",
        "",
        "rowid",
        "createProject",
        "type",
        "ProjectType*",
        "nodeType"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'project'
        QtMocHelpers::MethodData<Project *()>(3, 5, QMC::AccessPublic, 0x80000000 | 4),
        // Method 'project'
        QtMocHelpers::MethodData<Project *(int)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'createProject'
        QtMocHelpers::MethodData<Project *(const QString &)>(7, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QString, 8 },
        }}),
        // Method 'createProject'
        QtMocHelpers::MethodData<Project *(ProjectType *)>(7, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Method 'createProject'
        QtMocHelpers::MethodData<Project *()>(7, 5, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 4),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<ProjectStorage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ProjectStorage::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseStorage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ProjectStorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ProjectStorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ProjectStorageE_t>.metaTypes,
    nullptr
} };

void ProjectStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ProjectStorage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { Project* _r = _t->project();
            if (_a[0]) *reinterpret_cast< Project**>(_a[0]) = std::move(_r); }  break;
        case 1: { Project* _r = _t->project((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Project**>(_a[0]) = std::move(_r); }  break;
        case 2: { Project* _r = _t->createProject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Project**>(_a[0]) = std::move(_r); }  break;
        case 3: { Project* _r = _t->createProject((*reinterpret_cast< std::add_pointer_t<ProjectType*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Project**>(_a[0]) = std::move(_r); }  break;
        case 4: { Project* _r = _t->createProject();
            if (_a[0]) *reinterpret_cast< Project**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ProjectType* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *ProjectStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ProjectStorageE_t>.strings))
        return static_cast<void*>(this);
    return BaseStorage::qt_metacast(_clname);
}

int ProjectStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseStorage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
