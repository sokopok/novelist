#ifndef AI_RESPONSESREQUEST_H
#define AI_RESPONSESREQUEST_H

#include "request.h"

namespace ai {

class ResponsesRequestData
{
    bool mBackground = false;
    Conversation mConversation;
    Input mInput;

public:
    enum Truncation { TruncationAuto, TruncationDisabled };

    ResponsesRequestData();
    ResponsesRequestData(const RequestData& requestData);

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
    [[nodiscard]] QString instructions() const;
    bool setInstructions(const QString& instructions);
    void resetInstructions() { setInstructions({}); }

    /** max_output_tokens
        integer
        Optional
        An upper bound for the number of tokens that can be generated for a response, including visible output tokens and reasoning tokens.
    */
    [[nodiscard]] int maxOutputTokens() const;
    bool setMaxOutputTokens(int maxOutputTokens);
    void resetMaxOutputTokens() { setMaxOutputTokens(-1); }

    /** max_tool_calls
        integer
        Optional
        The maximum number of total calls to built-in tools that can be processed in a response. This maximum number applies across all built-in tool calls, not per individual tool. Any further attempts to call a tool by the model will be ignored.
    */
    [[nodiscard]] int maxToolCalls() const;
    bool setMaxToolCalls(int maxToolCalls);
    void resetMaxToolCalls() { setMaxToolCalls(-1); }

    /** parallel_tool_calls
        boolean
        Optional
        Defaults to true
        Whether to allow the model to run tool calls in parallel.
    */
    [[nodiscard]] bool parallelToolCalls() const;
    bool setParallelToolCalls(bool parallelToolCalls);
    void resetParallelToolCalls();
    /** previous_response_id
        string
        Optional
        The unique ID of the previous response to the model. Use this to create multi-turn conversations. Learn more about conversation state. Cannot be used in conjunction with conversation.
    */
    [[nodiscard]] QString previousResponseId() const;
    bool setPreviousResponseId(const QString& previousResponseId);
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
    [[nodiscard]] QString promptCacheKey() const;
    bool setPromptCacheKey(const QString& promptCacheKey);
    void resetPromptCacheKey() { setPromptCacheKey({}); }

    /** reasoning
        object
        Optional
        gpt-5 and o-series models only
        Configuration options for reasoning models.
    */
    // [[nodiscard]] AiReasoning reasoning() const;
    // bool setReasoning(const AiReasoning& reasoning);
    // void resetReasoning() { setReasoning({}); }

    /** safety_identifier
        string
        Optional
        A stable identifier used to help detect users of your application that may be violating OpenAI's usage policies. The IDs should be a string that uniquely identifies each user. We recommend hashing their username or email address, in order to avoid sending us any identifying information. Learn more.
    */
    [[nodiscard]] QString safetyIdetifier() const;
    bool setSafetyIdetifier(const QString& safetyIdetifier);
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
    [[nodiscard]] QString serviceTier() const;
    bool setServiceTier(const QString& serviceTier);
    void resetServiceTier() { setServiceTier(QStringLiteral("auto")); }

    /** isStored
        boolean
        Optional
        Defaults to true
        Whether to isStored the generated model response for later retrieval via API.
    */
    [[nodiscard]] bool isStored() const;
    bool setStored(bool store);
    void resetStored();

    /** temperature
        number
        Optional
        Defaults to 1
        What sampling temperature to use, between 0 and 2. Higher values like 0.8 will make the output more random, while lower values like 0.2 will make it more focused and deterministic. We generally recommend altering this or top_p but not both.
    */
    [[nodiscard]] double temperature() const;
    bool setTemperature(double temperature);
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
    [[nodiscard]] int topLogprobs() const;
    bool setTopLogprobs(int topLogprobs);
    void resetTopLogprobs() { setTopLogprobs(0); }

    /** top_p
        number
        Optional
        Defaults to 1
        An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.
        We generally recommend altering this or temperature but not both.
    */
    [[nodiscard]] double topP() const;
    bool setTopP(double topP);
    void resetTopP() { setTopP(1.0); }

    /** truncation
        string
        Optional
        Defaults to disabled
        The truncation strategy to use for the model response.
            auto: If the input to this Response exceeds the model's context window size, the model will truncate the response to fit the context window by dropping items from the beginning of the conversation.
            disabled (default): If the input size will exceed the context window size for a model, the request will fail with a 400 error.
    */
    [[nodiscard]] Truncation truncation() const;
    bool setTruncation(Truncation truncation);
    bool setTruncation(const QString& truncation);
    void resetTruncation() { setTruncation(Truncation::TruncationDisabled); }

    bool readJson(const QJsonObject& json)
    {
        // if (!RequestData::readJson(json))
        //     return false;

        if (const auto v = json.value("background"); v.isBool())
            setBackground(v.toBool());

        if (const auto v = json.value("conversation"); v.isString())
            setConversation({v.toString()});
        else if (v.isObject())
            setConversation(Conversation::fromJson(v.toObject()));

        if (const auto v = json.value("input"); v.isString())
            setInput({v.toString()});
        else if (v.isArray())
            setInput(Input::fromJson(v.toArray()));

        return true;
    }
    bool writeJson(QJsonObject& json) const
    {
        // if (!RequestData::writeJson(json))
        //     return false;

        if (const auto v = background())
            json[QStringLiteral("background")] = v;

        if (const auto v = conversation(); !v.isEmpty())
            json[QStringLiteral("conversation")] = v.toJson();

        if (const auto v = input(); !v.isEmpty())
            json[QStringLiteral("input")] = v.toJson();

        return true;
    }
};

class ResponsesRequest : public Request, public ResponsesRequestData
{
public:
    ResponsesRequest();

    ResponsesRequest& setBackground(bool background)
    {
        ResponsesRequestData::setBackground(background);
        return *this;
    }
    ResponsesRequest& setConversation(Conversation conversation)
    {
        ResponsesRequestData::setConversation(conversation);
        return *this;
    }
    ResponsesRequest& setInput(Input input)
    {
        ResponsesRequestData::setInput(input);
        return *this;
    }

    ResponsesRequest& setAttribute(QNetworkRequest::Attribute code, const QVariant& value)
    {
        QNetworkRequest::setAttribute(code, value);
        return *this;
    }
    ResponsesRequest& setDecompressedSafetyCheckThreshold(qint64 threshold)
    {
        QNetworkRequest::setDecompressedSafetyCheckThreshold(threshold);
        return *this;
    }
    ResponsesRequest& setHeader(QNetworkRequest::KnownHeaders header, const QVariant& value)
    {
        QNetworkRequest::setHeader(header, value);
        return *this;
    }
    ResponsesRequest& setHeaders(QHttpHeaders&& newHeaders)
    {
        QNetworkRequest::setHeaders(newHeaders);
        return *this;
    }
    ResponsesRequest& setHeaders(const QHttpHeaders& newHeaders)
    {
        QNetworkRequest::setHeaders(newHeaders);
        return *this;
    }
    ResponsesRequest& setHttp1Configuration(const QHttp1Configuration& configuration)
    {
        QNetworkRequest::setHttp1Configuration(configuration);
        return *this;
    }
    ResponsesRequest& setHttp2Configuration(const QHttp2Configuration& configuration)
    {
        QNetworkRequest::setHttp2Configuration(configuration);
        return *this;
    }
    ResponsesRequest& setMaximumRedirectsAllowed(int maxRedirectsAllowed)
    {
        QNetworkRequest::setMaximumRedirectsAllowed(maxRedirectsAllowed);
        return *this;
    }
    ResponsesRequest& setOriginatingObject(QObject* object)
    {
        QNetworkRequest::setOriginatingObject(object);
        return *this;
    }
    ResponsesRequest& setPeerVerifyName(const QString& peerName)
    {
        QNetworkRequest::setPeerVerifyName(peerName);
        return *this;
    }
    ResponsesRequest& setPriority(QNetworkRequest::Priority priority)
    {
        QNetworkRequest::setPriority(priority);
        return *this;
    }
    ResponsesRequest& setRawHeader(const QByteArray& headerName, const QByteArray& headerValue)
    {
        QNetworkRequest::setRawHeader(headerName, headerValue);
        return *this;
    }
    ResponsesRequest& setSslConfiguration(const QSslConfiguration& config)
    {
        QNetworkRequest::setSslConfiguration(config);
        return *this;
    }
    ResponsesRequest& setTransferTimeout(int timeout)
    {
        QNetworkRequest::setTransferTimeout(timeout);
        return *this;
    }
    ResponsesRequest& setTransferTimeout(std::chrono::milliseconds duration = DefaultTransferTimeout)
    {
        QNetworkRequest::setTransferTimeout(duration);
        return *this;
    }
    ResponsesRequest& setUrl(const QUrl& url)
    {
        QNetworkRequest::setUrl(url);
        return *this;
    }
    ResponsesRequest& setMetadata(const QVariantMap& metadata)
    {
        RequestData::setMetadata(metadata);
        return *this;
    }
    ResponsesRequest& setModel(const QString& model)
    {
        RequestData::setModel(model);
        return *this;
    }
    ResponsesRequest& setStreaming(bool streaming)
    {
        RequestData::setStreaming(streaming);
        return *this;
    }
    ResponsesRequest& setStreamOptions(const StreamOptions& streamOptions)
    {
        RequestData::setStreamOptions(streamOptions);
        return *this;
    }
    ResponsesRequest& setApiKey(const QByteArray& apiKey)
    {
        RequestData::setApiKey(apiKey);
        return *this;
    }
    ResponsesRequest& setApiUrl(const QUrl& apiUrl)
    {
        RequestData::setApiUrl(apiUrl);
        return *this;
    }
};

} // namespace ai

#endif // AI_RESPONSESREQUEST_H
