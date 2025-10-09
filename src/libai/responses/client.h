#ifndef AI_RESPONSES_CLIENT_H
#define AI_RESPONSES_CLIENT_H

#include "../client.h"
#include "request.h"

namespace ai::responses {

class Response;

class Client : public ai::Client
{
    Q_OBJECT

protected:
    RequestData* d() { return static_cast<RequestData*>(ai::Client::d); }
    const RequestData* d() const { return static_cast<const RequestData*>(ai::Client::d); }

    explicit Client(QObject* parent = nullptr);

public:
    enum PopulateRequestBehaviour {
        RequestThenClient,
        ClientThenRequest,
        RequestAndClient,
        ClientAndRequest
    };
    Q_ENUM(PopulateRequestBehaviour)

    [[nodiscard]] static Client* create(QObject* parent = nullptr);

    // using ai::Client::post;
    virtual Q_INVOKABLE Response* post(const Request& request, QIODevice* device = nullptr);

    Client& resetApiUrl() override
    {
        setApiUrl(QUrl{"https://api.openai.com/v1/responses"});
        return *this;
    }
    Client& resetApiKey() override
    {
        if (auto* tp = tokenProvider())
            setApiKey(tp->apiKey());
        // else
        //     setApiKey(
        //         QByteArray{"sk-proj-BIMS9hXqa-TurELZofPOGNECAULkl3f2L3atzXyaeXDU1uVVCvBb0Txg4sBH_"
        //                    "KQOL4kVZaWMXvT3BlbkFJW0NTHPaxqjSjvqfbDGAE7_xSOFurIWZ61iq4pTp-"
        //                    "8tS9Qe0bLHSjlATLLfhtt8A7oz2ujE9aYA"});
        return *this;
    }
    // Client& resetModel() override
    // {
    //     setModel("");
    //     return *this;
    // }

    [[nodiscard]] bool background() const;
    Client& setBackground(bool background);
    Client& resetBackground();

    [[nodiscard]] Conversation conversation() const;
    Client& setConversation(const Conversation& conversation);
    Client& resetConversation();

    [[nodiscard]] IncludeList include() const;
    Client& setInclude(const IncludeList& include);
    Client& resetInclude();

    [[nodiscard]] Input input() const;
    Client& setInput(const Input& input);
    Client& resetInput();

    [[nodiscard]] QString instructions() const;
    Client& setInstructions(const QString& instructions);
    Client& resetInstructions();

    [[nodiscard]] int maxOutputTokens() const;
    Client& setMaxOutputTokens(int maxOutputTokens);
    Client& resetMaxOutputTokens();

    [[nodiscard]] int maxToolCalls() const;
    Client& setMaxToolCalls(int maxToolCalls);
    Client& resetMaxToolCalls();

    [[nodiscard]] bool parallelToolCalls() const;
    Client& setParallelToolCalls(bool parallelToolCalls);
    Client& resetParallelToolCalls();

    [[nodiscard]] QString previousResponseId() const;
    Client& setPreviousResponseId(const QString& previousResponseId);
    Client& resetPreviousResponseId();

    [[nodiscard]] Prompt prompt() const;
    Client& setPrompt(const Prompt& prompt);
    Client& resetPrompt();

    [[nodiscard]] QString promptCacheKey() const;
    Client& setPromptCacheKey(const QString& promptCacheKey);
    Client& resetPromptCacheKey();

    [[nodiscard]] Reasoning reasoning() const;
    Client& setReasoning(const Reasoning& reasoning);
    Client& resetReasoning();

    [[nodiscard]] QString safetyIdentifier() const;
    Client& setSafetyIdentifier(const QString& safetyIdentifier);
    Client& resetSafetyIdentifier();

    [[nodiscard]] QString serviceTier() const;
    Client& setServiceTier(const QString& serviceTier);
    Client& resetServiceTier();

    [[nodiscard]] bool isStored() const;
    Client& setStored(bool store);
    Client& resetStored();

    [[nodiscard]] double temperature() const;
    Client& setTemperature(double temperature);
    Client& resetTemperature();

    // [[nodiscard]] AiText text() const;
    // Client& setText(const AiText& text);
    // Client& resetText() {return  setText({}); }

    // [[nodiscard]] AiToolChoice toolChoice() const;
    // Client& setToolChoice(const AiToolChoice& toolChoice);
    // Client& resetToolChoice() {return  setToolChoice({}); }

    // [[nodiscard]] AiTools tools() const;
    // Client& setTools(const AiTools& tools);
    // Client& resetTools() { return setTools({}); }

    [[nodiscard]] int topLogprobs() const;
    Client& setTopLogprobs(int topLogprobs);
    Client& resetTopLogprobs();

    [[nodiscard]] double topP() const;
    Client& setTopP(double topP);
    Client& resetTopP();

    [[nodiscard]] Request::Truncation truncation() const;
    Client& setTruncation(Request::Truncation truncation);
    Client& setTruncation(const QString& truncation);
    Client& resetTruncation();

    [[nodiscard]] PopulateRequestBehaviour populateRequestBehaviour() const
    {
        return mPopulateRequestBehaviour;
    }
    void setPopulateRequestBehaviour(const PopulateRequestBehaviour& populateRequestBehaviour);
    void resetPopulateRequestBehaviour() { setPopulateRequestBehaviour(ClientThenRequest); }

signals:
    void populateRequestBehaviourChanged();

protected:
    Client(RequestData* data, QObject* parent = nullptr);

    // ai::Request prepareRequest(const ai::Request& request) const override
    // {
    //     Request r;
    //     qDebug() << r.toJson();
    //     r = ai::Client::prepareRequest(request);
    //     qDebug() << r.toJson();
    //     return r;
    // }
    virtual bool prepareRequest(Request* request);

    // [[nodiscard]] bool validateRequest(const ai::Request& request) const override{return va}
    using ai::Client::validateRequest;
    [[nodiscard]] virtual bool validateRequest(const Request& request) const;

    void initialize() override;

private:
    PopulateRequestBehaviour mPopulateRequestBehaviour = ClientAndRequest;

    Q_PROPERTY(PopulateRequestBehaviour populateRequestBehaviour READ populateRequestBehaviour WRITE
                   setPopulateRequestBehaviour RESET resetPopulateRequestBehaviour NOTIFY
                       populateRequestBehaviourChanged FINAL)
};

} // namespace ai

#endif // AI_RESPONSES_CLIENT_H
