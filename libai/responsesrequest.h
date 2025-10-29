#ifndef LIBAI_RESPONSESREQUEST_H
#define LIBAI_RESPONSESREQUEST_H

#include "request.h"
#include "responsesrequestutils.h"

namespace ai {

class ResponsesClient;

class ResponsesRequest : public Request
{
    Q_GADGET
    QML_VALUE_TYPE(responsesRequest)
    QML_CONSTRUCTIBLE_VALUE
    Q_PROPERTY(bool background READ background WRITE setBackground FINAL)
    // Q_PROPERTY(ai::Conversation READ conversation WRITE setConversation FINAL)
    // Q_PROPERTY(ai::Include include READ include WRITE setInclude FINAL)
    Q_PROPERTY(ai::Input input READ input WRITE setInput FINAL)
    Q_PROPERTY(QString instructions READ instructions WRITE setInstructions FINAL)
    Q_PROPERTY(QString previousResponseId READ previousResponseId WRITE setPreviousResponseId FINAL)
    // Q_PROPERTY(QString id READ id WRITE setId FINAL)
    // Q_PROPERTY(QString id READ id WRITE setId FINAL)
    // Q_PROPERTY(QString id READ id WRITE setId FINAL)

public:
    enum Attribute {
        BackgroundAttribute = ai::Request::NumAttributes,
        ConversationAttribute,
        IncludeAttribute,
        InputAttribute,
        InstructionsAttribute,
        MaxOutputTokensAttribute,
        MaxToolCallsAttribute,
        MetadataAttribute,
        ModelAttribute,
        ParallelToolCallsAttribute,
        PreviousResponseIdAttribute,
        PromptAttribute,
        PromptCacheKeyAttribute,
        ReasoningAttribute,
        SafetyIdentifierAttribute,
        ServiceTierAttribute,
        StoredAttribute,
        StreamingAttribute,
        StreamOptionsAttribute,
        TemperatureAttribute,
        TextAttribute,
        ToolChoiceAttribute,
        ToolsAttribute,
        TopLogprobsAttribute,
        TopPAttribute,
        TruncationAttribute,
        NumAttributes
    };
    Q_ENUM(Attribute)

    enum Model {
        Model_Gpt5,
        Model_Gpt5Nano,
        Model_Gpt5Mini,
        Model_Gpt5Pro,
        Model_Gpt41,
        Model_Gpt41Mini,
        Model_Custom
    };
    Q_ENUM(Model)

    enum ServiceTier {
        ServiceTier_Auto,
        ServiceTier_Default,
        ServiceTier_Flex,
        ServiceTier_Priority,
        ServiceTier_Custom
    };
    Q_ENUM(ServiceTier)

    enum Truncation { Truncation_Auto, Truncation_Disabled, Truncation_Custom };
    Q_ENUM(Truncation)

    ResponsesRequest(const QUrl& url = {})
        : ai::Request{url}
    {
        if (url.isEmpty() || !url.isValid())
            resetUrl();
        setTransferTimeout(60000 * 10);
    }

    ResponsesRequest& operator=(const ai::Request& rhs);

    bool resetUrl() override
    {
        QUrl u{"https://api.openai.com/v1/responses"};
        if (url() == u)
            return false;
        setUrl(u);
        return true;
    }

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

    [[nodiscard]] IncludeList include() const { return mInclude; }
    bool setInclude(const IncludeList& include)
    {
        if (mInclude == include)
            return false;
        mInclude = include;
        return true;
    }
    bool resetInclude() { return setInclude({}); }

    [[nodiscard]] Input input() const { return mInput; }
    bool setInput(const Input& input)
    {
        if (mInput == input)
            return false;
        mInput = input;
        return true;
    }
    Q_SLOT bool setInput(const QString& text)
    {
        mInput.setItems({InputMessage{text}});
        return true;
    }
    bool resetInput() { return setInput(Input{}); }

    [[nodiscard]] QString inputText() const;
    [[nodiscard]] QList<InputItem> inputItems() const;
    [[nodiscard]] InputMessage inputMessage(int index) const;
    [[nodiscard]] InputMessage inputItemReference(int index) const;

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
        maxOutputTokens = std::max(0, std::min(1024 * 1024, maxOutputTokens));
        if (mMaxOutputTokens == maxOutputTokens)
            return false;
        mMaxOutputTokens = maxOutputTokens;
        return true;
    }
    bool resetMaxOutputTokens() { return setMaxOutputTokens(0); }

    [[nodiscard]] int maxToolCalls() const { return mMaxToolCalls; }
    bool setMaxToolCalls(int maxToolCalls)
    {
        maxToolCalls = std::max(0, std::min(1024 * 1024, maxToolCalls));
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
        return true;
    }
    bool resetMetadata() { return setMetadata({}); }

    [[nodiscard]] QVariant metadata(const QString& key) const { return mMetadata.value(key); }
    bool putMetadata(const QString& key, const QVariant& value)
    {
        if (key.isEmpty())
            return false;
        mMetadata[key] = value;
        return true;
    }
    bool putMetadata(const QVariantMap& map)
    {
        for (auto it = map.constBegin(); it != map.constEnd(); ++it)
            if (!putMetadata(it.key(), it.value()))
                return false;
        return true;
    }
    QVariant takeMetadata(const QString& key) { return mMetadata.take(key); }

    [[nodiscard]] Model model() const { return mModel; }
    [[nodiscard]] QString modelAsString() const
    {
        return mModel != Model_Custom ? modelToString(mModel)
                                      : mExtra.value(QStringLiteral("model")).toString();
    }
    bool setModel(const QString& model)
    {
        if (modelAsString() == model)
            return false;
        if (const auto m = stringToModel(model); m != Model_Custom)
            return setModel(m);
        extra().insert(QStringLiteral("model"), model);
        return setModel(Model_Custom);
    }
    bool setModel(Model model)
    {
        if (mModel == model)
            return false;
        mModel = model;
        if (mModel != Model_Custom)
            extra().remove(QStringLiteral("model"));
        return true;
    }
    bool resetModel() { return setModel(Model_Gpt41Mini); }

    [[nodiscard]] bool parallelToolCalls() const { return mParallelToolCalls; }
    bool setParallelToolCalls(bool parallelToolCalls)
    {
        if (mParallelToolCalls == parallelToolCalls)
            return false;
        mParallelToolCalls = parallelToolCalls;
        return true;
    }
    bool resetParallelToolCalls() { return setParallelToolCalls(true); }

    [[nodiscard]] QString previousResponseId() const { return mPreviousResponseId; }
    bool setPreviousResponseId(const QString& previousResponseId)
    {
        if (mPreviousResponseId == previousResponseId)
            return false;
        mPreviousResponseId = previousResponseId;
        return true;
    }
    bool resetPreviousResponseId() { return setPreviousResponseId({}); }

    [[nodiscard]] Prompt prompt() const { return mPrompt; }
    bool setPrompt(const Prompt& prompt)
    {
        if (mPrompt == prompt)
            return false;
        mPrompt = prompt;
        return true;
    }
    bool resetPrompt() { return setPrompt({}); }

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
    bool resetReasoning() { return setReasoning({}); }

    [[nodiscard]] QString safetyIdentifier() const { return mSafetyIdentifier; }
    bool setSafetyIdentifier(const QString& safetyIdetifier)
    {
        if (mSafetyIdentifier == safetyIdetifier)
            return false;
        mSafetyIdentifier = safetyIdetifier;
        return true;
    }
    bool resetSafetyIdentifier() { return setSafetyIdentifier({}); }

    [[nodiscard]] ServiceTier serviceTier() const { return mServiceTier; }
    [[nodiscard]] QString serviceTierAsString() const
    {
        return mServiceTier != ServiceTier_Custom
                   ? serviceTierToString(mServiceTier)
                   : mExtra.value(QStringLiteral("service_tier")).toString();
    }
    bool setServiceTier(const QString& serviceTier)
    {
        if (serviceTierAsString() == serviceTier)
            return false;
        if (const auto t = stringToServiceTier(serviceTier); t != ServiceTier_Custom)
            return setServiceTier(t);
        extra().insert(QStringLiteral("service_tier"), serviceTier);
        return setServiceTier(ServiceTier_Custom);
    }
    bool setServiceTier(ServiceTier serviceTier)
    {
        if (mServiceTier == serviceTier)
            return false;
        mServiceTier = serviceTier;
        if (mServiceTier != ServiceTier_Custom)
            extra().remove(QStringLiteral("service_tier"));
        return true;
    }
    bool resetServiceTier() { return setServiceTier(ServiceTier_Auto); }

    [[nodiscard]] bool isStored() const { return mStore; }
    bool setStored(bool store)
    {
        if (mStore == store)
            return false;
        mStore = store;
        return true;
    }
    bool resetStored() { return setStored(true); }

    [[nodiscard]] bool isStreaming() const { return mStream; }
    bool setStreaming(bool streaming)
    {
        if (mStream == streaming)
            return false;
        mStream = streaming;
        setRawHeader("Accept", mStream ? "text/event-stream" : "application/json");
        setTransferTimeout(mStream ? 0 : 60000);
        return true;
    }
    bool resetStreaming() { return setStreaming(false); }

    [[nodiscard]] StreamOptions streamOptions() const { return mStreamOptions; }
    bool setStreamOptions(const StreamOptions& streamOptions)
    {
        if (mStreamOptions == streamOptions)
            return false;
        mStreamOptions = streamOptions;
        return true;
    }
    bool resetStreamOptions() { return setStreamOptions({}); }

    [[nodiscard]] double temperature() const { return mTemperature; }
    bool setTemperature(double temperature)
    {
        temperature = std::max(0.0, std::min(2.0, temperature));
        if (mTemperature == temperature)
            return false;
        mTemperature = temperature;
        return true;
    }
    bool resetTemperature() { return setTemperature(1.0); }

    // [[nodiscard]] AiText text() const;
    // bool setText(const AiText& text);
    // bool resetText() {return  setText({}); }

    // [[nodiscard]] AiToolChoice toolChoice() const;
    // bool setToolChoice(const AiToolChoice& toolChoice);
    // bool resetToolChoice() {return  setToolChoice({}); }

    [[nodiscard]] QList<Tool> tools() const { return mTools; }
    bool setTools(const QList<Tool>& tools)
    {
        if (mTools == tools)
            return false;
        mTools = tools;
        return true;
    }
    bool resetTools() { return setTools({}); }

    [[nodiscard]] int topLogprobs() const { return mTopLogprobs; }
    bool setTopLogprobs(int topLogprobs)
    {
        topLogprobs = std::max(0, std::min(20, topLogprobs));
        if (mTopLogprobs == topLogprobs)
            return false;
        mTopLogprobs = topLogprobs;
        return true;
    }
    bool resetTopLogprobs() { return setTopLogprobs(0); }

    [[nodiscard]] double topP() const { return mTopP; }
    bool setTopP(double topP)
    {
        topP = std::max(0.0, std::min(1.0, topP));
        if (mTopP == topP)
            return false;
        mTopP = topP;
        return true;
    }
    bool resetTopP() { return setTopP(1.0); }

    [[nodiscard]] Truncation truncation() const { return mTruncation; }
    [[nodiscard]] QString truncationAsString() const
    {
        return mTruncation != Truncation_Custom
                   ? truncationToString(mTruncation)
                   : mExtra.value(QStringLiteral("truncation")).toString();
    }
    bool setTruncation(const QString& truncation)
    {
        if (truncationAsString() == truncation)
            return false;
        if (const auto t = stringToTruncation(truncation); t != Truncation_Custom)
            return setTruncation(t);
        extra().insert(QStringLiteral("truncation"), truncation);
        return setTruncation(Truncation_Custom);
    }
    bool setTruncation(Truncation truncation)
    {
        if (mTruncation == truncation)
            return false;
        mTruncation = truncation;
        if (mTruncation != Truncation_Custom)
            extra().remove(QStringLiteral("truncation"));
        return true;
    }
    bool resetTruncation() { return setTruncation(Truncation_Disabled); }

    [[nodiscard]] static Model stringToModel(const QString& value)
    {
        return Model(ModelKV.key(value, Model_Custom));
    }
    [[nodiscard]] static QString modelToString(Model model) { return ModelKV.value(model); }

    [[nodiscard]] static ServiceTier stringToServiceTier(const QString& value)
    {
        return ServiceTier(ServiceTierKV.key(value, ServiceTier_Custom));
    }
    [[nodiscard]] static QString serviceTierToString(ServiceTier serviceTier)
    {
        return ServiceTierKV.value(serviceTier);
    }

    [[nodiscard]] static Truncation stringToTruncation(const QString& value)
    {
        return Truncation(TruncationKV.key(value, Truncation_Custom));
    }
    [[nodiscard]] static QString truncationToString(Truncation truncation)
    {
        return TruncationKV.value(truncation);
    }

    [[nodiscard]] bool isReasoningModel() const { return isReasoningModel(mModel); }
    [[nodiscard]] static bool isReasoningModel(Model model)
    {
        switch (model) {
        case Model_Gpt5:
        case Model_Gpt5Mini:
        case Model_Gpt5Nano:
        case Model_Gpt5Pro:
            return true;
        default:
            return false;
        }
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;

    static const QMap<int, QString> ModelKV;
    static const QMap<int, QString> ServiceTierKV;
    static const QMap<int, QString> TruncationKV;

    friend class ResponsesClient;

    QVariantMap mMetadata;
    QString mId;
    QString mInstructions;
    QString mPreviousResponseId;
    QString mPromptCacheKey;
    QString mSafetyIdentifier;
    QByteArray mApiKey;
    Conversation mConversation;
    IncludeList mInclude;
    Input mInput;
    StreamOptions mStreamOptions;
    Prompt mPrompt;
    Reasoning mReasoning;
    double mTemperature = 1.0;
    double mTopP = 1.0;
    int mMaxOutputTokens = 0;
    int mMaxToolCalls = 0;
    int mTopLogprobs = 0;
    Model mModel = Model_Gpt41Mini;
    ServiceTier mServiceTier = ServiceTier_Auto;
    Truncation mTruncation = Truncation_Disabled;
    bool mBackground = false;
    bool mParallelToolCalls = true;
    bool mStore = true;
    bool mStream = false;
    QList<Tool> mTools;
};

} // namespace ai

#endif // LIBAI_RESPONSESREQUEST_H
