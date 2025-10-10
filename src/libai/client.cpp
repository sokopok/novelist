#include "client.h"

namespace ai {

Client::Client(QObject *parent)
    : QObject{parent}
{}

Client::~Client()
{
}

Client *Client::create(QObject *parent)
{
    Client *client = new Client{parent};
    client->initialize();
    return client;
}

void Client::initialize()
{
    resetTokenProvider();
    resetNetworkAccessManager();
    resetApiKey();
    resetApiUrl();
}

void Client::setError(const Error &error)
{
    mError = error;
    if (mError.code() != Error::NoError) {
        qWarning() << "Client::setError" << mError.type() << mError.code() << mError.message()
                   << mError.param();
        emit errorOccurred(mError, QPrivateSignal{});
    }
}

QMap<QString, Request *> Client::pendingRequests() const
{
    return mPendingRequests;
}

QMap<QString, Request *> &Client::pendingRequests()
{
    return mPendingRequests;
}

void Client::addRecycledRequest(Request *request)
{
    if (!request) {
        qWarning() << "No request";
        return;
    }
    recycledRequests().append(request);
}

QList<Request *> Client::recycledRequests() const
{
    return mRecycledRequests;
}

QList<Request *> &Client::recycledRequests()
{
    return mRecycledRequests;
}

} // namespace ai
