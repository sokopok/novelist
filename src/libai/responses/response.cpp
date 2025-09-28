#include "response.h"
#include "client.h"

namespace ai::responses {

Response::Response(const Request &request, QNetworkReply *reply, Client *client)
    : Response(new ResponseData, request, reply, client)
{}

Response::Response(ResponseData *data, const Request &request, QNetworkReply *reply, Client *client)
    : ai::Response{data, request, reply, client}
{}

} // namespace ai::responses
