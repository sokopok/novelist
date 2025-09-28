#include "client.h"
#include "request.h"

namespace ai {

Response *responses::Client::post(const Request &request, QIODevice *device)
{
    return ai::Client::post(request, device);
}

} // namespace ai
