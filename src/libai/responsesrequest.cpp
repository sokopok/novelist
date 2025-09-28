#include "responsesrequest.h"
#include "client.h"

namespace ai {

ResponsesRequestData::ResponsesRequestData() {}

ResponsesRequestData::ResponsesRequestData(const RequestData& requestData)
    : RequestData{requestData}
{}

ResponsesRequest::ResponsesRequest(QObject* parent)
    : Request{parent}
{}

} // namespace ai
