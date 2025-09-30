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
    RequestData* d() { return static_cast<RequestData*>(ai::Client::d.data()); }
    const RequestData* d() const { return static_cast<const RequestData*>(ai::Client::d.data()); }

public:
    explicit Client(QObject* parent = nullptr);

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

    /** background
        boolean
        Optional
        Defaults to false
        Whether to run the model response in the background. Learn more.
    */
    [[nodiscard]] bool background() const { return d()->background(); }
    Client& setBackground(bool background)
    {
        d()->setBackground(background);
        return *this;
    }
    Client& resetBackground() { return setBackground(false); }

    /** conversation
        string or object
        Optional
        Defaults to null
        The conversation that this response belongs to. Items from this conversation are prepended to input_items for this response request. Input items and output items from this response are automatically added to this conversation after this response completes.
    */
    [[nodiscard]] Conversation conversation() const { return d()->conversation(); }
    Client& setConversation(const Conversation& conversation)
    {
        d()->setConversation(conversation);
        return *this;
    }
    Client& resetConversation() { return setConversation({}); }

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
    // Request& setInclude(const AiIncludeList& include);
    // Request& resetInclude() { setInclude({}); }

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
    Client& setInput(const Input& input)
    {
        d()->setInput(input);
        return *this;
    }
    Client& resetInput() { return setInput({}); }

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
    virtual bool prepareRequest(ai::Request& prep, const ai::Request& request) const override
    {
        return ai::Client::prepareRequest(prep, request);
    }
    virtual bool prepareRequest(Request& prep, const Request& request) const
    {
        if (!prepareRequest(static_cast<ai::Request&>(prep),
                            static_cast<const ai::Request&>(request)))
            return false;

        prep.setBackground(request.background());
        prep.setInput(request.input().isEmpty() ? input() : request.input());
        prep.setConversation(request.conversation().isEmpty() ? conversation()
                                                              : request.conversation());
        return true;
    }

    // [[nodiscard]] bool validateRequest(const ai::Request& request) const override{return va}
    using ai::Client::validateRequest;
    [[nodiscard]] virtual bool validateRequest(const Request& request) const;

private:
};

} // namespace ai

#endif // AI_RESPONSES_CLIENT_H
