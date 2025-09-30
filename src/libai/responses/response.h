#ifndef AI_RESPONSES_RESPONSE_H
#define AI_RESPONSES_RESPONSE_H

#include "../response.h"
#include "request.h"

namespace ai::responses {

class Client;

class ResponseData : public ai::ResponseData
{
public:
    enum Truncation { TruncationAuto, TruncationDisabled };

protected:
    bool mBackground = false;
    Conversation mConversation;
    Input mInput;
    QString mInstructions;
    Output mOutput;
    int mMaxOutputTokens = 0;
    int mMaxToolCalls = 0;
    bool mParallelToolCalls = true;
    QString mPreviousResponseId;
    QString mPromptCacheKey;
    Reasoning mReasoning;
    QString mSafetyIdetifier;
    QString mServiceTier;
    bool mStored = true;
    double mTemperature = 1.0;
    double mTopLogprobs = 0;
    double mTopP = 1.0;
    Truncation mTrucation = TruncationAuto;

    inline static QMap<Truncation, QString> TruncationKV = {{TruncationAuto, "auto"},
                                                            {TruncationDisabled, "disabled"}};

public:
    static Truncation toTruncation(const QString& truncation)
    {
        return Truncation(TruncationKV.key(truncation, TruncationAuto));
    }
    static Truncation toTruncation(int truncation)
    {
        return truncation == 1 ? TruncationDisabled : TruncationAuto;
    }
    static QString toString(Truncation truncation) { return TruncationKV.value(truncation); }

    /** background
        boolean
        Optional
        Defaults to false
        Whether to run the model response in the background. Learn more.
    */
    [[nodiscard]] bool background() const { return mBackground; }
    bool setBackground(bool background)
    {
        if (mBackground == background)
            return false;
        mBackground = background;
        return true;
    }
    void resetBackground() { setBackground(false); }

    /** conversation
        string or object
        Optional
        Defaults to null
        The conversation that this response belongs to. Items from this conversation are prepended to input_items for this response request. Input items and output items from this response are automatically added to this conversation after this response completes.
    */
    [[nodiscard]] Conversation conversation() const { return mConversation; }
    bool setConversation(const Conversation& conversation)
    {
        if (mConversation == conversation)
            return false;
        mConversation = conversation;
        return true;
    }
    void resetConversation() { setConversation({}); }

    /** include
        array
        Optional
        Specify additional output data to include in the model response. Currently supported values are:
            web_search_call.action.sources: Include the sources of the web search tool call.
            code_interpreter_call.outputs: Includes the outputs of python code execution in code interpreter tool call items.
            computer_call_output.output.image_url: Include image urls from the computer call output.
            file_search_call.results: Include the search results of the file search tool call.
            message.input_image.image_url: Include image urls from the input message.
            message.output_text.logprobs: Include logprobs with assistant messages.
            reasoning.encrypted_content: Includes an encrypted version of reasoning tokens in reasoning item outputs. This enables reasoning items to be used in multi-turn conversations when using the Responses API statelessly (like when the store parameter is set to false, or when an organization is enrolled in the zero data retention program).
    */
    // [[nodiscard]] AiIncludeList include() const;
    // bool setInclude(const AiIncludeList& include);
    // void resetInclude() { setInclude({}); }

    /** input
        string or array
        Optional
        Text, image, or file inputs to the model, used to generate a response.
        Learn more:
            Text inputs and outputs
            Image inputs
            File inputs
            Conversation state
            Function calling
    */
    [[nodiscard]] Input input() const { return mInput; }
    bool setInput(const Input& input)
    {
        if (mInput == input)
            return false;
        mInput = input;
        return true;
    }
    void resetInput() { setInput({}); }

    /** instructions
        string
        Optional
        A system (or developer) message inserted into the model's context.
        When using along with previous_response_id, the instructions from a previous response will not be carried over to the next response. This makes it simple to swap out system (or developer) messages in new responses.
    */
    [[nodiscard]] QString instructions() const { return mInstructions; }
    bool setInstructions(const QString& instructions)
    {
        if (mInstructions == instructions)
            return false;
        mInstructions = instructions;
        return true;
    }
    void resetInstructions() { setInstructions({}); }

    /** max_output_tokens
        integer
        Optional
        An upper bound for the number of tokens that can be generated for a response, including visible output tokens and reasoning tokens.
    */
    [[nodiscard]] int maxOutputTokens() const { return mMaxOutputTokens; }
    bool setMaxOutputTokens(int maxOutputTokens)
    {
        if (mMaxOutputTokens == maxOutputTokens)
            return false;
        mMaxOutputTokens = maxOutputTokens;
        return true;
    }
    void resetMaxOutputTokens() { setMaxOutputTokens(-1); }

    /** max_tool_calls
        integer
        Optional
        The maximum number of total calls to built-in tools that can be processed in a response. This maximum number applies across all built-in tool calls, not per individual tool. Any further attempts to call a tool by the model will be ignored.
    */
    [[nodiscard]] int maxToolCalls() const { return mMaxToolCalls; }
    bool setMaxToolCalls(int maxToolCalls)
    {
        if (mMaxToolCalls == maxToolCalls)
            return false;
        mMaxToolCalls = maxToolCalls;
        return true;
    }
    void resetMaxToolCalls() { setMaxToolCalls(-1); }

    /** output
        array
        An array of content items generated by the model.
            The length and order of items in the output array is dependent on the model's response.
            Rather than accessing the first item in the output array and assuming it's an assistant message with the content generated by the model, you might consider using the output_text property where supported in SDKs.
    **/
    [[nodiscard]] Output output() const { return mOutput; }
    bool setOutput(const Output& output)
    {
        if (mOutput == output)
            return false;
        mOutput = output;
        return true;
    }
    void resetOutput() { setOutput({}); }

    /** parallel_tool_calls
        boolean
        Optional
        Defaults to true
        Whether to allow the model to run tool calls in parallel.
    */
    [[nodiscard]] bool parallelToolCalls() const { return mParallelToolCalls; }
    bool setParallelToolCalls(bool parallelToolCalls)
    {
        if (mParallelToolCalls == parallelToolCalls)
            return false;
        mParallelToolCalls = parallelToolCalls;
        return true;
    }
    void resetParallelToolCalls();

    /** previous_response_id
        string
        Optional
        The unique ID of the previous response to the model. Use this to create multi-turn conversations. Learn more about conversation state. Cannot be used in conjunction with conversation.
    */
    [[nodiscard]] QString previousResponseId() const { return mPreviousResponseId; }
    bool setPreviousResponseId(const QString& previousResponseId)
    {
        if (mPreviousResponseId == previousResponseId)
            return false;
        mPreviousResponseId = previousResponseId;
        return true;
    }
    void resetPreviousResponseId() { setPreviousResponseId({}); }

    /** prompt
        object
        Optional
        Reference to a prompt template and its variables. Learn more.
    */
    // [[nodiscard]] AiPrompt prompt() const;
    // bool setPrompt(const AiPrompt& prompt);
    // void resetPrompt() { setPrompt({}); }

    /** prompt_cache_key
        string
        Optional
        Used by OpenAI to cache responses for similar requests to optimize your cache hit rates. Replaces the user field. Learn more.
    */
    [[nodiscard]] QString promptCacheKey() const { return mPromptCacheKey; }
    bool setPromptCacheKey(const QString& promptCacheKey)
    {
        if (mPromptCacheKey == promptCacheKey)
            return false;
        mPromptCacheKey = promptCacheKey;
        return true;
    }
    void resetPromptCacheKey() { setPromptCacheKey({}); }

    /** reasoning
        object
        Optional
        gpt-5 and o-series models only
        Configuration options for reasoning models.
    */
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

    /** safety_identifier
        string
        Optional
        A stable identifier used to help detect users of your application that may be violating OpenAI's usage policies. The IDs should be a string that uniquely identifies each user. We recommend hashing their username or email address, in order to avoid sending us any identifying information. Learn more.
    */
    [[nodiscard]] QString safetyIdentifier() const { return mSafetyIdetifier; }
    bool setSafetyIdetifier(const QString& safetyIdetifier)
    {
        if (mSafetyIdetifier == safetyIdetifier)
            return false;
        mSafetyIdetifier = safetyIdetifier;
        return true;
    }
    void resetSafetyIdetifier() { setSafetyIdetifier({}); }

    /** service_tier
        string
        Optional
        Defaults to auto
        Specifies the processing type used for serving the request.
            If set to 'auto', then the request will be processed with the service tier configured in the Project settings. Unless otherwise configured, the Project will use 'default'.
            If set to 'default', then the request will be processed with the standard pricing and performance for the selected model.
            If set to 'flex' or 'priority', then the request will be processed with the corresponding service tier.
            When not set, the default behavior is 'auto'.
        When the service_tier parameter is set, the response body will include the service_tier value based on the processing mode actually used to serve the request. This response value may be different from the value set in the parameter.
    */
    [[nodiscard]] QString serviceTier() const { return mServiceTier; }
    bool setServiceTier(const QString& serviceTier)
    {
        if (mServiceTier == serviceTier)
            return false;
        mServiceTier = serviceTier;
        return true;
    }
    void resetServiceTier() { setServiceTier(QStringLiteral("auto")); }

    /** isStored
        boolean
        Optional
        Defaults to true
        Whether to isStored the generated model response for later retrieval via API.
    */
    [[nodiscard]] bool isStored() const { return mStored; }
    bool setStored(bool store)
    {
        if (mStored == store)
            return false;
        mStored = store;
        return true;
    }
    void resetStored();

    /** temperature
        number
        Optional
        Defaults to 1
        What sampling temperature to use, between 0 and 2. Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic. We generally recommend altering this or top_p but not both.
    */
    [[nodiscard]] double temperature() const { return mTemperature; }
    bool setTemperature(double temperature)
    {
        if (mTemperature == temperature)
            return false;
        mTemperature = temperature;
        return true;
    }
    void resetTemperature() { setTemperature(1.0); }

    /** text
        object
        Optional
        Configuration options for a text response from the model. Can be plain text or structured JSON data. Learn more:
            Text inputs and outputs
            Structured Outputs
        format
            object
            Optional
            An object specifying the format that the model must output.
            Configuring { "type": "json_schema" } enables Structured Outputs, which ensures the model will match your supplied JSON schema. Learn more in the Structured Outputs guide.
            The default format is { "type": "text" } with no additional options.
            Not recommended for gpt-4o and newer models:
            Setting to { "type": "json_object" } enables the older JSON mode, which ensures the message the model generates is valid JSON. Using json_schema is preferred for models that support it.
            Text
                object
                Default response format. Used to generate text responses.
            JSON schema
                object
                JSON Schema response format. Used to generate structured JSON responses. Learn more about Structured Outputs.
            JSON object
                object
                JSON object response format. An older method of generating JSON responses. Using json_schema is recommended for models that support it. Note that the model will not generate JSON without a system or user message instructing it to do so.
        verbosity
            string
            Optional
            Defaults to medium
            Constrains the verbosity of the model's response. Lower values will result in more concise responses, while higher values will result in more verbose responses. Currently supported values are low, medium, and high.
    */
    // [[nodiscard]] AiText text() const;
    // bool setText(const AiText& text);
    // void resetText() { setText({}); }

    /** tool_choice
        string or object
        Optional
        How the model should select which tool (or tools) to use when generating a response. See the tools parameter to see how to specify which tools the model can call.
    */
    // [[nodiscard]] AiToolChoice toolChoice() const;
    // bool setToolChoice(const AiToolChoice& toolChoice);
    // void resetToolChoice() { setToolChoice({}); }

    /** tools
        array
        Optional
        An array of tools the model may call while generating a response. You can specify which tool to use by setting the tool_choice parameter.
        We support the following categories of tools:
            Built-in tools: Tools that are provided by OpenAI that extend the model's capabilities, like web search or file search. Learn more about built-in tools.
            MCP Tools: Integrations with third-party systems via custom MCP servers or predefined connectors such as Google Drive and SharePoint. Learn more about MCP Tools.
            Function calls (custom tools): Functions that are defined by you, enabling the model to call your own code with strongly typed arguments and outputs. Learn more about function calling. You can also use custom tools to call your own code.
    */
    // [[nodiscard]] AiTools tools() const;
    // bool setTools(const AiTools& tools);
    // void resetTools() { setTools({}); }

    /** top_logprobs
        integer
        Optional
        An integer between 0 and 20 specifying the number of most likely tokens to return at each token position, each with an associated log probability.
    */
    [[nodiscard]] int topLogprobs() const { return mTopLogprobs; }
    bool setTopLogprobs(int topLogprobs)
    {
        if (mTopLogprobs == topLogprobs)
            return false;
        mTopLogprobs = topLogprobs;
        return true;
    }
    void resetTopLogprobs() { setTopLogprobs(0); }

    /** top_p
        number
        Optional
        Defaults to 1
        An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.
        We generally recommend altering this or temperature but not both.
    */
    [[nodiscard]] double topP() const { return mTopP; }
    bool setTopP(double topP)
    {
        if (mTopP == topP)
            return false;
        mTopP = topP;
        return true;
    }
    void resetTopP() { setTopP(1.0); }

    /** truncation
        string
        Optional
        Defaults to disabled
        The truncation strategy to use for the model response.
            auto: If the input to this Response exceeds the model's context window size, the model will truncate the response to fit the context window by dropping items from the beginning of the conversation.
            disabled (default): If the input size will exceed the context window size for a model, the request will fail with a 400 error.
    */
    [[nodiscard]] Truncation truncation() const { return mTrucation; }
    bool setTruncation(Truncation truncation)
    {
        if (mTrucation == truncation)
            return true;
        mTrucation = truncation;
        return true;
    }
    bool setTruncation(const QString& truncation)
    {
        return setTruncation(toTruncation(truncation));
    }
    void resetTruncation() { setTruncation(Truncation::TruncationDisabled); }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;
};

class Response : public ai::Response
{
    Q_OBJECT

    Request mRequest;

protected:
    ResponseData* d() { return static_cast<ResponseData*>(ai::Response::d.data()); }
    const ResponseData* d() const
    {
        return static_cast<const ResponseData*>(ai::Response::d.data());
    }

public:
    Response(const Request& request, QNetworkReply* reply, Client* client);

    [[nodiscard]] Client* client() const;
    [[nodiscard]] Request request() const;

public:
    enum Truncation { TruncationAuto, TruncationDisabled };

    /** background
        boolean
        Optional
        Defaults to false
        Whether to run the model response in the background. Learn more.
    */
    [[nodiscard]] bool background() const { return d()->background(); }
    Response& setBackground(bool background)
    {
        if (d()->setBackground(background))
            emit backgroundChanged(QPrivateSignal{});
        return *this;
    }
    Response& resetBackground() { return setBackground(false); }

    /** conversation
        string or object
        Optional
        Defaults to null
        The conversation that this response belongs to. Items from this conversation are prepended to input_items for this response Response. Input items and output items from this response are automatically added to this conversation after this response completes.
    */
    [[nodiscard]] Conversation conversation() const { return d()->conversation(); }
    Response& setConversation(const Conversation& conversation)
    {
        if (d()->setConversation(conversation))
            emit conversationChanged(QPrivateSignal{});
        return *this;
    }
    Response& resetConversation() { return setConversation({}); }

    /** include
        array
        Optional
        Specify additional output data to include in the model response. Currently supported values are:
            web_search_call.action.sources: Include the sources of the web search tool call.
            code_interpreter_call.outputs: Includes the outputs of python code execution in code interpreter tool call items.
            computer_call_output.output.image_url: Include image urls from the computer call output.
            file_search_call.results: Include the search results of the file search tool call.
            message.input_image.image_url: Include image urls from the input message.
            message.output_text.logprobs: Include logprobs with assistant messages.
            reasoning.encrypted_content: Includes an encrypted version of reasoning tokens in reasoning item outputs. This enables reasoning items to be used in multi-turn conversations when using the Responses API statelessly (like when the store parameter is set to false, or when an organization is enrolled in the zero data retention program).
    */
    // [[nodiscard]] AiIncludeList include() const;
    // Response& setInclude(const AiIncludeList& include);
    // Response& resetInclude() { setInclude({}); }

    /** input
        string or array
        Optional
        Text, image, or file inputs to the model, used to generate a response.
        Learn more:
            Text inputs and outputs
            Image inputs
            File inputs
            Conversation state
            Function calling
    */
    [[nodiscard]] Input input() const { return d()->input(); }
    Response& setInput(const Input& input)
    {
        if (d()->setInput(input))
            emit inputChanged(QPrivateSignal{});
        return *this;
    }
    Response& resetInput() { return setInput({}); }

    /** instructions
        string
        Optional
        A system (or developer) message inserted into the model's context.
        When using along with previous_response_id, the instructions from a previous response will not be carried over to the next response. This makes it simple to swap out system (or developer) messages in new responses.
    */
    [[nodiscard]] QString instructions() const;
    Response& setInstructions(const QString& instructions);
    Response& resetInstructions() { return setInstructions({}); }

    /** max_output_tokens
        integer
        Optional
        An upper bound for the number of tokens that can be generated for a response, including visible output tokens and reasoning tokens.
    */
    [[nodiscard]] int maxOutputTokens() const;
    Response& setMaxOutputTokens(int maxOutputTokens);
    Response& resetMaxOutputTokens() { return setMaxOutputTokens(-1); }

    /** max_tool_calls
        integer
        Optional
        The maximum number of total calls to built-in tools that can be processed in a response. This maximum number applies across all built-in tool calls, not per individual tool. Any further attempts to call a tool by the model will be ignored.
    */
    [[nodiscard]] int maxToolCalls() const;
    Response& setMaxToolCalls(int maxToolCalls);
    Response& resetMaxToolCalls() { return setMaxToolCalls(-1); }

    /** parallel_tool_calls
        boolean
        Optional
        Defaults to true
        Whether to allow the model to run tool calls in parallel.
    */
    [[nodiscard]] bool parallelToolCalls() const;
    Response& setParallelToolCalls(bool parallelToolCalls);
    Response& resetParallelToolCalls();

    /** previous_response_id
        string
        Optional
        The unique ID of the previous response to the model. Use this to create multi-turn conversations. Learn more about conversation state. Cannot be used in conjunction with conversation.
    */
    [[nodiscard]] QString previousResponseId() const;
    Response& setPreviousResponseId(const QString& previousResponseId);
    Response& resetPreviousResponseId() { return setPreviousResponseId({}); }

    /** prompt
        object
        Optional
        Reference to a prompt template and its variables. Learn more.
    */
    // [[nodiscard]] AiPrompt prompt() const;
    // Response& setPrompt(const AiPrompt& prompt);
    // Response& resetPrompt() { return setPrompt({}); }

    /** prompt_cache_key
        string
        Optional
        Used by OpenAI to cache responses for similar Responses to optimize your cache hit rates. Replaces the user field. Learn more.
    */
    [[nodiscard]] QString promptCacheKey() const;
    Response& setPromptCacheKey(const QString& promptCacheKey);
    Response& resetPromptCacheKey() { return setPromptCacheKey({}); }

    /** reasoning
        object
        Optional
        gpt-5 and o-series models only
        Configuration options for reasoning models.
    */
    [[nodiscard]] Reasoning reasoning() const { return d()->reasoning(); }
    Response& setReasoning(const Reasoning& reasoning)
    {
        if (d()->setReasoning(reasoning))
            emit reasoningChanged(QPrivateSignal{});
        return *this;
    }
    Response& resetReasoning() { return setReasoning({}); }

    /** safety_identifier
        string
        Optional
        A stable identifier used to help detect users of your application that may be violating OpenAI's usage policies. The IDs should be a string that uniquely identifies each user. We recommend hashing their username or email address, in order to avoid sending us any identifying information. Learn more.
    */
    [[nodiscard]] QString safetyIdetifier() const;
    Response& setSafetyIdetifier(const QString& safetyIdetifier);
    Response& resetSafetyIdetifier() { return setSafetyIdetifier({}); }

    /** service_tier
        string
        Optional
        Defaults to auto
        Specifies the processing type used for serving the Response.
            If set to 'auto', then the Response will be processed with the service tier configured in the Project settings. Unless otherwise configured, the Project will use 'default'.
            If set to 'default', then the Response will be processed with the standard pricing and performance for the selected model.
            If set to 'flex' or 'priority', then the Response will be processed with the corresponding service tier.
            When not set, the default behavior is 'auto'.
        When the service_tier parameter is set, the response body will include the service_tier value based on the processing mode actually used to serve the Response. This response value may be different from the value set in the parameter.
    */
    [[nodiscard]] QString serviceTier() const;
    Response& setServiceTier(const QString& serviceTier);
    Response& resetServiceTier() { return setServiceTier(QStringLiteral("auto")); }

    /** isStored
        boolean
        Optional
        Defaults to true
        Whether to isStored the generated model response for later retrieval via API.
    */
    [[nodiscard]] bool isStored() const;
    Response& setStored(bool store);
    Response& resetStored();

    /** temperature
        number
        Optional
        Defaults to 1
        What sampling temperature to use, between 0 and 2. Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic. We generally recommend altering this or top_p but not both.
    */
    [[nodiscard]] double temperature() const;
    Response& setTemperature(double temperature);
    Response& resetTemperature() { return setTemperature(1.0); }

    /** text
        object
        Optional
        Configuration options for a text response from the model. Can be plain text or structured JSON data. Learn more:
            Text inputs and outputs
            Structured Outputs
        format
            object
            Optional
            An object specifying the format that the model must output.
            Configuring { "type": "json_schema" } enables Structured Outputs, which ensures the model will match your supplied JSON schema. Learn more in the Structured Outputs guide.
            The default format is { "type": "text" } with no additional options.
            Not recommended for gpt-4o and newer models:
            Setting to { "type": "json_object" } enables the older JSON mode, which ensures the message the model generates is valid JSON. Using json_schema is preferred for models that support it.
            Text
                object
                Default response format. Used to generate text responses.
            JSON schema
                object
                JSON Schema response format. Used to generate structured JSON responses. Learn more about Structured Outputs.
            JSON object
                object
                JSON object response format. An older method of generating JSON responses. Using json_schema is recommended for models that support it. Note that the model will not generate JSON without a system or user message instructing it to do so.
        verbosity
            string
            Optional
            Defaults to medium
            Constrains the verbosity of the model's response. Lower values will result in more concise responses, while higher values will result in more verbose responses. Currently supported values are low, medium, and high.
    */
    // [[nodiscard]] AiText text() const;
    // Response& setText(const AiText& text);
    // Response& resetText() {return  setText({}); }

    /** tool_choice
        string or object
        Optional
        How the model should select which tool (or tools) to use when generating a response. See the tools parameter to see how to specify which tools the model can call.
    */
    // [[nodiscard]] AiToolChoice toolChoice() const;
    // Response& setToolChoice(const AiToolChoice& toolChoice);
    // Response& resetToolChoice() {return  setToolChoice({}); }

    /** tools
        array
        Optional
        An array of tools the model may call while generating a response. You can specify which tool to use by setting the tool_choice parameter.
        We support the following categories of tools:
            Built-in tools: Tools that are provided by OpenAI that extend the model's capabilities, like web search or file search. Learn more about built-in tools.
            MCP Tools: Integrations with third-party systems via custom MCP servers or predefined connectors such as Google Drive and SharePoint. Learn more about MCP Tools.
            Function calls (custom tools): Functions that are defined by you, enabling the model to call your own code with strongly typed arguments and outputs. Learn more about function calling. You can also use custom tools to call your own code.
    */
    // [[nodiscard]] AiTools tools() const;
    // Response& setTools(const AiTools& tools);
    // Response& resetTools() { return setTools({}); }

    /** top_logprobs
        integer
        Optional
        An integer between 0 and 20 specifying the number of most likely tokens to return at each token position, each with an associated log probability.
    */
    [[nodiscard]] int topLogprobs() const;
    Response& setTopLogprobs(int topLogprobs);
    Response& resetTopLogprobs() { return setTopLogprobs(0); }

    /** top_p
        number
        Optional
        Defaults to 1
        An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.
        We generally recommend altering this or temperature but not both.
    */
    [[nodiscard]] double topP() const;
    Response& setTopP(double topP);
    Response& resetTopP() { return setTopP(1.0); }

    /** truncation
        string
        Optional
        Defaults to disabled
        The truncation strategy to use for the model response.
            auto: If the input to this Response exceeds the model's context window size, the model will truncate the response to fit the context window by dropping items from the beginning of the conversation.
            disabled (default): If the input size will exceed the context window size for a model, the Response will fail with a 400 error.
    */
    [[nodiscard]] Truncation truncation() const;
    Response& setTruncation(Truncation truncation);
    Response& setTruncation(const QString& truncation);
    Response& resetTruncation() { return setTruncation(Truncation::TruncationDisabled); }

signals:
    void backgroundChanged(QPrivateSignal);
    void conversationChanged(QPrivateSignal);
    void inputChanged(QPrivateSignal);
    void reasoningChanged(QPrivateSignal);

protected:
    Response(ResponseData* data,
             const Request& request,
             QNetworkReply* reply,
             Client* client = nullptr);

    // bool readJson(const QJsonObject& json) override;
    // bool writeJson(QJsonObject& json) const override;
};

} // namespace ai::responses

#endif // AI_RESPONSES_RESPONSE_H
