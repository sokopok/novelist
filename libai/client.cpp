#include "client.h"

namespace ai {

Client::Client(QObject *parent)
    : QObject{parent}
{
    resetTokenProvider();
    resetNetworkAccessManager();
    resetApiKey();
    resetApiUrl();
}

Client::~Client()
{
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

} // namespace ai
