/****************************************************************************
** Meta object code from reading C++ file 'node.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libnovelist/node.h"
#include "nodetype.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'node.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN4NodeE_t {};
} // unnamed namespace

template <> constexpr inline auto Node::qt_create_metaobjectdata<qt_meta_tag_ZN4NodeE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Node",
        "QML.Element",
        "auto",
        "QML.Creatable",
        "false",
        "QML.UncreatableReason",
        "Node is a base class",
        "nameChanged",
        "",
        "newName",
        "oldName",
        "labelChanged",
        "newLabel",
        "oldLabel",
        "infoChanged",
        "newInfo",
        "oldInfo",
        "iconChanged",
        "newIcon",
        "oldIcon",
        "nodeTypeChanged",
        "NodeType*",
        "newNodeType",
        "oldNodeType",
        "childNodeAdded",
        "Node*",
        "newChild",
        "childNodeRemoved",
        "oldChild",
        "name",
        "label",
        "info",
        "icon",
        "nodeType",
        "nodeListModel",
        "NodeListModel*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'nameChanged'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(7, 8, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Signal 'labelChanged'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(11, 8, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 }, { QMetaType::QString, 13 },
        }}),
        // Signal 'infoChanged'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(14, 8, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 }, { QMetaType::QString, 16 },
        }}),
        // Signal 'iconChanged'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(17, 8, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::QString, 19 },
        }}),
        // Signal 'nodeTypeChanged'
        QtMocHelpers::SignalData<void(NodeType *, NodeType *)>(20, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 }, { 0x80000000 | 21, 23 },
        }}),
        // Signal 'childNodeAdded'
        QtMocHelpers::SignalData<void(Node *)>(24, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 25, 26 },
        }}),
        // Signal 'childNodeRemoved'
        QtMocHelpers::SignalData<void(Node *)>(27, 8, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 25, 28 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'name'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 0),
        // property 'label'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'info'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 2),
        // property 'icon'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 3),
        // property 'nodeType'
        QtMocHelpers::PropertyData<NodeType*>(33, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Final, 4),
        // property 'nodeListModel'
        QtMocHelpers::PropertyData<NodeListModel*>(34, 0x80000000 | 35, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant | QMC::Final),
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
            {    3,    4 },
            {    5,    6 },
    });
    return QtMocHelpers::metaObjectData<Node, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject Node::staticMetaObject = { {
    QMetaObject::SuperData::link<Storable::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4NodeE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4NodeE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4NodeE_t>.metaTypes,
    nullptr
} };

void Node::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Node *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->nameChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])), QPrivateSignal()); break;
        case 1: _t->labelChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])), QPrivateSignal()); break;
        case 2: _t->infoChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])), QPrivateSignal()); break;
        case 3: _t->iconChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])), QPrivateSignal()); break;
        case 4: _t->nodeTypeChanged((*reinterpret_cast< std::add_pointer_t<NodeType*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NodeType*>>(_a[2])), QPrivateSignal()); break;
        case 5: _t->childNodeAdded((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        case 6: _t->childNodeRemoved((*reinterpret_cast< std::add_pointer_t<Node*>>(_a[1])), QPrivateSignal()); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
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
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Node::*)(const QString & , const QString & , QPrivateSignal)>(_a, &Node::nameChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Node::*)(const QString & , const QString & , QPrivateSignal)>(_a, &Node::labelChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Node::*)(const QString & , const QString & , QPrivateSignal)>(_a, &Node::infoChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Node::*)(const QString & , const QString & , QPrivateSignal)>(_a, &Node::iconChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Node::*)(NodeType * , NodeType * , QPrivateSignal)>(_a, &Node::nodeTypeChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Node::*)(Node * , QPrivateSignal)>(_a, &Node::childNodeAdded, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Node::*)(Node * , QPrivateSignal)>(_a, &Node::childNodeRemoved, 6))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NodeListModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->label(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->info(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->icon(); break;
        case 4: *reinterpret_cast<NodeType**>(_v) = _t->nodeType(); break;
        case 5: *reinterpret_cast<NodeListModel**>(_v) = _t->nodeListModel(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setLabel(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setInfo(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setIcon(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Node::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Node::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4NodeE_t>.strings))
        return static_cast<void*>(this);
    return Storable::qt_metacast(_clname);
}

int Node::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Storable::qt_metacall(_c, _id, _a);
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
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Node::nameChanged(const QString & _t1, const QString & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void Node::labelChanged(const QString & _t1, const QString & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3);
}

// SIGNAL 2
void Node::infoChanged(const QString & _t1, const QString & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}

// SIGNAL 3
void Node::iconChanged(const QString & _t1, const QString & _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void Node::nodeTypeChanged(NodeType * _t1, NodeType * _t2, QPrivateSignal _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2, _t3);
}

// SIGNAL 5
void Node::childNodeAdded(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void Node::childNodeRemoved(Node * _t1, QPrivateSignal _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}
QT_WARNING_POP
