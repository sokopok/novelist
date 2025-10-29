#include "responsesclient.h"
#include "responsesresponse.h"

namespace ai {

ResponsesClient::ResponsesClient(QObject *parent)
    : Client{parent}
{
    resetApiUrl();
    resetApiKey();
}

ResponsesResponse *ResponsesClient::post(const ResponsesRequest &request)
{
    auto *network = networkAccessManager();
    if (!network) {
        setError({Error::InternalErrorType, Error::InternalError, "No networkAccessManager"});
        return nullptr;
    }

    ResponsesRequest r = request;
    if (r.apiKey().isEmpty())
        r.setApiKey(apiKey());

    const auto json = r.toJson();
    const auto data = QJsonDocument{json}.toJson();

    qDebug().noquote().nospace() << "POST: " << data;

    auto *response = new ResponsesResponse{request, network->post(r, data), this};
    connect(response,
            &ResponsesResponse::errorOccurred,
            this,
            [this, response](const ai::Error &error) {
                emitResponseErrorOccurred(response, error);
            });
    connect(response, &ResponsesResponse::requestSent, this, [this, response]() {
        emitResponseRequestSent(response);
    });
    connect(response, &ResponsesResponse::readyRead, this, [this, response]() {
        emitResponseReadyRead(response);
    });
    connect(response, &ResponsesResponse::finished, this, [this, response]() {
        emitResponseFinished(response);
    });
    // connect(response,
    //         &ResponsesResponse::textGenerated,
    //         this,
    //         [this, response](const QString &text) { emitResponseTextGenerated(response, text); });
    // connect(response,
    //         &ResponsesResponse::imageGenerated,
    //         this,
    //         [this, response](const QImage &image) { emitResponseImageGenerated(response, image); });

    return response;
}

} // namespace ai
