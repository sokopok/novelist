#include "request.h"
#include "client.h"

namespace ai::responses {

Request::Request()
    : Request(new RequestData)
{}

Request::Request(RequestData* data)
    : ai::Request{data ? data : new RequestData}
{}

} // namespace ai::responses
