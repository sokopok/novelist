#ifndef LIBNOVELIST_LOGGING_H
#define LIBNOVELIST_LOGGING_H

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(projectCore)
Q_DECLARE_LOGGING_CATEGORY(projectStorage)
Q_DECLARE_LOGGING_CATEGORY(projectLifecycle)

#define ERROR_PROJECTCORE(MSG) \
    qCDebug(projectCore) << MSG << "at" << __FILE__ << __LINE__; \
    if (errors) \
        errors->append(MSG);

#define ERROR_PROJECTSTORAGE(MSG) \
    qCDebug(projectStorage) << MSG << "at" << __FILE__ << __LINE__; \
    if (errors) \
        errors->append(MSG);

#define ERROR_PROJECTLIFECYCLE(MSG) \
    qCDebug(projectLifecycle) << MSG << "at" << __FILE__ << __LINE__; \
    if (errors) \
        errors->append(MSG);

#define ERROR_PROJECT(BUS, MSG) \
    qCDebug(BUS) << MSG << "at" << __FILE__ << __LINE__; \
    if (errors) \
        errors->append(MSG);

#endif // LIBNOVELIST_LOGGING_H
