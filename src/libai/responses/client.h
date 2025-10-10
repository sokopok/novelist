#ifndef AI_RESPONSES_CLIENT_H
#define AI_RESPONSES_CLIENT_H

#include "../client.h"
#include "request.h"

namespace ai::responses {

class Response;

class Client : public ai::Client
{
    Q_OBJECT

public:
    [[nodiscard]] static Client* create(QObject* parent = nullptr);

    virtual Q_INVOKABLE Response* post(const Request& request, QIODevice* device = nullptr);

    bool resetApiUrl() override { return setApiUrl(QUrl{"https://api.openai.com/v1/responses"}); }
    bool resetApiKey() override
    {
        if (auto* tp = tokenProvider())
            return setApiKey(tp->apiKey());
        return setApiKey({});
    }

protected:
    explicit Client(QObject* parent = nullptr);

    void initialize() override;
};

} // namespace ai

#endif // AI_RESPONSES_CLIENT_H
