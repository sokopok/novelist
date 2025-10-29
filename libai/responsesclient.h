#ifndef LIBAI_RESPONSESCLIENT_H
#define LIBAI_RESPONSESCLIENT_H

#include "client.h"
#include "responsesresponse.h"

namespace ai {

class ResponsesClient : public Client
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ResponsesClient)

public:
    explicit ResponsesClient(QObject* parent = nullptr);

    virtual Q_INVOKABLE ResponsesResponse* post(const ResponsesRequest& request);

    bool resetApiUrl() override { return setApiUrl(QUrl{"https://api.openai.com/v1/responses"}); }
    bool resetApiKey() override
    {
        if (auto* tp = tokenProvider())
            return setApiKey(tp->apiKey());
        return setApiKey({});
    }
};

} // namespace ai

#endif // LIBAI_RESPONSESCLIENT_H
