#ifndef AI_RESPONSES_REQUEST_H
#define AI_RESPONSES_REQUEST_H

#include "../request.h"

namespace ai::responses {

class Client;
class RequestData;

class Request : public ai::Request
{
    Q_GADGET

protected:
    RequestData* d();
    const RequestData* d() const;

public:
    enum Attribute {
        BackgroundAttribute = ai::Request::NumAttributes,
        ConversationAttribute,
        IncludeAttribute,
        InputAttribute,
        InstructionsAttribute,
        MaxOutputTokensAttribute,
        MaxToolCallsAttribute,
        ParallelToolCallsAttribute,
        PreviousResponseIdAttribute,
        PromptAttribute,
        PromptCacheKeyAttribute,
        ReasoningAttribute,
        SafetyIdentifierAttribute,
        ServiceTierAttribute,
        StoredAttribute,
        TemperatureAttribute,
        TextAttribute,
        ToolChoiseAttribute,
        ToolsAttribute,
        TopLogprobsAttribute,
        TopPAttribute,
        TruncationAttribute,
        NumAttributes
    };
    Q_ENUM(Attribute)

    enum Truncation { TruncationAuto, TruncationDisabled };

    Request();

    Request& operator=(const ai::Request& rhs);

    [[nodiscard]] bool background() const;
    Request& setBackground(bool background);
    Request& resetBackground();

    [[nodiscard]] Conversation conversation() const;
    Request& setConversation(const Conversation& conversation);
    Request& resetConversation();

    [[nodiscard]] IncludeList include() const;
    Request& setInclude(const IncludeList& include);
    Request& resetInclude();

    [[nodiscard]] Input input() const;
    Request& setInput(const Input& input);
    Request& resetInput();

    [[nodiscard]] QString instructions() const;
    Request& setInstructions(const QString& instructions);
    Request& resetInstructions();

    [[nodiscard]] int maxOutputTokens() const;
    Request& setMaxOutputTokens(int maxOutputTokens);
    Request& resetMaxOutputTokens();

    [[nodiscard]] int maxToolCalls() const;
    Request& setMaxToolCalls(int maxToolCalls);
    Request& resetMaxToolCalls();

    [[nodiscard]] bool parallelToolCalls() const;
    Request& setParallelToolCalls(bool parallelToolCalls);
    Request& resetParallelToolCalls();

    [[nodiscard]] QString previousResponseId() const;
    Request& setPreviousResponseId(const QString& previousResponseId);
    Request& resetPreviousResponseId();

    [[nodiscard]] Prompt prompt() const;
    Request& setPrompt(const Prompt& prompt);
    Request& resetPrompt();

    [[nodiscard]] QString promptCacheKey() const;
    Request& setPromptCacheKey(const QString& promptCacheKey);
    Request& resetPromptCacheKey();

    [[nodiscard]] Reasoning reasoning() const;
    Request& setReasoning(const Reasoning& reasoning);
    Request& resetReasoning();

    [[nodiscard]] QString safetyIdentifier() const;
    Request& setSafetyIdentifier(const QString& safetyIdetifier);
    Request& resetSafetyIdentifier();

    [[nodiscard]] QString serviceTier() const;
    Request& setServiceTier(const QString& serviceTier);
    Request& resetServiceTier();

    [[nodiscard]] bool isStored() const;
    Request& setStored(bool store);
    Request& resetStored();

    [[nodiscard]] double temperature() const;
    Request& setTemperature(double temperature);
    Request& resetTemperature();

    // [[nodiscard]] AiText text() const;
    // Request& setText(const AiText& text);
    // Request& resetText() {return  setText({}); }

    // [[nodiscard]] AiToolChoice toolChoice() const;
    // Request& setToolChoice(const AiToolChoice& toolChoice);
    // Request& resetToolChoice() {return  setToolChoice({}); }

    // [[nodiscard]] AiTools tools() const;
    // Request& setTools(const AiTools& tools);
    // Request& resetTools() { return setTools({}); }

    [[nodiscard]] int topLogprobs() const;
    Request& setTopLogprobs(int topLogprobs);
    Request& resetTopLogprobs();

    [[nodiscard]] double topP() const;
    Request& setTopP(double topP);
    Request& resetTopP();

    [[nodiscard]] Truncation truncation() const;
    Request& setTruncation(Truncation truncation);
    Request& setTruncation(const QString& truncation);
    Request& resetTruncation();

protected:
    Request(RequestData* data);

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;

    friend class Client;
};

class RequestData : public ai::RequestData
{
    bool mBackground = false;
    Conversation mConversation;
    IncludeList mInclude;
    Input mInput;
    QString mInstructions;
    int mMaxOutputTokens = 0;
    int mMaxToolCalls = 0;
    bool mParallelToolCalls = true;
    QString mPreviousResponseId;
    Prompt mPrompt;
    QString mPromptCacheKey;
    Reasoning mReasoning;
    QString mSafetyIdentifier;
    QString mServiceTier;
    bool mStored = true;
    double mTemperature = 1.0;
    int mTopLogprobs = 0;
    double mTopP = 1.0;
    Request::Truncation mTruncation = Request::Truncation::TruncationAuto;

public:

    [[nodiscard]] bool background() const { return mBackground; }
    bool setBackground(bool background,
                       Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::BackgroundAttribute, explicitHandling);
        if (mBackground == background)
            return false;
        mBackground = background;
        return true;
    }
    void resetBackground(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setBackground(false, explicitHandling);
    }

    [[nodiscard]] Conversation conversation() const { return mConversation; }
    bool setConversation(const Conversation& conversation,
                         Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ConversationAttribute, explicitHandling);
        if (mConversation == conversation)
            return false;
        mConversation.setId(conversation.id());
        return true;
    }
    void resetConversation(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setConversation({}, explicitHandling);
    }

    [[nodiscard]] IncludeList include() const { return mInclude; }
    bool setInclude(const IncludeList& include,
                    Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::IncludeAttribute, explicitHandling);
        if (mInclude == include)
            return false;
        mInclude = include;
        return true;
    }
    void resetInclude(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setInclude({}, explicitHandling);
    }

    [[nodiscard]] Input input() const { return mInput; }
    bool setInput(const Input& input,
                  Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::InputAttribute, explicitHandling);
        if (mInput == input)
            return false;
        mInput = input;
        return true;
    }
    void resetInput(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setInput({}, explicitHandling);
    }

    [[nodiscard]] QString instructions() const { return mInstructions; }
    bool setInstructions(const QString& instructions,
                         Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::InstructionsAttribute, explicitHandling);
        if (mInstructions == instructions)
            return false;
        mInstructions = instructions;
        return true;
    }
    void resetInstructions(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setInstructions({}, explicitHandling);
    }

    [[nodiscard]] int maxOutputTokens() const { return mMaxOutputTokens; }
    bool setMaxOutputTokens(int maxOutputTokens,
                            Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::MaxOutputTokensAttribute, explicitHandling);
        if (mMaxOutputTokens == maxOutputTokens)
            return false;
        mMaxOutputTokens = maxOutputTokens;
        return true;
    }
    void resetMaxOutputTokens(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setMaxOutputTokens(0, explicitHandling);
    }

    [[nodiscard]] int maxToolCalls() const { return mMaxToolCalls; }
    bool setMaxToolCalls(int maxToolCalls,
                         Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::MaxToolCallsAttribute, explicitHandling);
        if (mMaxToolCalls == maxToolCalls)
            return false;
        mMaxToolCalls = maxToolCalls;
        return true;
    }
    void resetMaxToolCalls(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setMaxToolCalls(0, explicitHandling);
    }

    [[nodiscard]] bool parallelToolCalls() const { return mParallelToolCalls; }
    bool setParallelToolCalls(bool parallelToolCalls,
                              Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ParallelToolCallsAttribute, explicitHandling);
        if (mParallelToolCalls == parallelToolCalls)
            return false;
        mParallelToolCalls = parallelToolCalls;
        return true;
    }
    void resetParallelToolCalls(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setParallelToolCalls(true, explicitHandling);
    }

    [[nodiscard]] QString previousResponseId() const { return mPreviousResponseId; }
    bool setPreviousResponseId(const QString& previousResponseId,
                               Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::PreviousResponseIdAttribute, explicitHandling);
        if (mPreviousResponseId == previousResponseId)
            return false;
        mPreviousResponseId = previousResponseId;
        return true;
    }
    void resetPreviousResponseId(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setPreviousResponseId({}, explicitHandling);
    }

    [[nodiscard]] Prompt prompt() const { return mPrompt; }
    bool setPrompt(const Prompt& prompt,
                   Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::PromptAttribute, explicitHandling);
        if (mPrompt == prompt)
            return false;
        mPrompt = prompt;
        return true;
    }
    void resetPrompt(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setPrompt({}, explicitHandling);
    }

    [[nodiscard]] QString promptCacheKey() const { return mPromptCacheKey; }
    bool setPromptCacheKey(const QString& promptCacheKey,
                           Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::PromptCacheKeyAttribute, explicitHandling);
        if (mPromptCacheKey == promptCacheKey)
            return false;
        mPromptCacheKey = promptCacheKey;
        return true;
    }
    void resetPromptCacheKey(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setPromptCacheKey({}, explicitHandling);
    }

    [[nodiscard]] Reasoning reasoning() const { return mReasoning; }
    bool setReasoning(const Reasoning& reasoning,
                      Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ReasoningAttribute, explicitHandling);
        if (mReasoning == reasoning)
            return false;
        mReasoning = reasoning;
        return true;
    }
    void resetReasoning(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setReasoning({}, explicitHandling);
    }

    [[nodiscard]] QString safetyIdentifier() const { return mSafetyIdentifier; }
    bool setSafetyIdentifier(const QString& safetyIdentifier,
                             Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::SafetyIdentifierAttribute, explicitHandling);
        if (mSafetyIdentifier == safetyIdentifier)
            return false;
        mSafetyIdentifier = safetyIdentifier;
        return true;
    }
    void resetSafetyIdentifier(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setSafetyIdentifier({}, explicitHandling);
    }

    [[nodiscard]] QString serviceTier() const { return mServiceTier; }
    bool setServiceTier(const QString& serviceTier,
                        Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ServiceTierAttribute, explicitHandling);
        if (mServiceTier == serviceTier)
            return false;
        mServiceTier = serviceTier;
        return true;
    }
    void resetServiceTier(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setServiceTier(QStringLiteral("auto"), explicitHandling);
    }

    [[nodiscard]] bool isStored() const { return mStored; }
    bool setStored(bool store, Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::StoredAttribute, explicitHandling);
        if (mStored == store)
            return false;
        mStored = store;
        return true;
    }
    void resetStored(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setStored(true, explicitHandling);
    }

    [[nodiscard]] double temperature() const { return mTemperature; }
    bool setTemperature(double temperature,
                        Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::TemperatureAttribute, explicitHandling);
        if (mTemperature == temperature)
            return false;
        mTemperature = temperature;
        return true;
    }
    void resetTemperature(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setTemperature(1.0, explicitHandling);
    }

    // [[nodiscard]] AiText text() const;
    // bool setText(const AiText& text,
    // Request::ExplicitHandling explicitHandling = Request::SetExplicit);
    // void resetText(Request::ExplicitHandling explicitHandling = Request::ClearExplicit) { setText({}); }

    // [[nodiscard]] AiToolChoice toolChoice() const;
    // bool setToolChoice(const AiToolChoice& toolChoice,
    // Request::ExplicitHandling explicitHandling = Request::SetExplicit);
    // void resetToolChoice(Request::ExplicitHandling explicitHandling = Request::ClearExplicit) { setToolChoice({}); }

    // [[nodiscard]] AiTools tools() const;
    // bool setTools(const AiTools& tools,
    // Request::ExplicitHandling explicitHandling = Request::SetExplicit);
    // void resetTools(Request::ExplicitHandling explicitHandling = Request::ClearExplicit) { setTools({}); }

    [[nodiscard]] int topLogprobs() const { return mTopLogprobs; }
    bool setTopLogprobs(int topLogprobs,
                        Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::TopLogprobsAttribute, explicitHandling);
        if (mTopLogprobs == topLogprobs)
            return false;
        mTopLogprobs = topLogprobs;
        return true;
    }
    void resetTopLogprobs(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setTopLogprobs(0, explicitHandling);
    }

    [[nodiscard]] double topP() const { return mTopP; }
    bool setTopP(double topP, Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::TopPAttribute, explicitHandling);
        if (mTopP == topP)
            return false;
        mTopP = topP;
        return true;
    }
    void resetTopP(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setTopP(1.0, explicitHandling);
    }

    [[nodiscard]] Request::Truncation truncation() const { return mTruncation; }
    bool setTruncation(Request::Truncation truncation,
                       Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::TruncationAttribute, explicitHandling);
        if (mTruncation == truncation)
            return false;
        mTruncation = truncation;
        return true;
    }
    bool setTruncation(const QString& truncation,
                       Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        return setTruncation(Request::TruncationAuto);
    }
    void resetTruncation(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setTruncation(Request::Truncation::TruncationDisabled, explicitHandling);
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;
};

} // namespace ai::responses

#endif // AI_RESPONSES_REQUEST_H
