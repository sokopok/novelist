#ifndef AI_RESPONSES_RESPONSE_H
#define AI_RESPONSES_RESPONSE_H

#include "../response.h"
#include "request.h"

namespace ai::responses {

class Client;

class Response : public ai::Response
{
    Q_OBJECT

    Request mRequest;

public:
    enum Attribute {
        BackgroundAttribute = ai::Response::NumAttributes,
        ConversationAttribute,
        CreatedAtAttribute,
        ErrorAttribute,
        IncompleteDetailsAttribute,
        InstructionsAttribute,
        MaxOutputTokensAttribute,
        MaxToolCallsAttribute,
        MetadataAttribute,
        ModelAttribute,
        ObjectAttribute,
        OutputAttribute,
        OutputTextAttribute,
        ParallelToolCallsAttribute,
        PreviousResponseIdAttribute,
        PromptAttribute,
        PromptCacheKeyAttribute,
        ReasoningAttribute,
        SafetyIdentifierAttribute,
        ServiceTierAttribute,
        StatusAttribute,
        TemperatureAttribute,
        TextAttribute,
        ToolChoiceAttribute,
        ToolsAttribute,
        TopLogprobsAttribute,
        TopPAttribute,
        TruncationAttribute,
        UsageAttribute,
        NumAttributes
    };
    Q_ENUM(Attribute)

    enum Status {
        Status_Completed,
        Status_Failed,
        Status_InProgress,
        Status_Cancelled,
        Status_Queued,
        Status_Incomplete,
        Status_Custom
    };
    Q_ENUM(Status)

    [[nodiscard]] Client* client() const;
    [[nodiscard]] Request request() const { return mRequest; }

    [[nodiscard]] bool background() const { return mBackground; }
    bool setBackground(bool background)
    {
        if (mBackground == background)
            return false;
        mBackground = background;
        return true;
    }
    bool resetBackground() { return setBackground(false); }

    [[nodiscard]] Conversation conversation() const { return mConversation; }
    bool setConversation(const Conversation& conversation)
    {
        if (mConversation == conversation)
            return false;
        mConversation = conversation;
        return true;
    }
    bool resetConversation() { return setConversation({}); }

    [[nodiscard]] int createdAt() const { return mCreatedAt; }
    bool setCreatedAt(int createdAt)
    {
        if (mCreatedAt == createdAt)
            return false;
        mCreatedAt = createdAt;
        return true;
    }
    bool resetCreatedAt() { return setCreatedAt(0); }

    [[nodiscard]] Error error() const { return mError; }
    bool setError(const Error& error)
    {
        if (mError == error)
            return false;
        mError = error;
        return true;
    }
    bool resetError() { return setError({}); }

    // [[nodiscard]] IncompleteDetails incompleteDetails() const { return mIncompleteDetails; }
    // bool setIncompleteDetails(const IncompleteDetails& incompleteDetails)
    // {
    //     if (mIncompleteDetails== incompleteDetails)
    //         return false;
    //     mIncompleteDetails= incompleteDetails;
    //     return true;
    // }
    // bool resetIncompleteDetails() { return setIncompleteDetails({}); }

    [[nodiscard]] QString instructions() const { return mInstructions; }
    bool setInstructions(const QString& instructions)
    {
        if (mInstructions == instructions)
            return false;
        mInstructions = instructions;
        return true;
    }
    bool resetInstructions() { return setInstructions({}); }

    [[nodiscard]] int maxOutputTokens() const { return mMaxOutputTokens; }
    bool setMaxOutputTokens(int maxOutputTokens)
    {
        if (mMaxOutputTokens == maxOutputTokens)
            return false;
        mMaxOutputTokens = maxOutputTokens;
        return true;
    }
    bool resetMaxOutputTokens() { return setMaxOutputTokens(0); }

    [[nodiscard]] int maxToolCalls() const { return mMaxToolCalls; }
    bool setMaxToolCalls(int maxToolCalls)
    {
        if (mMaxToolCalls == maxToolCalls)
            return false;
        mMaxToolCalls = maxToolCalls;
        return true;
    }
    bool resetMaxToolCalls() { return setMaxToolCalls(0); }

    [[nodiscard]] QVariantMap metadata() const { return mMetadata; }
    bool setMetadata(const QVariantMap& metadata)
    {
        if (mMetadata == metadata)
            return false;
        mMetadata = metadata;
        emit metadataChanged(QPrivateSignal{});
        return true;
    }
    bool resetMetadata() { return setMetadata({}); }

    [[nodiscard]] QVariant metadata(const QString& key) const { return mMetadata.value(key); }
    bool putMetadata(const QString& key, const QVariant& value)
    {
        if (key.isEmpty())
            return false;
        mMetadata[key] = value;
        emit metadataChanged(QPrivateSignal{});
        return true;
    }
    QVariant takeMetadata(const QString& key)
    {
        if (mMetadata.contains(key)) {
            const auto result = mMetadata.take(key);
            emit metadataChanged(QPrivateSignal{});
            return result;
        }
        return {};
    }

    [[nodiscard]] Request::Model model() const { return mModel; }
    [[nodiscard]] QString modelAsString() const
    {
        return mModel != Request::Model_Custom ? Request::modelToString(mModel)
                                               : extra().value(QStringLiteral("model")).toString();
    }
    bool setModel(const QString& model)
    {
        if (modelAsString() == model)
            return false;
        if (Request::Model m = Request::stringToModel(model); m != Request::Model_Custom)
            return setModel(m);
        extra().insert(QStringLiteral("model"), model);
        return setModel(Request::Model_Custom);
    }
    bool setModel(Request::Model model)
    {
        if (mModel == model)
            return false;
        mModel = model;
        return true;
    }
    bool resetModel() { return setModel(Request::Model_Gpt41Mini); }

    [[nodiscard]] Output output() const { return mOutput; }
    bool setOutput(const Output& output)
    {
        if (mOutput == output)
            return false;
        mOutput = output;
        return true;
    }
    bool resetOutput() { return setOutput({}); }

    [[nodiscard]] bool parallelToolCalls() const { return mParallelToolCalls; }
    bool setParallelToolCalls(bool parallelToolCalls)
    {
        if (mParallelToolCalls == parallelToolCalls)
            return false;
        mParallelToolCalls = parallelToolCalls;
        return true;
    }
    bool resetParallelToolCalls();

    [[nodiscard]] QString previousResponseId() const { return mPreviousResponseId; }
    bool setPreviousResponseId(const QString& previousResponseId)
    {
        if (mPreviousResponseId == previousResponseId)
            return false;
        mPreviousResponseId = previousResponseId;
        return true;
    }
    bool resetPreviousResponseId() { return setPreviousResponseId({}); }

    // [[nodiscard]] AiPrompt prompt() const;
    // bool setPrompt(const AiPrompt& prompt);
    // bool resetPrompt() { return setPrompt({}); }

    [[nodiscard]] QString promptCacheKey() const { return mPromptCacheKey; }
    bool setPromptCacheKey(const QString& promptCacheKey)
    {
        if (mPromptCacheKey == promptCacheKey)
            return false;
        mPromptCacheKey = promptCacheKey;
        return true;
    }
    bool resetPromptCacheKey() { return setPromptCacheKey({}); }

    [[nodiscard]] Reasoning reasoning() const { return mReasoning; }
    bool setReasoning(const Reasoning& reasoning)
    {
        if (mReasoning == reasoning)
            return false;
        mReasoning = reasoning;
        return true;
    }
    bool setReasoning(bool reasoning)
    {
        if (reasoning ? mReasoning.effort() != Reasoning::Effort::None
                      : mReasoning.effort() == Reasoning::Effort::None)
            return false;

        return setReasoning(
            Reasoning{reasoning ? Reasoning::Effort::Medium : Reasoning::Effort::None});
    }
    bool resetReasoning() { return setReasoning({}); }

    [[nodiscard]] QString safetyIdentifier() const { return mSafetyIdentifier; }
    bool setSafetyIdentifier(const QString& safetyIdentifier)
    {
        if (mSafetyIdentifier == safetyIdentifier)
            return false;
        mSafetyIdentifier = safetyIdentifier;
        return true;
    }
    bool resetSafetyIdentifier() { return setSafetyIdentifier({}); }

    [[nodiscard]] Request::ServiceTier serviceTier() const { return mServiceTier; }
    [[nodiscard]] QString serviceTierAsString() const
    {
        return mServiceTier != Request::ServiceTier_Custom
                   ? Request::serviceTierToString(mServiceTier)
                   : extra().value(QStringLiteral("service_tier")).toString();
    }
    bool setServiceTier(const QString& serviceTier)
    {
        if (serviceTierAsString() == serviceTier)
            return false;
        if (Request::ServiceTier st = Request::stringToServiceTier(serviceTier);
            st != Request::ServiceTier_Custom)
            return setServiceTier(st);
        extra().insert(QStringLiteral("service_tier"), serviceTier);
        return setServiceTier(Request::ServiceTier_Custom);
    }
    bool setServiceTier(Request::ServiceTier serviceTier)
    {
        if (mServiceTier == serviceTier)
            return false;
        mServiceTier = serviceTier;
        if (mServiceTier != Request::ServiceTier_Custom)
            extra().remove(QStringLiteral("service_tier"));
        return true;
    }
    bool resetServiceTier() { return setServiceTier(Request::ServiceTier_Auto); }

    [[nodiscard]] Status status() const { return mStatus; }
    [[nodiscard]] QString statusAsString() const
    {
        return mStatus != Status_Custom ? statusToString(mStatus)
                                        : extra().value(QStringLiteral("status")).toString();
    }
    bool setStatus(const QString& status)
    {
        if (statusAsString() == status)
            return false;
        if (Status s = stringToStatus(status); s != Status_Custom)
            return setStatus(s);
        extra().insert(QStringLiteral("status"), status);
        return setStatus(Status_Custom);
    }
    bool setStatus(Status status)
    {
        if (mStatus == status)
            return false;
        mStatus = status;
        if (mStatus != Status_Custom)
            extra().remove(QStringLiteral("status"));
        return true;
    }
    bool resetStatus() { return setStatus(Status_Completed); }

    [[nodiscard]] bool isStored() const { return mStored; }
    bool setStored(bool store)
    {
        if (mStored == store)
            return false;
        mStored = store;
        return true;
    }
    bool resetStored() { return setStored(true); }

    [[nodiscard]] bool isStreaming() const { return mStreaming; }
    bool setStreaming(bool streaming)
    {
        if (mStreaming == streaming)
            return false;
        mStreaming = streaming;
        emit streamingChanged(QPrivateSignal{});
        return true;
    }
    bool resetStreaming() { return setStreaming(false); }

    [[nodiscard]] StreamOptions streamOptions() const { return mStreamOptions; }
    bool setStreamOptions(const StreamOptions& streamOptions)
    {
        if (mStreamOptions == streamOptions)
            return false;
        mStreamOptions = streamOptions;
        emit streamOptionsChanged(QPrivateSignal{});
        return true;
    }
    bool resetStreamOptions() { return setStreamOptions({}); }

    [[nodiscard]] double temperature() const { return mTemperature; }
    bool setTemperature(double temperature)
    {
        if (mTemperature == temperature)
            return false;
        mTemperature = temperature;
        return true;
    }
    bool resetTemperature() { return setTemperature(1.0); }

    // [[nodiscard]] AiText text() const;
    // bool setText(const AiText& text);
    // bool resetText() { return setText({}); }

    // [[nodiscard]] AiToolChoice toolChoice() const;
    // bool setToolChoice(const AiToolChoice& toolChoice);
    // bool resetToolChoice() { return setToolChoice({}); }

    // [[nodiscard]] AiTools tools() const;
    // bool setTools(const AiTools& tools);
    // bool resetTools() {return  setTools({}); }

    [[nodiscard]] int topLogprobs() const { return mTopLogprobs; }
    bool setTopLogprobs(int topLogprobs)
    {
        if (mTopLogprobs == topLogprobs)
            return false;
        mTopLogprobs = topLogprobs;
        return true;
    }
    bool resetTopLogprobs() { return setTopLogprobs(0); }

    [[nodiscard]] double topP() const { return mTopP; }
    bool setTopP(double topP)
    {
        if (mTopP == topP)
            return false;
        mTopP = topP;
        return true;
    }
    bool resetTopP() { return setTopP(1.0); }

    [[nodiscard]] Request::Truncation truncation() const { return mTruncation; }
    [[nodiscard]] QString truncationAsString() const
    {
        return mTruncation != Request::Truncation_Custom
                   ? Request::truncationToString(mTruncation)
                   : extra().value(QStringLiteral("truncation")).toString();
    }
    bool setTruncation(const QString& truncation)
    {
        if (truncationAsString() == truncation)
            return false;
        if (Request::Truncation t = Request::stringToTruncation(truncation);
            t != Request::Truncation_Custom)
            return setTruncation(t);
        extra().insert(QStringLiteral("truncation"), truncation);
        return setTruncation(Request::Truncation_Custom);
    }
    bool setTruncation(Request::Truncation truncation)
    {
        if (mTruncation == truncation)
            return false;
        mTruncation = truncation;
        if (mTruncation != Request::Truncation_Custom)
            extra().remove(QStringLiteral("truncation"));
        return true;
    }
    bool resetTruncation() { return setTruncation(Request::Truncation_Disabled); }

    [[nodiscard]] static Status stringToStatus(const QString& value)
    {
        return Status(StatusKV.key(value, Status_Custom));
    }
    [[nodiscard]] static QString statusToString(Status status) { return StatusKV.value(status); }

signals:
    void backgroundChanged(QPrivateSignal);
    void conversationChanged(QPrivateSignal);
    void inputChanged(QPrivateSignal);
    void reasoningChanged(QPrivateSignal);
    void metadataChanged(QPrivateSignal);
    void modelChanged(QPrivateSignal);
    void streamingChanged(QPrivateSignal);
    void streamOptionsChanged(QPrivateSignal);

protected:
    Response(const Request& request, QNetworkReply* reply, Client* client);

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;

    bool mBackground = false;
    Conversation mConversation;
    int mCreatedAt = 0;
    Error mError;
    Input mInput;
    QString mInstructions;
    Request::Model mModel;
    Output mOutput;
    int mMaxOutputTokens = 0;
    int mMaxToolCalls = 0;
    bool mParallelToolCalls = true;
    QString mPreviousResponseId;
    QString mPromptCacheKey;
    Reasoning mReasoning;
    QString mSafetyIdentifier;
    Request::ServiceTier mServiceTier;
    bool mStored = true;
    double mTemperature = 1.0;
    double mTopLogprobs = 0;
    double mTopP = 1.0;
    Request::Truncation mTruncation = Request::Truncation_Auto;

    QVariantMap mMetadata;
    StreamOptions mStreamOptions;
    bool mStreaming = false;
    Status mStatus = Status_Completed;

    static const QMap<int, QString> StatusKV;

    friend class Client;
};

} // namespace ai::responses

#endif // AI_RESPONSES_RESPONSE_H
