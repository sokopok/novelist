#include "request.h"
#include "client.h"

namespace ai::responses {

bool RequestData::readJson(const QJsonObject &json, QStringList *errors)
{
    bool ok = ai::RequestData::readJson(json);

    if (json.contains(QStringLiteral("background"))) {
        if (const auto v = json.value(QStringLiteral("background")); v.isBool()) {
            setBackground(v.toBool());
            extra().remove(QStringLiteral("background"));
        } else {
            if (errors)
                errors->append("background is not a boolean");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("conversation"))) {
        if (const auto v = json.value(QStringLiteral("conversation")); v.isString()) {
            setConversation(v.toString());
            extra().remove(QStringLiteral("conversation"));
        } else if (v.isObject()) {
            setConversation(Conversation::fromJson(v.toObject()));
            extra().remove(QStringLiteral("conversation"));
        } else {
            if (errors)
                errors->append("conversation is not a string or object");
            ok = false;
        }
    }

    if (json.contains(QStringLiteral("input"))) {
        if (const auto v = json.value(QStringLiteral("input")); v.isString()) {
            setInput({v.toString()});
            extra().remove(QStringLiteral("input"));
        } else if (v.isArray()) {
            setInput(Input::fromJson(v.toArray()));
            extra().remove(QStringLiteral("input"));
        } else {
            if (errors)
                errors->append("input is not a string or array");
            ok = false;
        }
    }

    return ok;
}

bool RequestData::writeJson(QJsonObject &json, bool full) const
{
    if (!ai::RequestData::writeJson(json, full))
        return false;

    if (full || background())
        json[QStringLiteral("background")] = background();

    if (full || conversation().isValid())
        json[QStringLiteral("conversation")] = conversation().toJson();

    if (full || input().isValid())
        json[QStringLiteral("input")] = input().toJson();

    if (full || !instructions().isEmpty())
        json[QStringLiteral("instructions")] = instructions();

    if (full || !isStored())
        json[QStringLiteral("store")] = isStored();

    if (full || temperature() != 1.0)
        json[QStringLiteral("temperature")] = temperature();

    return true;
}

RequestData *Request::d()
{
    return static_cast<RequestData *>(ai::Request::d);
}

const RequestData *Request::d() const
{
    return static_cast<const RequestData *>(ai::Request::d);
}

Request::Request()
    : Request(new RequestData)
{}

// Request &Request::operator=(const Request &rhs)
// {
//     ai::Request::operator=(rhs);
//     return *this;
// }

bool Request::background() const
{
    return d()->background();
}

Request &Request::setBackground(bool background)
{
    d()->setBackground(background);
    return *this;
}

Request &Request::resetBackground()
{
    d()->resetBackground();
    return *this;
}

Conversation Request::conversation() const
{
    return d()->conversation();
}

Request &Request::setConversation(const Conversation &conversation)
{
    d()->setConversation(conversation);
    return *this;
}

Request &Request::resetConversation()
{
    d()->resetConversation();
    return *this;
}

IncludeList Request::include() const
{
    return d()->include();
}

Request &Request::setInclude(const IncludeList &include)
{
    d()->setInclude(include);
    return *this;
}

Request &Request::resetInclude()
{
    d()->resetInclude();
    return *this;
}

Input Request::input() const
{
    return d()->input();
}

Request &Request::setInput(const Input &input)
{
    d()->setInput(input);
    return *this;
}

Request &Request::resetInput()
{
    d()->resetInput();
    return *this;
}

QString Request::instructions() const
{
    return d()->instructions();
}

Request &Request::setInstructions(const QString &instructions)
{
    d()->setInstructions(instructions);
    return *this;
}

Request &Request::resetInstructions()
{
    d()->resetInstructions();
    return *this;
}

int Request::maxOutputTokens() const
{
    return d()->maxOutputTokens();
}

Request &Request::setMaxOutputTokens(int maxOutputTokens)
{
    d()->setMaxOutputTokens(maxOutputTokens);
    return *this;
}

Request &Request::resetMaxOutputTokens()
{
    d()->resetMaxOutputTokens();
    return *this;
}

int Request::maxToolCalls() const
{
    return d()->maxToolCalls();
}

Request &Request::setMaxToolCalls(int maxToolCalls)
{
    d()->setMaxToolCalls(maxToolCalls);
    return *this;
}

Request &Request::resetMaxToolCalls()
{
    d()->resetMaxToolCalls();
    return *this;
}

bool Request::parallelToolCalls() const
{
    return d()->parallelToolCalls();
}

Request &Request::setParallelToolCalls(bool parallelToolCalls)
{
    d()->setParallelToolCalls(parallelToolCalls);
    return *this;
}

Request &Request::resetParallelToolCalls()
{
    d()->resetParallelToolCalls();
    return *this;
}

QString Request::previousResponseId() const
{
    return d()->previousResponseId();
}

Request &Request::setPreviousResponseId(const QString &previousResponseId)
{
    d()->setPreviousResponseId(previousResponseId);
    return *this;
}

Request &Request::resetPreviousResponseId()
{
    d()->resetPreviousResponseId();
    return *this;
}

Prompt Request::prompt() const
{
    return d()->prompt();
}

Request &Request::setPrompt(const Prompt &prompt)
{
    d()->setPrompt(prompt);
    return *this;
}

Request &Request::resetPrompt()
{
    d()->resetPrompt();
    return *this;
}

QString Request::promptCacheKey() const
{
    return d()->promptCacheKey();
}

Request &Request::setPromptCacheKey(const QString &promptCacheKey)
{
    d()->setPromptCacheKey(promptCacheKey);
    return *this;
}

Request &Request::resetPromptCacheKey()
{
    d()->resetPromptCacheKey();
    return *this;
}

Reasoning Request::reasoning() const
{
    return d()->reasoning();
}

Request &Request::setReasoning(const Reasoning &reasoning)
{
    d()->setReasoning(reasoning);
    return *this;
}

Request &Request::resetReasoning()
{
    d()->resetReasoning();
    return *this;
}

QString Request::safetyIdentifier() const
{
    return d()->safetyIdentifier();
}

Request &Request::setSafetyIdentifier(const QString &safetyIdentifier)
{
    d()->setSafetyIdentifier(safetyIdentifier);
    return *this;
}

Request &Request::resetSafetyIdentifier()
{
    d()->resetSafetyIdentifier();
    return *this;
}

QString Request::serviceTier() const
{
    return d()->serviceTier();
}

Request &Request::setServiceTier(const QString &serviceTier)
{
    d()->setServiceTier(serviceTier);
    return *this;
}

Request &Request::resetServiceTier()
{
    d()->resetServiceTier();
    return *this;
}

bool Request::isStored() const
{
    return d()->isStored();
}

Request &Request::setStored(bool store)
{
    d()->setStored(store);
    return *this;
}

Request &Request::resetStored()
{
    d()->resetStored();
    return *this;
}

double Request::temperature() const
{
    return d()->temperature();
}

Request &Request::setTemperature(double temperature)
{
    d()->setTemperature(temperature);
    return *this;
}

Request &Request::resetTemperature()
{
    d()->resetTemperature();
    return *this;
}

int Request::topLogprobs() const
{
    return d()->topLogprobs();
}

Request &Request::setTopLogprobs(int topLogprobs)
{
    d()->setTopLogprobs(topLogprobs);
    return *this;
}

Request &Request::resetTopLogprobs()
{
    d()->resetTopLogprobs();
    return *this;
}

double Request::topP() const
{
    return d()->topP();
}

Request &Request::setTopP(double topP)
{
    d()->setTopP(topP);
    return *this;
}

Request &Request::resetTopP()
{
    d()->resetTopP();
    return *this;
}

Request::Truncation Request::truncation() const
{
    return d()->truncation();
}

Request &Request::setTruncation(Truncation truncation)
{
    d()->setTruncation(truncation);
    return *this;
}

Request &Request::setTruncation(const QString &truncation)
{
    d()->setTruncation(truncation);
    return *this;
}

Request &Request::resetTruncation()
{
    d()->resetTruncation();
    return *this;
}

Request::Request(RequestData* data)
    : ai::Request{data ? data : new RequestData}
{}

bool Request::readJson(const QJsonObject &json, QStringList *errors)
{
    if (!ai::Request::readJson(json, errors))
        return false;
    return d()->readJson(json, errors);
}

bool Request::writeJson(QJsonObject &json, bool full) const
{
    if (!ai::Request::writeJson(json, full))
        return false;

    const ai::responses::RequestData *D = (const ai::responses::RequestData *) d();
    return D->ai::responses::RequestData ::writeJson(json, full);
}

} // namespace ai::responses
