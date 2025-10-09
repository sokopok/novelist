#ifndef AI_IMAGES_REQUEST_H
#define AI_IMAGES_REQUEST_H

#include "../request.h"

namespace ai::images {

class Client;

class RequestData;

class Request : public ai::Request
{
    Q_GADGET

public:
    enum Background { AutomaticBackground, TransparentBackground, OpaqueBackground };
    Q_ENUM(Background)

    enum Model { DallE2, DallE3, GptImage1 };
    Q_ENUM(Model)

    enum Moderation { AutomaticModeration, LowModeration };
    Q_ENUM(Moderation)

    enum OutputFormat { PngOutputFormat, JpegOutputFormat, WebpOutputFormat };
    Q_ENUM(OutputFormat)

    enum Quality {
        AutomaticQuality,
        LowQuality,
        MediumQuality,
        HighQuality,
        HdQuality,
        StandardQuality
    };
    Q_ENUM(Quality)

    enum ResponseFormat { UrlResponseFormat, B64JsonResponseFormat };
    Q_ENUM(ResponseFormat)

protected:
    RequestData* d();
    const RequestData* d() const;

    inline static const QMap<Background, QString> BackgroundKV = {{AutomaticBackground, "auto"},
                                                                  {TransparentBackground,
                                                                   "transparent"},
                                                                  {OpaqueBackground, "opaque"}};
    inline static const QMap<Model, QString> ModelKV = {{DallE2, "dall-e-2"},
                                                        {DallE3, "dall-e-3"},
                                                        {GptImage1, "gpt-image-1"}};
    inline static const QMap<Moderation, QString> ModerationKV = {{AutomaticModeration, "auto"},
                                                                  {LowModeration, "low"}};
    inline static const QMap<OutputFormat, QString> OutputFormatKV = {{PngOutputFormat, "png"},
                                                                      {JpegOutputFormat, "jpeg"},
                                                                      {WebpOutputFormat, "webp"}};
    inline static const QMap<Quality, QString> QualityKV = {{AutomaticQuality, "auto"},
                                                            {LowQuality, "low"},
                                                            {MediumQuality, "medium"},
                                                            {HighQuality, "high"},
                                                            {HdQuality, "hd"},
                                                            {StandardQuality, "standard"}};
    inline static const QMap<ResponseFormat, QString> ResponseFormatKV = {{UrlResponseFormat, "url"},
                                                                          {B64JsonResponseFormat,
                                                                           "b64_json"}};

public:
    static Background toBackground(const QString& background)
    {
        return BackgroundKV.key(background, AutomaticBackground);
    }
    static Background toBackground(int background)
    {
        return background >= TransparentBackground && background <= OpaqueBackground
                   ? Background(background)
                   : AutomaticBackground;
    }
    static QString toString(Background background) { return BackgroundKV.value(background); }

    static Model toModel(const QString& model) { return ModelKV.key(model, DallE2); }
    static Model toModel(int model)
    {
        return model >= DallE2 && model <= GptImage1 ? Model(model) : DallE2;
    }
    static QString toString(Model model) { return ModelKV.value(model); }

    static Moderation toModeration(const QString& moderation)
    {
        return ModerationKV.key(moderation, AutomaticModeration);
    }
    static Moderation toModeration(int moderation)
    {
        return moderation >= AutomaticModeration && moderation <= LowModeration
                   ? Moderation(moderation)
                   : AutomaticModeration;
    }
    static QString toString(Moderation moderation) { return ModerationKV.value(moderation); }

    static OutputFormat toOutputFormat(const QString& outputFormat)
    {
        return OutputFormatKV.key(outputFormat, PngOutputFormat);
    }
    static OutputFormat toOutputFormat(int outputFormat)
    {
        return outputFormat >= PngOutputFormat && outputFormat <= WebpOutputFormat
                   ? OutputFormat(outputFormat)
                   : PngOutputFormat;
    }
    static QString toString(OutputFormat outputFormat)
    {
        return OutputFormatKV.value(outputFormat);
    }

    static Quality toQuality(const QString& quality)
    {
        return QualityKV.key(quality, AutomaticQuality);
    }
    static Quality toQuality(int quality)
    {
        return quality >= AutomaticQuality && quality <= StandardQuality ? Quality(quality)
                                                                         : AutomaticQuality;
    }
    static QString toString(Quality quality) { return QualityKV.value(quality); }

    static ResponseFormat toResponseFormat(const QString& responseFormat)
    {
        return ResponseFormatKV.key(responseFormat, UrlResponseFormat);
    }
    static ResponseFormat toResponseFormat(int responseFormat)
    {
        return responseFormat >= UrlResponseFormat && responseFormat <= B64JsonResponseFormat
                   ? ResponseFormat(responseFormat)
                   : UrlResponseFormat;
    }
    static QString toString(ResponseFormat responseFormat)
    {
        return ResponseFormatKV.value(responseFormat);
    }

    Request();

    Request& operator=(const ai::Request& rhs)
    {
        ai::Request::operator=(rhs);
        return *this;
    }

    /** prompt
        string
        Required
        A text description of the desired image(s). The maximum length is 32000 characters for gpt-image-1, 1000 characters for dall-e-2 and 4000 characters for dall-e-3.
        **/
    [[nodiscard]] QString prompt() const;
    Request& setPrompt(const QString& prompt);
    Request& resetPrompt();

    /** background
        string or null
        Optional
        Defaults to auto
        Allows to set transparency for the background of the generated image(s). This parameter is only supported for gpt-image-1. Must be one of transparent, opaque or auto (default value). When auto is used, the model will automatically determine the best background for the image.
        If transparent, the output format needs to support transparency, so it should be set to either png (default value) or webp.
        **/
    [[nodiscard]] Background background() const;
    Request& setBackground(Background background);
    Request& setBackground(const QString& background);
    Request& resetBackground();

    /** model
        string
        Optional
        Defaults to dall-e-2
        The model to use for image generation. One of dall-e-2, dall-e-3, or gpt-image-1. Defaults to dall-e-2 unless a parameter specific to gpt-image-1 is used.
        **/
    [[nodiscard]] Model model() const;
    Request& setModel(Model model);
    Request& setModel(const QString& model);
    Request& resetModel();

    /** moderation
        string or null
        Optional
        Defaults to auto
        Control the content-moderation level for images generated by gpt-image-1. Must be either low for less restrictive filtering or auto (default value).
        **/
    [[nodiscard]] Moderation moderation() const;
    Request& setModeration(Moderation moderation);
    Request& setModeration(const QString& moderation);
    Request& resetModeration();

    /** n
        integer or null
        Optional
        Defaults to 1
        The number of images to generate. Must be between 1 and 10. For dall-e-3, only n=1 is supported.
        **/
    [[nodiscard]] int n() const;
    Request& setN(int n);
    Request& resetN();

    /** output_compression
        integer or null
        Optional
        Defaults to 100
        The compression level (0-100%) for the generated images. This parameter is only supported for gpt-image-1 with the webp or jpeg output formats, and defaults to 100.
        **/
    [[nodiscard]] int outputCompression() const;
    Request& setOutputCompression(int outputCompression);
    Request& resetOutputCompression();

    /** output_format
        string or null
        Optional
        Defaults to png
        The format in which the generated images are returned. This parameter is only supported for gpt-image-1. Must be one of png, jpeg, or webp.
        **/
    [[nodiscard]] OutputFormat outputFormat() const;
    Request& setOutputFormat(OutputFormat outputFormat);
    Request& setOutputFormat(const QString& outputFormat);
    Request& resetOutputFormat();

    /** partial_images
        integer
        Optional
        Defaults to 0
        The number of partial images to generate. This parameter is used for streaming responses that return partial images. Value must be between 0 and 3. When set to 0, the response will be a single image sent in one streaming event.
        Note that the final image may be sent before the full number of partial images are generated if the full image is generated more quickly.
        **/
    [[nodiscard]] int partialImages() const;
    Request& setPartialImages(int partialImages);
    Request& resetPartialImages();

    /** quality
        string or null
        Optional
        Defaults to auto
        The quality of the image that will be generated.
            auto (default value) will automatically select the best quality for the given model.
            high, medium and low are supported for gpt-image-1.
            hd and standard are supported for dall-e-3.
            standard is the only option for dall-e-2.
        **/
    [[nodiscard]] Quality quality() const;
    Request& setQuality(Quality quality);
    Request& setQuality(const QString& quality);
    Request& resetQuality();

    /** response_format
        string or null
        Optional
        Defaults to url
        The format in which generated images with dall-e-2 and dall-e-3 are returned. Must be one of url or b64_json. URLs are only valid for 60 minutes after the image has been generated. This parameter isn't supported for gpt-image-1 which will always return base64-encoded images.
        **/
    [[nodiscard]] ResponseFormat responseFormat() const;
    Request& setResponseFormat(ResponseFormat responseFormat);
    Request& setResponseFormat(const QString& responseFormat);
    Request& resetResponseFormat();

    /** size
        string or null
        Optional
        Defaults to auto
        The size of the generated images. Must be one of 1024x1024, 1536x1024 (landscape), 1024x1536 (portrait), or auto (default value) for gpt-image-1, one of 256x256, 512x512, or 1024x1024 for dall-e-2, and one of 1024x1024, 1792x1024, or 1024x1792 for dall-e-3.
        **/
    [[nodiscard]] QString size() const;
    Request& setSize(const QString& size);
    Request& resetSize();

    /** stream
        boolean or null
        Optional
        Defaults to false
        Generate the image in streaming mode. Defaults to false. See the Image generation guide for more information. This parameter is only supported for gpt-image-1.
        */
    [[nodiscard]] bool isStreaming() const;
    Request& setStreaming(bool streaming);
    Request& resetStreaming();

    /** style
        string or null
        Optional
        Defaults to vivid
        The style of the generated images. This parameter is only supported for dall-e-3. Must be one of vivid or natural. Vivid causes the model to lean towards generating hyper-real and dramatic images. Natural causes the model to produce more natural, less hyper-real looking images.
        **/
    [[nodiscard]] QString style() const;
    Request& setStyle(const QString& style);
    Request& resetStyle();

    /** user
        string
        Optional
        A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse. Learn more.
        **/
    [[nodiscard]] QString user() const;
    Request& setUser(const QString& user);
    Request& resetUser();

protected:
    Request(RequestData* data);
};

class RequestData : public ai::RequestData
{
    QString mPrompt;
    QString mSize;
    QString mStyle;
    QString mUser;
    int mN = 1;
    int mOutputCompression = 0;
    int mPartialImages = 0;
    Request::Background mBackground = Request::AutomaticBackground;
    Request::Model mModel;
    Request::Moderation mModeration;
    Request::OutputFormat mOutputFormat;
    Request::Quality mQuality;
    Request::ResponseFormat mResponseFormat;
    bool mStreaming = false;

public:
    RequestData* clone() const override { return new RequestData{*this}; }

    /** prompt
        string
        Required
        A text description of the desired image(s). The maximum length is 32000 characters for gpt-image-1, 1000 characters for dall-e-2 and 4000 characters for dall-e-3.
        **/
    [[nodiscard]] QString prompt() const { return mPrompt; }
    bool setPrompt(const QString& prompt)
    {
        if (mPrompt == prompt)
            return false;
        mPrompt = prompt;
        return true;
    }
    void resetPrompt() { setPrompt({}); }

    /** background
        string or null
        Optional
        Defaults to auto
        Allows to set transparency for the background of the generated image(s). This parameter is only supported for gpt-image-1. Must be one of transparent, opaque or auto (default value). When auto is used, the model will automatically determine the best background for the image.
        If transparent, the output format needs to support transparency, so it should be set to either png (default value) or webp.
        **/
    [[nodiscard]] Request::Background background() const { return mBackground; }
    bool setBackground(Request::Background background)
    {
        if (mBackground == background)
            return false;
        mBackground = background;
        return true;
    }
    bool setBackground(const QString& background)
    {
        return setBackground(Request::toBackground(background));
    }
    void resetBackground() { setBackground({}); }

    /** model
        string
        Optional
        Defaults to dall-e-2
        The model to use for image generation. One of dall-e-2, dall-e-3, or gpt-image-1. Defaults to dall-e-2 unless a parameter specific to gpt-image-1 is used.
        **/
    [[nodiscard]] Request::Model model() const { return mModel; }
    bool setModel(Request::Model model)
    {
        if (mModel == model)
            return false;
        mModel = model;
        if (mModel == Request::DallE3)
            setN(n());
        return true;
    }
    bool setModel(const QString& model) { return setModel(Request::toModel(model)); }
    void resetModel() { setModel({}); }

    /** moderation
        string or null
        Optional
        Defaults to auto
        Control the content-moderation level for images generated by gpt-image-1. Must be either low for less restrictive filtering or auto (default value).
        **/
    [[nodiscard]] Request::Moderation moderation() const { return mModeration; }
    bool setModeration(Request::Moderation moderation)
    {
        if (mModeration == moderation)
            return false;
        mModeration = moderation;
        return true;
    }
    bool setModeration(const QString& moderation)
    {
        return setModeration(Request::toModeration(moderation));
    }
    void resetModeration() { setModeration({}); }

    /** n
        integer or null
        Optional
        Defaults to 1
        The number of images to generate. Must be between 1 and 10. For dall-e-3, only n=1 is supported.
        **/
    [[nodiscard]] int n() const { return mN; }
    bool setN(int n)
    {
        n = std::max(1, std::min(mModel == Request::DallE3 ? 1 : 10, n));
        if (mN == n)
            return false;
        mN = n;
        return true;
    }
    void resetN() { setN({}); }

    /** output_compression
        integer or null
        Optional
        Defaults to 100
        The compression level (0-100%) for the generated images. This parameter is only supported for gpt-image-1 with the webp or jpeg output formats, and defaults to 100.
        **/
    [[nodiscard]] int outputCompression() const { return mOutputCompression; }
    bool setOutputCompression(int outputCompression)
    {
        outputCompression = std::max(0, std::min(100, outputCompression));
        if (mOutputCompression == outputCompression)
            return false;
        mOutputCompression = outputCompression;
        return true;
    }
    void resetOutputCompression() { setOutputCompression({}); }

    /** output_format
        string or null
        Optional
        Defaults to png
        The format in which the generated images are returned. This parameter is only supported for gpt-image-1. Must be one of png, jpeg, or webp.
        **/
    [[nodiscard]] Request::OutputFormat outputFormat() const { return mOutputFormat; }
    bool setOutputFormat(Request::OutputFormat outputFormat)
    {
        if (mOutputFormat == outputFormat)
            return false;
        mOutputFormat = outputFormat;
        return true;
    }
    bool setOutputFormat(const QString& outputFormat)
    {
        return setOutputFormat(Request::toOutputFormat(outputFormat));
    }
    void resetOutputFormat() { setOutputFormat({}); }

    /** partial_images
        integer
        Optional
        Defaults to 0
        The number of partial images to generate. This parameter is used for streaming responses that return partial images. Value must be between 0 and 3. When set to 0, the response will be a single image sent in one streaming event.
        Note that the final image may be sent before the full number of partial images are generated if the full image is generated more quickly.
        **/
    [[nodiscard]] int partialImages() const { return mPartialImages; }
    bool setPartialImages(int partialImages)
    {
        if (mPartialImages == partialImages)
            return false;
        mPartialImages = partialImages;
        return true;
    }
    void resetPartialImages() { setPartialImages({}); }

    /** quality
        string or null
        Optional
        Defaults to auto
        The quality of the image that will be generated.
            auto (default value) will automatically select the best quality for the given model.
            high, medium and low are supported for gpt-image-1.
            hd and standard are supported for dall-e-3.
            standard is the only option for dall-e-2.
        **/
    [[nodiscard]] Request::Quality quality() const { return mQuality; }
    bool setQuality(Request::Quality quality)
    {
        if (mQuality == quality)
            return false;
        mQuality = quality;
        return true;
    }
    bool setQuality(const QString& quality) { return setQuality(Request::toQuality(quality)); }
    void resetQuality() { setQuality({}); }

    /** response_format
        string or null
        Optional
        Defaults to url
        The format in which generated images with dall-e-2 and dall-e-3 are returned. Must be one of url or b64_json. URLs are only valid for 60 minutes after the image has been generated. This parameter isn't supported for gpt-image-1 which will always return base64-encoded images.
        **/
    [[nodiscard]] Request::ResponseFormat responseFormat() const { return mResponseFormat; }
    bool setResponseFormat(Request::ResponseFormat responseFormat)
    {
        if (mResponseFormat == responseFormat)
            return false;
        mResponseFormat = responseFormat;
        return true;
    }
    bool setResponseFormat(const QString& responseFormat)
    {
        return setResponseFormat(Request::toResponseFormat(responseFormat));
    }
    void resetResponseFormat() { setResponseFormat({}); }

    /** size
        string or null
        Optional
        Defaults to auto
        The size of the generated images. Must be one of 1024x1024, 1536x1024 (landscape), 1024x1536 (portrait), or auto (default value) for gpt-image-1, one of 256x256, 512x512, or 1024x1024 for dall-e-2, and one of 1024x1024, 1792x1024, or 1024x1792 for dall-e-3.
        **/
    [[nodiscard]] QString size() const { return mSize; }
    bool setSize(const QString& size)
    {
        if (mSize == size)
            return false;
        mSize = size;
        return true;
    }
    void resetSize() { setSize({}); }

    /** stream
        boolean or null
        Optional
        Defaults to false
        Generate the image in streaming mode. Defaults to false. See the Image generation guide for more information. This parameter is only supported for gpt-image-1.
        */
    [[nodiscard]] bool isStreaming() const { return mStreaming; }
    bool setStreaming(bool streaming)
    {
        if (mStreaming == streaming)
            return false;
        mStreaming = streaming;
        return true;
    }
    void resetStreaming() { setStreaming(false); }

    /** style
        string or null
        Optional
        Defaults to vivid
        The style of the generated images. This parameter is only supported for dall-e-3. Must be one of vivid or natural. Vivid causes the model to lean towards generating hyper-real and dramatic images. Natural causes the model to produce more natural, less hyper-real looking images.
        **/
    [[nodiscard]] QString style() const { return mStyle; }
    bool setStyle(const QString& style)
    {
        if (mStyle == style)
            return false;
        mStyle = style;
        return true;
    }
    void resetStyle() { setStyle({}); }

    /** user
        string
        Optional
        A unique identifier representing your end-user, which can help OpenAI to monitor and detect abuse. Learn more.
        **/
    [[nodiscard]] QString user() const { return mUser; }
    bool setUser(const QString& user)
    {
        if (mUser == user)
            return false;
        mUser = user;
        return true;
    }
    void resetUser() { setUser({}); }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override
    {
        if (!ai::RequestData::writeJson(json, full))
            return false;

        return true;
    }
};

} // namespace ai::images

#endif // AI_IMAGES_REQUEST_H
