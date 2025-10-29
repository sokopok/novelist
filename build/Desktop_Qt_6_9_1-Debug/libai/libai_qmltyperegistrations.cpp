/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<client.h>)
#  include <client.h>
#endif
#if __has_include(<imagesresponse.h>)
#  include <imagesresponse.h>
#endif
#if __has_include(<request.h>)
#  include <request.h>
#endif
#if __has_include(<response.h>)
#  include <response.h>
#endif
#if __has_include(<responsesclient.h>)
#  include <responsesclient.h>
#endif
#if __has_include(<responsesrequest.h>)
#  include <responsesrequest.h>
#endif
#if __has_include(<responsesrequestutils.h>)
#  include <responsesrequestutils.h>
#endif
#if __has_include(<responsesresponse.h>)
#  include <responsesresponse.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_libai()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    QMetaType::fromType<QNetworkRequest>().id();
    QMetaType::fromType<QNetworkRequest::KnownHeaders>().id();
    qmlRegisterTypesAndRevisions<ai::AiBase>("libai", 1);
    qmlRegisterTypesAndRevisions<ai::AiItemReference>("libai", 1);
    QMetaType::fromType<ai::Base>().id();
    qmlRegisterTypesAndRevisions<ai::Client>("libai", 1);
    qmlRegisterTypesAndRevisions<ai::ImagesResponse>("libai", 1);
    qmlRegisterTypesAndRevisions<ai::Input>("libai", 1);
    qmlRegisterTypesAndRevisions<ai::Request>("libai", 1);
    QMetaType::fromType<ai::Request::Attribute>().id();
    QMetaType::fromType<ai::Request::Error>().id();
    qmlRegisterTypesAndRevisions<ai::Response>("libai", 1);
    QMetaType::fromType<ai::Response::Attribute>().id();
    qmlRegisterTypesAndRevisions<ai::ResponsesClient>("libai", 1);
    qmlRegisterTypesAndRevisions<ai::ResponsesRequest>("libai", 1);
    QMetaType::fromType<ai::ResponsesRequest::Attribute>().id();
    QMetaType::fromType<ai::ResponsesRequest::Model>().id();
    QMetaType::fromType<ai::ResponsesRequest::ServiceTier>().id();
    QMetaType::fromType<ai::ResponsesRequest::Truncation>().id();
    qmlRegisterTypesAndRevisions<ai::ResponsesResponse>("libai", 1);
    QMetaType::fromType<ai::ResponsesResponse::Attribute>().id();
    QMetaType::fromType<ai::ResponsesResponse::Status>().id();
    QT_WARNING_POP
    qmlRegisterModule("libai", 1, 0);
}

static const QQmlModuleRegistration libaiRegistration("libai", qml_register_types_libai);
