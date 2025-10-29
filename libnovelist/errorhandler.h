#ifndef LIBNOVELIST_ERRORHANDLER_H
#define LIBNOVELIST_ERRORHANDLER_H

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>

class ErrorHandler
{
    QDebug& debug(QDebug& d, const QVariant& value)
    {
        d << value.toString();
        return d;
    }

    template<typename T>
    QDebug& debug(QDebug& d, const T& value)
    {
        d << value;
        return d;
    }

    template<typename T>
    QDebug& debug(QDebug& d, const QList<T>& values)
    {
        d << values.size() << ": ";
        bool first = true;
        for (const T& v : values) {
            if (!first)
                d << ", ";
            debug(d, v);
            first = false;
        }
        return d;
    }

    template<typename T>
    QDebug& debug(QDebug& d, const QMap<QString, T>& values)
    {
        d << values.size() << ": ";
        bool first = true;
        for (auto it = values.constBegin(); it != values.constEnd(); ++it) {
            if (!first)
                d << ", ";
            d << it.key() << ": ";
            debug(d, it.value());
            first = false;
        }
        return d;
    }

public:
    void handleError(QObject* object, const QString& function, const QString& message)
    {
        qDebug() << object << function << message;
    }
    void handleError(QObject* object, const QString& function, const QStringList& messages)
    {
        qDebug() << object << function << messages;
    }
    void handleError(QObject* object, const QString& function, const QSqlQuery& query)
    {
        qDebug() << object << function << query.lastError().text() << query.lastQuery();
    }
    void handleError(const QString& message) { qDebug() << message; }
    void handleError(const QStringList& messages) { qDebug() << messages; }
    void handleError(const QVariantList& messages)
    {
        QDebug d = qDebug().nospace().noquote();
        bool first = true;
        for (const QVariant& message : messages) {
            if (!first)
                d << '\n';
            debug(d, message);
            first = false;
        }
    }
};

#endif // LIBNOVELIST_ERRORHANDLER_H
