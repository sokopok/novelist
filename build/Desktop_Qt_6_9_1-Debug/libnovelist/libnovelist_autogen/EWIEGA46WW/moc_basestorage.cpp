/****************************************************************************
** Meta object code from reading C++ file 'basestorage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/basestorage.h"
#include "nodetype.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basestorage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11BaseStorageE_t {};
} // unnamed namespace

template <> constexpr inline auto BaseStorage::qt_create_metaobjectdata<qt_meta_tag_ZN11BaseStorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BaseStorage",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "BaseStorage is a base class",
        "nodeCreated",
        "",
        "Node*",
        "node",
        "nodeRecycled",
        "nodeRevived",
        "nodeDestroyed",
        "nodeInserted",
        "nodeUpdated",
        "nodeSaved",
        "nodeReloaded",
        "nodeLoaded",
        "nodeRemoved",
        "databaseChanged",
        "database",
        "QSqlDatabase"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'nodeCreated'
        QtMocHelpers::SignalData<void(Node *)>(7, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeRecycled'
        QtMocHelpers::SignalData<void(Node *)>(11, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeRevived'
        QtMocHelpers::SignalData<void(Node *)>(12, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeDestroyed'
        QtMocHelpers::SignalData<void(Node *)>(13, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeInserted'
        QtMocHelpers::SignalData<void(Node *)>(14, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeUpdated'
        QtMocHelpers::SignalData<void(Node *)>(15, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeSaved'
        QtMocHelpers::SignalData<void(Node *)>(16, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeReloaded'
        QtMocHelpers::SignalData<void(Node *)>(17, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeLoaded'
        QtMocHelpers::SignalData<void(Node *)>(18, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'nodeRemoved'
        QtMocHelpers::SignalData<void(Node *)>(19, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'databaseChanged'
        QtMocHelpers::SignalData<void()>(20, 8, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'database'
        QtMocHelpers::PropertyData<QSqlDatabase>(21, 0x80000000 | 22, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 10),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<BaseStorage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject BaseStorage::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11BaseStorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11BaseStorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11BaseStorageE_t>.metaTypes,
    nullptr
} };

void BaseStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BaseStorage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->nodeCreated((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 1: _t->nodeRecycled((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 2: _t->nodeRevived((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 3: _t->nodeDestroyed((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 4: _t->nodeInserted((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 5: _t->nodeUpdated((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 6: _t->nodeSaved((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 7: _t->nodeReloaded((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 8: _t->nodeLoaded((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 9: _t->nodeRemoved((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 10: _t->databaseChanged(QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Node* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeCreated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeRecycled, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeRevived, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeDestroyed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeInserted, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeUpdated, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeSaved, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeReloaded, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeLoaded, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(Node * , QPrivateSignal)>(_a, &BaseStorage::nodeRemoved, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (BaseStorage::*)(QPrivateSignal)>(_a, &BaseStorage::databaseChanged, 10))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QSqlDatabase*>(_v) = _t->database(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDatabase(*reinterpret_cast<QSqlDatabase*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *BaseStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11BaseStorageE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ErrorHandler"))
        return static_cast< ErrorHandler*>(this);
    return QObject::qt_metacast(_clname);
}

int BaseStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
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
void BaseStorage::nodeCreated(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void BaseStorage::nodeRecycled(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void BaseStorage::nodeRevived(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}

// SIGNAL 3
void BaseStorage::nodeDestroyed(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void BaseStorage::nodeInserted(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void BaseStorage::nodeUpdated(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void BaseStorage::nodeSaved(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}

// SIGNAL 7
void BaseStorage::nodeReloaded(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void BaseStorage::nodeLoaded(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1, _t2);
}

// SIGNAL 9
void BaseStorage::nodeRemoved(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1, _t2);
}

// SIGNAL 10
void BaseStorage::databaseChanged(QPrivateSignal _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}
namespace {
struct qt_meta_tag_ZN15BaseTypeStorageE_t {};
} // unnamed namespace

template <> constexpr inline auto BaseTypeStorage::qt_create_metaobjectdata<qt_meta_tag_ZN15BaseTypeStorageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "BaseTypeStorage",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "BaseTypeStorage is a base class",
        "nodeType",
        "NodeType*",
        "",
        "name"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'nodeType'
        QtMocHelpers::MethodData<NodeType *(const QString &)>(7, 9, QMC::AccessPublic, 0x80000000 | 8, {{
            { QMetaType::QString, 10 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<BaseTypeStorage, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject BaseTypeStorage::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseStorage::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15BaseTypeStorageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15BaseTypeStorageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15BaseTypeStorageE_t>.metaTypes,
    nullptr
} };

void BaseTypeStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<BaseTypeStorage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { NodeType* _r = _t->nodeType((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< NodeType**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *BaseTypeStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseTypeStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15BaseTypeStorageE_t>.strings))
        return static_cast<void*>(this);
    return BaseStorage::qt_metacast(_clname);
}

int BaseTypeStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseStorage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
