#ifndef AI_CONFIG_ERROR_H
#define AI_CONFIG_ERROR_H

#include "base.h"

namespace ai {

class Error
{
    Q_GADGET
    Q_PROPERTY(AiObjectType objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(Type type READ type WRITE setType FINAL)
    Q_PROPERTY(Code code READ code WRITE setCode FINAL)
    Q_PROPERTY(QString message READ message WRITE setMessage FINAL)
    Q_PROPERTY(QString param READ param WRITE setParam FINAL)

public:
    enum Code {
        NoError,
        UnknownError,
        InternalError,
        NetworkError,
        SslError,
        MissingRequiredParameter
    };
    Q_ENUM(Code)

    enum Type {
        NoErrorType,
        UnknownErrorType,
        InternalErrorType,
        NetworkErrorType,
        InvalidRequestErrorType
    };
    Q_ENUM(Type)

private:
    QString m;
    QString p;
    Type t = NoErrorType;
    Code c = NoError;
    QJsonObject e;

    inline static QMap<Code, QString> codeKV = {{NoError, "no_error"},
                                                {MissingRequiredParameter,
                                                 "missing_required_parameter"}};
    inline static QMap<Type, QString> typeKV = {{NoErrorType, "no_error"},
                                                {NetworkErrorType, "network_error"},
                                                {InvalidRequestErrorType, "invalid_request_error"}};

public:
    Error(const QJsonObject& extra = {})
        : e{extra}
    {}
    Error(Type type,
          Code code = NoError,
          const QString& message = {},
          const QString& param = {},
          const QJsonObject& extra = {})
        : m{message}
        , p{param}
        , t{type}
        , c{code}
        , e{extra}
    {}

    [[nodiscard]] AiObjectType objectType() const { return AiObjectType::Error; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString message() const { return m; }
    Error& setMessage(const QString& message)
    {
        m = message;
        return *this;
    }

    [[nodiscard]] QString param() const { return p; }
    Error& setParam(const QString& param)
    {
        p = param;
        return *this;
    }

    [[nodiscard]] Code code() const { return c; }
    Error& setCode(Code code)
    {
        c = code;
        return *this;
    }
    Error& setCode(const QString& code)
    {
        c = Code(QMetaEnum::fromType<Code>().keyToValue(code.toUtf8()));
        return *this;
    }

    [[nodiscard]] Type type() const { return t; }
    Error& setType(Type type)
    {
        t = type;
        return *this;
    }
    Error& setType(const QString& type)
    {
        t = Type(QMetaEnum::fromType<Type>().keyToValue(type.toUtf8()));
        return *this;
    }

    [[nodiscard]] bool operator==(const Error& that) const
    {
        return c == that.c && t == that.t && m == that.m && p == that.p && e == that.e;
    }

    [[nodiscard]] bool isError() const { return t != NoErrorType || c != NoError; }
    [[nodiscard]] bool isEmpty() const
    {
        return c == 0 && t == 0 && m.isEmpty() && p.isEmpty() && e.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return c != 0 || t != 0 || !m.isEmpty() || !p.isEmpty(); }

    static Code toCode(const QString& code) { return Code(codeKV.key(code, Code::NoError)); }
    static Code toCode(int code)
    {
        const auto metaEnum = QMetaEnum::fromType<Code>();
        for (int i = 0; i < metaEnum.keyCount(); ++i)
            if (metaEnum.value(i) == code)
                return Code(i);
        return Code::UnknownError;
    }
    static QString toString(Code code) { return codeKV.value(code, QString::number(code)); }
    static int toInt(Code code) { return std::to_underlying(code); }

    static Type toType(const QString& type) { return Type(typeKV.key(type, Type::NoErrorType)); }
    static Type toType(int type)
    {
        const auto metaEnum = QMetaEnum::fromType<Type>();
        for (int i = 0; i < metaEnum.keyCount(); ++i)
            if (metaEnum.value(i) == type)
                return Type(i);
        return Type::UnknownErrorType;
    }
    static QString toString(Type type) { return typeKV.value(type, QString::number(type)); }
    static int toInt(Type type) { return std::to_underlying(type); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        if (c != 0)
            json.insert(QStringLiteral("code"), toString(c));

        if (t != 0)
            json.insert(QStringLiteral("type"), toString(t));

        if (!m.isEmpty())
            json.insert(QStringLiteral("text"), m);

        if (!p.isEmpty())
            json.insert(QStringLiteral("param"), p);

        return json;
    }

    static Error fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        // if (json.value(QStringLiteral("type")).toString() != QStringLiteral("error")) {
        //     if (ok)
        //         *ok = false;
        //     return {};
        // }

        QJsonObject x = json;
        // extra.remove(QStringLiteral("type"));

        QString m;
        QString p;
        Code c = NoError;
        Type t = NoErrorType;

        if (json.contains(QStringLiteral("message"))) {
            if (const auto v = json.value(QStringLiteral("message")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                m = v.toString();
                x.remove(QStringLiteral("message"));
            }
        }

        if (json.contains(QStringLiteral("param"))) {
            if (const auto v = json.value(QStringLiteral("param")); v.isString()) {
                p = v.toString();
                x.remove(QStringLiteral("param"));
            } else if (ok)
                *ok = false;
        }

        if (json.contains(QStringLiteral("code"))) {
            if (const auto v = json.value(QStringLiteral("code")); v.isDouble()) {
                c = toCode(v.toInt());
                x.remove(QStringLiteral("code"));
            }

            else if (v.isString()) {
                c = toCode(v.toString());
                x.remove(QStringLiteral("code"));
            }

            else if (ok)
                *ok = false;
        }

        if (json.contains(QStringLiteral("type"))) {
            if (const auto v = json.value(QStringLiteral("type")); v.isDouble()) {
                t = toType(v.toInt());
                x.remove(QStringLiteral("type"));
            }

            else if (v.isString()) {
                t = toType(v.toString());
                x.remove(QStringLiteral("type"));
            }

            else if (ok)
                *ok = false;

        }

        else if (ok)
            *ok = false;

        return {t, c, m, p, x};
    }
};

} // namespace ai

#endif // AI_CONFIG_ERROR_H
