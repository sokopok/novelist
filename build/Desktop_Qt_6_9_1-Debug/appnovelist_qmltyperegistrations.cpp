/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<textareautils.h>)
#  include <textareautils.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_appnovelist()
{
    qmlRegisterModule("appnovelist", 254, 0);
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<TextAreaUtils>("appnovelist", 254);
    QT_WARNING_POP
    qmlRegisterModule("appnovelist", 254, 254);
}

static const QQmlModuleRegistration appnovelistRegistration("appnovelist", qml_register_types_appnovelist);
