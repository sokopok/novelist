#include "client.h"
#include "response.h"

namespace ai::responses {

Client::Client(QObject *parent)
    : Client{new RequestData, parent}
{}

Client::Client(RequestData *data, QObject *parent)
    : ai::Client{data ? data : new RequestData, parent}
{
}

Client *Client::create(QObject *parent)
{
    Client *client = new Client{parent};
    client->initialize();
    return client;
}

bool Client::prepareRequest(Request *request)
{
    if (!ai::Client::prepareRequest(request))
        return false;

    if (!request->isExplicit(Request::BackgroundAttribute)) {
        if (d()->isExplicit(Request::BackgroundAttribute))
            request->setBackground(background());
        // else {
        //     setError(
        //         {Error::InternalErrorType, Error::InternalError, "prepareRequest", "background"});
        //     return false;
        // }
    }

    if (!request->isExplicit(Request::ConversationAttribute)) {
        if (d()->isExplicit(Request::ConversationAttribute))
            request->setConversation(conversation());
        // else {
        //     setError(
        //         {Error::InternalErrorType, Error::InternalError, "prepareRequest", "conversation"});
        //     return false;
        // }
    }

    if (!request->isExplicit(Request::IncludeAttribute)) {
        if (d()->isExplicit(Request::IncludeAttribute))
            request->setInclude(include());
    } else if (d()->isExplicit(Request::IncludeAttribute)) {
        auto md = metadata();
        for (auto it = request->metadata().begin(), end = request->metadata().end(); it != end; ++it)
            md[it.key()] = it.value();
        request->setMetadata(md);
    }

    if (d()->isExplicit(Request::InputAttribute)) {
        request->setInput(input().merge(request->input()));
    }

    if (!request->isExplicit(Request::InstructionsAttribute)) {
        if (d()->isExplicit(Request::InstructionsAttribute))
            request->setInstructions(instructions());
    } else if (d()->isExplicit(Request::InstructionsAttribute))
        request->setInstructions(instructions() + '\n' + request->instructions());

    if (!request->isExplicit(Request::StoredAttribute)) {
        if (d()->isExplicit(Request::StoredAttribute))
            request->setStored(isStored());
        // else {
        //     setError({Error::InternalErrorType, Error::InternalError, "prepareRequest", "store"});
        //     return false;
        // }
    }

    if (!request->isExplicit(Request::TemperatureAttribute)) {
        if (d()->isExplicit(Request::TemperatureAttribute))
            request->setTemperature(temperature());
        // else {
        //     setError(
        //         {Error::InternalErrorType, Error::InternalError, "prepareRequest", "temperature"});
        //     return false;
        // }
    }

    return true;
}

Response *Client::post(const Request &request, QIODevice *device)
{
    auto *network = networkAccessManager();
    if (!network) {
        setError({Error::InternalErrorType, Error::InternalError, "No networkAccessManager"});
        return nullptr;
    }

    Request r = request;

    if (!prepareRequest(&r)) {
        setError({Error::InternalErrorType, Error::InternalError, "Couldn't prepare request"});
        return nullptr;
    }

    qDebug() << "prepared request:" << r.toJson();
    qDebug() << "prepared request:" << r.toJson(true);

    // if (!validateRequest(r)) {
    //     setError({Error::InternalErrorType, Error::InternalError, "Couldn't validate request"});
    //     return nullptr;
    // }

    const auto data = QJsonDocument{r.toJson()}.toJson();

    // qDebug().noquote().nospace() << toJson(true);
    // qDebug().noquote().nospace() << r.url().toString() << '\n' << data;

    return new Response{r, network->post(r, data), this};
}

bool Client::validateRequest(const Request &request) const
{
    if (!ai::Client::validateRequest(request))
        return false;

    if (!request.conversation().isValid()) {
        return false;
    }

    if (!request.input().isValid()) {
        return false;
    }

    return true;
}

void Client::initialize()
{
    ai::Client::initialize();

    setApiUrl(QUrl{"https://api.openai.com/v1/responses"});
    resetBackground();
    resetMaxOutputTokens();
    resetMaxToolCalls();
    resetParallelToolCalls();
    resetStored();
    resetTemperature();
    resetTopLogprobs();
    resetTopP();
}

void Client::setPopulateRequestBehaviour(const PopulateRequestBehaviour &populateRequestBehaviour)
{
    if (mPopulateRequestBehaviour == populateRequestBehaviour)
        return;
    mPopulateRequestBehaviour = populateRequestBehaviour;
    emit populateRequestBehaviourChanged();
}

bool Client::background() const
{
    return d()->background();
}

Client &Client::setBackground(bool background)
{
    d()->setBackground(background);
    return *this;
}

Client &Client::resetBackground()
{
    d()->resetBackground(Request::SetExplicit);
    return *this;
}

Conversation Client::conversation() const
{
    return d()->conversation();
}

Client &Client::setConversation(const Conversation &conversation)
{
    d()->setConversation(conversation);
    return *this;
}

Client &Client::resetConversation()
{
    d()->resetConversation();
    return *this;
}

IncludeList Client::include() const
{
    return d()->include();
}

Client &Client::setInclude(const IncludeList &include)
{
    d()->setInclude(include);
    return *this;
}

Client &Client::resetInclude()
{
    d()->resetInclude();
    return *this;
}

Input Client::input() const
{
    return d()->input();
}

Client &Client::setInput(const Input &input)
{
    d()->setInput(input);
    return *this;
}

Client &Client::resetInput()
{
    d()->resetInput();
    return *this;
}

QString Client::instructions() const
{
    return d()->instructions();
}

Client &Client::setInstructions(const QString &instructions)
{
    d()->setInstructions(instructions);
    return *this;
}

Client &Client::resetInstructions()
{
    d()->resetInstructions();
    return *this;
}

int Client::maxOutputTokens() const
{
    return d()->maxOutputTokens();
}

Client &Client::setMaxOutputTokens(int maxOutputTokens)
{
    d()->setMaxOutputTokens(maxOutputTokens);
    return *this;
}

Client &Client::resetMaxOutputTokens()
{
    d()->resetMaxOutputTokens();
    return *this;
}

int Client::maxToolCalls() const
{
    return d()->maxToolCalls();
}

Client &Client::setMaxToolCalls(int maxToolCalls)
{
    d()->setMaxToolCalls(maxToolCalls);
    return *this;
}

Client &Client::resetMaxToolCalls()
{
    d()->resetMaxToolCalls();
    return *this;
}

bool Client::parallelToolCalls() const
{
    return d()->parallelToolCalls();
}

Client &Client::setParallelToolCalls(bool parallelToolCalls)
{
    d()->setParallelToolCalls(parallelToolCalls);
    return *this;
}

Client &Client::resetParallelToolCalls()
{
    d()->resetParallelToolCalls();
    return *this;
}

QString Client::previousResponseId() const
{
    return d()->previousResponseId();
}

Client &Client::setPreviousResponseId(const QString &previousResponseId)
{
    d()->setPreviousResponseId(previousResponseId);
    return *this;
}

Client &Client::resetPreviousResponseId()
{
    d()->resetPreviousResponseId();
    return *this;
}

Prompt Client::prompt() const
{
    return d()->prompt();
}

Client &Client::setPrompt(const Prompt &prompt)
{
    d()->setPrompt(prompt);
    return *this;
}

Client &Client::resetPrompt()
{
    d()->resetPrompt();
    return *this;
}

QString Client::promptCacheKey() const
{
    return d()->promptCacheKey();
}

Client &Client::setPromptCacheKey(const QString &promptCacheKey)
{
    d()->setPromptCacheKey(promptCacheKey);
    return *this;
}

Client &Client::resetPromptCacheKey()
{
    d()->resetPromptCacheKey();
    return *this;
}

Reasoning Client::reasoning() const
{
    return d()->reasoning();
}

Client &Client::setReasoning(const Reasoning &reasoning)
{
    d()->setReasoning(reasoning);
    return *this;
}

Client &Client::resetReasoning()
{
    d()->resetReasoning();
    return *this;
}

QString Client::safetyIdentifier() const
{
    return d()->safetyIdentifier();
}

Client &Client::setSafetyIdentifier(const QString &safetyIdentifier)
{
    d()->setSafetyIdentifier(safetyIdentifier);
    return *this;
}

Client &Client::resetSafetyIdentifier()
{
    d()->resetSafetyIdentifier();
    return *this;
}

QString Client::serviceTier() const
{
    return d()->serviceTier();
}

Client &Client::setServiceTier(const QString &serviceTier)
{
    d()->setServiceTier(serviceTier);
    return *this;
}

Client &Client::resetServiceTier()
{
    d()->resetServiceTier();
    return *this;
}

bool Client::isStored() const
{
    return d()->isStored();
}

Client &Client::setStored(bool store)
{
    d()->setStored(store);
    return *this;
}

Client &Client::resetStored()
{
    d()->resetStored();
    return *this;
}

double Client::temperature() const
{
    return d()->temperature();
}

Client &Client::setTemperature(double temperature)
{
    d()->setTemperature(temperature);
    return *this;
}

Client &Client::resetTemperature()
{
    d()->resetTemperature();
    return *this;
}

int Client::topLogprobs() const
{
    return d()->topLogprobs();
}

Client &Client::setTopLogprobs(int topLogprobs)
{
    d()->setTopLogprobs(topLogprobs);
    return *this;
}

Client &Client::resetTopLogprobs()
{
    d()->resetTopLogprobs();
    return *this;
}

double Client::topP() const
{
    return d()->topP();
}

Client &Client::setTopP(double topP)
{
    d()->setTopP(topP);
    return *this;
}

Client &Client::resetTopP()
{
    d()->resetTopP();
    return *this;
}

Request::Truncation Client::truncation() const
{
    return d()->truncation();
}

Client &Client::setTruncation(Request::Truncation truncation)
{
    d()->setTruncation(truncation);
    return *this;
}

Client &Client::setTruncation(const QString &truncation)
{
    d()->setTruncation(truncation);
    return *this;
}

Client &Client::resetTruncation()
{
    d()->resetTruncation();
    return *this;
}

} // namespace ai::responses
