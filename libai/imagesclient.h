#ifndef LIBAI_IMAGESCLIENT_H
#define LIBAI_IMAGESCLIENT_H

#include "client.h"
#include "imagesresponse.h"

namespace ai {

class ImagesClient : public Client
{
    Q_OBJECT

public:
    explicit ImagesClient(QObject* parent = nullptr);

    virtual Q_INVOKABLE ImagesResponse* post(const ImagesRequest& request);

    bool resetApiUrl() override
    {
        return setApiUrl(QUrl{"https://api.openai.com/v1/images/generations"});
    }
    bool resetApiKey() override
    {
        if (auto* tp = tokenProvider())
            return setApiKey(tp->apiKey());
        return setApiKey({});
    }
};

} // namespace ai

#endif // LIBAI_IMAGESCLIENT_H
