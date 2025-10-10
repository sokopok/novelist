#include "client.h"
#include "response.h"

namespace ai::images {

Client::Client(QObject *parent)
    : ai::Client{parent}
{}

Client *Client::create(QObject *parent)
{
    Client *client = new Client{parent};
    client->initialize();
    return client;
}

void Client::initialize()
{
    ai::Client::initialize();
}

Response *Client::post(const Request &request, QIODevice *device)
{
    auto *network = networkAccessManager();
    if (!network) {
        setError({Error::InternalErrorType, Error::InternalError, "No networkAccessManager"});
        return nullptr;
    }

    Request r = request;
    if (r.apiKey().isEmpty())
        r.setApiKey(mApiKey);

    const auto json = r.toJson();
    const auto data = QJsonDocument{json}.toJson();

    qDebug().noquote().nospace() << "POST: " << data;

    return new Response{request, network->post(r, data), this};
}

} // namespace ai::images
