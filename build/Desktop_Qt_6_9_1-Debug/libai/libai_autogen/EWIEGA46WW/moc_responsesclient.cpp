/****************************************************************************
** Meta object code from reading C++ file 'responsesclient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../libai/responsesclient.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'responsesclient.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN2ai15ResponsesClientE_t {};
} // unnamed namespace

template <> constexpr inline auto ai::ResponsesClient::qt_create_metaobjectdata<qt_meta_tag_ZN2ai15ResponsesClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ai::ResponsesClient",
        "QML.Element",
        "ResponsesClient",
        "post",
        "ResponsesResponse*",
        "",
        "ResponsesRequest",
        "request"
    };

    QtMocHelpers::UintData qt_methods {
        // Method 'post'
        QtMocHelpers::MethodData<ResponsesResponse *(const ResponsesRequest &)>(3, 5, QMC::AccessPublic, 0x80000000 | 4, {{
            { 0x80000000 | 6, 7 },
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
    return QtMocHelpers::metaObjectData<ResponsesClient, void>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject ai::ResponsesClient::staticMetaObject = { {
    QMetaObject::SuperData::link<Client::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15ResponsesClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15ResponsesClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2ai15ResponsesClientE_t>.metaTypes,
    nullptr
} };

void ai::ResponsesClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ResponsesClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { ResponsesResponse* _r = _t->post((*reinterpret_cast< std::add_pointer_t<ResponsesRequest>>(_a[1])));
            if (_a[0]) *reinterpret_cast< ResponsesResponse**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject *ai::ResponsesClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ai::ResponsesClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2ai15ResponsesClientE_t>.strings))
        return static_cast<void*>(this);
    return Client::qt_metacast(_clname);
}

int ai::ResponsesClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Client::qt_metacall(_c, _id, _a);
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
