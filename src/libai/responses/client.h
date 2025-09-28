#ifndef AI_RESPONSES_CLIENT_H
#define AI_RESPONSES_CLIENT_H

#include "../client.h"

namespace ai::responses {

class Request;

class Client : public ai::Client
{
    Q_OBJECT

public:
    explicit Client(QObject* parent = nullptr)
        : ai::Client{parent}
    {}

    using ai::Client::post;
    virtual Q_INVOKABLE Response* post(const Request& request, QIODevice* device = nullptr);
};

} // namespace ai

#endif // AI_RESPONSES_CLIENT_H
