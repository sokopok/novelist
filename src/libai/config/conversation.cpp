#include "conversation.h"
#include <utility>

namespace ai {

class ConversationData : public QSharedData
{
public:
    QString id;
    QJsonObject extra;
};

Conversation::Conversation(const QJsonObject &extra)
    : Conversation({}, extra)
{}

Conversation::Conversation(const QString &id, const QJsonObject &extra)
    : d(new ConversationData)
{
    d->id = id;
    d->extra = extra;
}

Conversation::Conversation(const Conversation &rhs)
    : d{rhs.d}
{}

Conversation::Conversation(Conversation &&rhs)
    : d{std::move(rhs.d)}
{}

Conversation &Conversation::operator=(const Conversation &rhs)
{
    if (this != &rhs)
        d = rhs.d;
    return *this;
}

Conversation &Conversation::operator=(Conversation &&rhs)
{
    if (this != &rhs)
        d = std::move(rhs.d);
    return *this;
}

Conversation::~Conversation() {}

QJsonObject Conversation::extra() const
{
    return d->extra;
}

bool Conversation::setExtra(const QJsonObject &extra)
{
    return d->extra == extra ? false : (d->extra = extra, true);
}

QString Conversation::id() const
{
    return d->id;
}

bool Conversation::setId(const QString &id)
{
    return d->id == id ? false : (d->id = id, true);
}

QJsonObject Conversation::toJson() const
{
    QJsonObject json = d->extra;
    json.insert(QStringLiteral("id"), id());
    json.insert(QStringLiteral("type"), QStringLiteral("conversation"));
    return json;
}

} // namespace ai
