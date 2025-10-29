#ifndef LIBAI_RESPONSESRESPONSE_H
#define LIBAI_RESPONSESRESPONSE_H

#include "response.h"
#include "responsesrequest.h"
#include "responsesresponseutils.h"

namespace ai {

class ResponsesClient;

class ResponsesResponse : public Response
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ResponsesResponse)
    QML_UNCREATABLE("ResponsesResponse is created internally")

    ResponsesRequest mRequest;

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

    [[nodiscard]] ResponsesClient* client() const;
    [[nodiscard]] ResponsesRequest request() const { return mRequest; }

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

    [[nodiscard]] ResponsesRequest::Model model() const { return mModel; }
    [[nodiscard]] QString modelAsString() const
    {
        return mModel != ResponsesRequest::Model_Custom
                   ? ResponsesRequest::modelToString(mModel)
                   : extra().value(QStringLiteral("model")).toString();
    }
    bool setModel(const QString& model)
    {
        if (modelAsString() == model)
            return false;
        if (ResponsesRequest::Model m = ResponsesRequest::stringToModel(model);
            m != ResponsesRequest::Model_Custom)
            return setModel(m);
        extra().insert(QStringLiteral("model"), model);
        return setModel(ResponsesRequest::Model_Custom);
    }
    bool setModel(ResponsesRequest::Model model)
    {
        if (mModel == model)
            return false;
        mModel = model;
        return true;
    }
    bool resetModel() { return setModel(ResponsesRequest::Model_Gpt41Mini); }

    [[nodiscard]] QList<OutputItem> output() const { return mOutput; }
    bool setOutput(const QList<OutputItem>& output)
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
        return setReasoning(
            Reasoning{reasoning ? Reasoning::Effort_Medium : Reasoning::Effort::Effort_Minimal});
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

    [[nodiscard]] ResponsesRequest::ServiceTier serviceTier() const { return mServiceTier; }
    [[nodiscard]] QString serviceTierAsString() const
    {
        return mServiceTier != ResponsesRequest::ServiceTier_Custom
                   ? ResponsesRequest::serviceTierToString(mServiceTier)
                   : extra().value(QStringLiteral("service_tier")).toString();
    }
    bool setServiceTier(const QString& serviceTier)
    {
        if (serviceTierAsString() == serviceTier)
            return false;
        if (ResponsesRequest::ServiceTier st = ResponsesRequest::stringToServiceTier(serviceTier);
            st != ResponsesRequest::ServiceTier_Custom)
            return setServiceTier(st);
        extra().insert(QStringLiteral("service_tier"), serviceTier);
        return setServiceTier(ResponsesRequest::ServiceTier_Custom);
    }
    bool setServiceTier(ResponsesRequest::ServiceTier serviceTier)
    {
        if (mServiceTier == serviceTier)
            return false;
        mServiceTier = serviceTier;
        if (mServiceTier != ResponsesRequest::ServiceTier_Custom)
            extra().remove(QStringLiteral("service_tier"));
        return true;
    }
    bool resetServiceTier() { return setServiceTier(ResponsesRequest::ServiceTier_Auto); }

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

    [[nodiscard]] ResponsesRequest::Truncation truncation() const { return mTruncation; }
    [[nodiscard]] QString truncationAsString() const
    {
        return mTruncation != ResponsesRequest::Truncation_Custom
                   ? ResponsesRequest::truncationToString(mTruncation)
                   : extra().value(QStringLiteral("truncation")).toString();
    }
    bool setTruncation(const QString& truncation)
    {
        if (truncationAsString() == truncation)
            return false;
        if (ResponsesRequest::Truncation t = ResponsesRequest::stringToTruncation(truncation);
            t != ResponsesRequest::Truncation_Custom)
            return setTruncation(t);
        extra().insert(QStringLiteral("truncation"), truncation);
        return setTruncation(ResponsesRequest::Truncation_Custom);
    }
    bool setTruncation(ResponsesRequest::Truncation truncation)
    {
        if (mTruncation == truncation)
            return false;
        mTruncation = truncation;
        if (mTruncation != ResponsesRequest::Truncation_Custom)
            extra().remove(QStringLiteral("truncation"));
        return true;
    }
    bool resetTruncation() { return setTruncation(ResponsesRequest::Truncation_Disabled); }

    [[nodiscard]] static Status stringToStatus(const QString& value)
    {
        return Status(StatusKV.key(value, Status_Custom));
    }
    [[nodiscard]] static QString statusToString(Status status) { return StatusKV.value(status); }

signals:
    void textGenerated(const QString& text, QPrivateSignal);
    void imageGenerated(const QImage& image, QPrivateSignal);

    void backgroundChanged(QPrivateSignal);
    void conversationChanged(QPrivateSignal);
    void inputChanged(QPrivateSignal);
    void reasoningChanged(QPrivateSignal);
    void metadataChanged(QPrivateSignal);
    void modelChanged(QPrivateSignal);
    void streamingChanged(QPrivateSignal);
    void streamOptionsChanged(QPrivateSignal);

protected:
    ResponsesResponse(const ResponsesRequest& request,
                      QNetworkReply* reply,
                      ResponsesClient* client);

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;

    bool mBackground = false;
    Conversation mConversation;
    int mCreatedAt = 0;
    Error mError;
    Input mInput;
    QString mInstructions;
    ResponsesRequest::Model mModel;
    QList<OutputItem> mOutput;
    int mMaxOutputTokens = 0;
    int mMaxToolCalls = 0;
    bool mParallelToolCalls = true;
    QString mPreviousResponseId;
    QString mPromptCacheKey;
    Reasoning mReasoning;
    QString mSafetyIdentifier;
    ResponsesRequest::ServiceTier mServiceTier;
    bool mStored = true;
    double mTemperature = 1.0;
    double mTopLogprobs = 0;
    double mTopP = 1.0;
    ResponsesRequest::Truncation mTruncation = ResponsesRequest::Truncation_Auto;

    QVariantMap mMetadata;
    StreamOptions mStreamOptions;
    bool mStreaming = false;
    Status mStatus = Status_Completed;

    static const QMap<int, QString> StatusKV;

    friend class ResponsesClient;
};

} // namespace ai

#endif // LIBAI_RESPONSESRESPONSE_H
