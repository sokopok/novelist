#include "imagesclient.h"

namespace ai {

ImagesClient::ImagesClient(QObject *parent)
    : Client{parent}
{}

ImagesResponse *ImagesClient::post(const ImagesRequest &request)
{
    auto *network = networkAccessManager();
    if (!network) {
        setError({Error::InternalErrorType, Error::InternalError, "No networkAccessManager"});
        return nullptr;
    }

    ImagesRequest r = request;
    if (r.apiKey().isEmpty())
        r.setApiKey(apiKey());

    const auto json = r.toJson();
    const auto data = QJsonDocument{json}.toJson();

    qDebug().noquote().nospace() << "POST: " << data;

    return new ImagesResponse{request, network->post(r, data), this};
}

} // namespace ai
