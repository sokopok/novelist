#include "client.h"
#include "response.h"

namespace ai::responses {

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

    const auto json = QJsonDocument{request.toJson()};
    const auto data = json.toJson();

    qDebug().noquote().nospace() << "POST: " << data;

    return new Response{request, network->post(request, data), this};
}

} // namespace ai::responses
