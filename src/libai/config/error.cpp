#include "error.h"

#include <QSharedData>
#include <utility>

namespace ai {

class ErrorData : public QSharedData
{
public:
    QString message;
    QString param;
    Error::Type type = Error::NoErrorType;
    Error::Code code = Error::NoError;
    QJsonObject extra;
};

Error::Error(const QJsonObject &extra)
    : Error(NoErrorType, NoError, {}, {}, extra)
{}

Error::Error(Type type,
             Code code,
             const QString &message,
             const QString &param,
             const QJsonObject &extra)
    : d(new ErrorData)
{
    d->message = message;
    d->param = param;
    d->type = type;
    d->code = code;
    d->extra = extra;
}

Error::Error(const Error &rhs)
    : d{rhs.d}
{}

Error::Error(Error &&rhs)
    : d{std::move(rhs.d)}
{}

Error &Error::operator=(const Error &rhs)
{
    if (this != &rhs)
        d = rhs.d;
    return *this;
}

Error &Error::operator=(Error &&rhs)
{
    if (this != &rhs)
        d = std::move(rhs.d);
    return *this;
}

Error::~Error() = default;

QJsonObject Error::extra() const
{
    return d->extra;
}

QString Error::message() const
{
    return d->message;
}

Error &Error::setMessage(const QString &message)
{
    d->message = message;
    return *this;
}

QString Error::param() const
{
    return d->param;
}

Error &Error::setParam(const QString &param)
{
    d->param = param;
    return *this;
}

Error::Code Error::code() const
{
    return d->code;
}

Error &Error::setCode(Code code)
{
    d->code = code;
    return *this;
}

Error &Error::setCode(const QString &code)
{
    d->code = Code(QMetaEnum::fromType<Code>().keyToValue(code.toUtf8()));
    return *this;
}

Error::Type Error::type() const
{
    return d->type;
}

Error &Error::setType(Type type)
{
    d->type = type;
    return *this;
}

Error &Error::setType(const QString &type)
{
    d->type = Type(QMetaEnum::fromType<Type>().keyToValue(type.toUtf8()));
    return *this;
}

bool Error::operator==(const Error &that) const
{
    return code() == that.code() && type() == that.type() && message() == that.message()
        && param() == that.param() && extra() == that.extra();
}

bool Error::isError() const
{
    return type() != NoErrorType || code() != NoError;
}

bool Error::isEmpty() const
{
    return code() == 0 && type() == 0 && message().isEmpty() && param().isEmpty() && extra().isEmpty();
}

bool Error::isValid() const
{
    return code() != 0 || type() != 0 || !message().isEmpty() || !param().isEmpty();
}

QJsonObject Error::toJson() const
{
    QJsonObject json = extra();

    if (code() != 0)
        json.insert(QStringLiteral("code"), toString(code()));

    if (type() != 0)
        json.insert(QStringLiteral("type"), toString(type()));

    if (!message().isEmpty())
        json.insert(QStringLiteral("text"), message());

    if (!param().isEmpty())
        json.insert(QStringLiteral("param"), param());

    return json;
}

} // namespace ai
