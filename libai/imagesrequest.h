#ifndef LIBAI_IMAGESREQUEST_H
#define LIBAI_IMAGESREQUEST_H

#include "request.h"

namespace ai {

class ImagesClient;

class ImagesRequest : public Request
{
    Q_GADGET

public:
    enum Background {
        Background_Auto,
        Background_Transparent,
        Background_Opaque,
        Background_Custom
    };
    Q_ENUM(Background)

    enum Model { Model_DallE2, Model_DallE3, Model_GptImage1, Model_Custom };
    Q_ENUM(Model)

    enum Moderation { Moderation_Auto, Moderation_Low, Moderation_Custom };
    Q_ENUM(Moderation)

    enum OutputFormat {
        OutputFormat_Png,
        OutputFormat_Jpeg,
        OutputFormat_Webp,
        OutputFormat_Custom
    };
    Q_ENUM(OutputFormat)

    enum Quality {
        Quality_Auto,
        Quality_Low,
        Quality_Medium,
        Quality_High,
        Quality_Hd,
        Quality_Standard,
        Quality_Custom
    };
    Q_ENUM(Quality)

    enum ResponseFormat { ResponseFormat_Url, ResponseFormat_B64Json, ResponseFormat_Custom };
    Q_ENUM(ResponseFormat)

    enum Size {
        Size_Auto,
        Size_256x256,
        Size_512x512,
        Size_1024x1024,
        Size_1536x1024,
        Size_1024x1536,
        Size_1792x1024,
        Size_1024x1792,
        Size_Custom
    };
    Q_ENUM(Size)

    enum Style { Style_Vivid, Style_Natural, Style_Custom };
    Q_ENUM(Style)

    static Background toBackground(const QString& background)
    {
        return BackgroundKV.key(background, Background_Auto);
    }
    static Background toBackground(int background)
    {
        return background >= Background_Transparent && background <= Background_Opaque
                   ? Background(background)
                   : Background_Auto;
    }
    static QString toString(Background background) { return BackgroundKV.value(background); }

    static Model toModel(const QString& model) { return ModelKV.key(model, Model_DallE2); }
    static Model toModel(int model)
    {
        return model >= Model_DallE2 && model <= Model_GptImage1 ? Model(model) : Model_DallE2;
    }
    static QString toString(Model model) { return ModelKV.value(model); }

    static Moderation toModeration(const QString& moderation)
    {
        return ModerationKV.key(moderation, Moderation_Auto);
    }
    static Moderation toModeration(int moderation)
    {
        return moderation >= Moderation_Auto && moderation <= Moderation_Low
                   ? Moderation(moderation)
                   : Moderation_Auto;
    }
    static QString toString(Moderation moderation) { return ModerationKV.value(moderation); }

    static OutputFormat toOutputFormat(const QString& outputFormat)
    {
        return OutputFormatKV.key(outputFormat, OutputFormat_Png);
    }
    static OutputFormat toOutputFormat(int outputFormat)
    {
        return outputFormat >= OutputFormat_Png && outputFormat <= OutputFormat_Webp
                   ? OutputFormat(outputFormat)
                   : OutputFormat_Png;
    }
    static QString toString(OutputFormat outputFormat)
    {
        return OutputFormatKV.value(outputFormat);
    }

    static Quality toQuality(const QString& quality)
    {
        return QualityKV.key(quality, Quality_Auto);
    }
    static Quality toQuality(int quality)
    {
        return quality >= Quality_Auto && quality <= Quality_Standard ? Quality(quality)
                                                                      : Quality_Auto;
    }
    static QString toString(Quality quality) { return QualityKV.value(quality); }

    static ResponseFormat toResponseFormat(const QString& responseFormat)
    {
        return ResponseFormatKV.key(responseFormat, ResponseFormat_Url);
    }
    static ResponseFormat toResponseFormat(int responseFormat)
    {
        return responseFormat >= ResponseFormat_Url && responseFormat <= ResponseFormat_B64Json
                   ? ResponseFormat(responseFormat)
                   : ResponseFormat_Url;
    }
    static QString toString(ResponseFormat responseFormat)
    {
        return ResponseFormatKV.value(responseFormat);
    }

    static Size toSize(const QString& size) { return SizeKV.key(size, Size_Auto); }
    static Size toSize(int size)
    {
        return size >= Size_Auto && size <= Size_1024x1792 ? Size(size) : Size_Auto;
    }
    static QString toString(Size size) { return SizeKV.value(size); }

    static Style toStyle(const QString& style) { return StyleKV.key(style, Style_Vivid); }
    static Style toStyle(int style)
    {
        return style >= Style_Vivid && style <= Style_Natural ? Style(style) : Style_Vivid;
    }
    static QString toString(Style style) { return StyleKV.value(style); }

    ImagesRequest(const QUrl& url = {})
        : Request{url}
    {
        if (url.isEmpty() || !url.isValid())
            resetUrl();
    }

    bool resetUrl() override
    {
        QUrl u{"https://api.openai.com/v1/images/generations"};
        if (url() == u)
            return false;
        setUrl(u);
        return true;
    }

    [[nodiscard]] QString prompt() const { return mPrompt; }
    bool setPrompt(const QString& prompt)
    {
        auto p = prompt.left(mModel == Model_GptImage1 ? 32000
                             : mModel == Model_DallE2  ? 1000
                             : mModel == Model_DallE3  ? 4000
                                                       : 32000);
        if (mPrompt == p)
            return false;
        mPrompt = p;
        return true;
    }
    void resetPrompt() { setPrompt({}); }

    [[nodiscard]] Background background() const { return mBackground; }
    [[nodiscard]] QString backgroundAsString() const
    {
        return mBackground != Background_Custom
                   ? toString(mBackground)
                   : mExtra.value(QStringLiteral("background")).toString();
    }
    bool setBackground(const QString& background)
    {
        if (backgroundAsString() == background)
            return false;
        if (const auto b = toBackground(background); b != Background_Custom)
            return setBackground(b);
        extra().insert(QStringLiteral("background"), background);
        return setBackground(Background_Custom);
    }
    bool setBackground(Background background)
    {
        if (mBackground == background)
            return false;
        mBackground = background;
        if (mBackground != Background_Custom)
            extra().remove(QStringLiteral("background"));
        return true;
    }
    bool resetBackground() { return setBackground(Background_Auto); }

    [[nodiscard]] Model model() const { return mModel; }
    [[nodiscard]] QString modelAsString() const
    {
        return mModel != Model_Custom ? toString(mModel)
                                      : extra().value(QStringLiteral("model")).toString();
    }
    bool setModel(const QString& model)
    {
        if (modelAsString() == model)
            return false;
        if (const auto m = toModel(model); m != Model_Custom)
            return setModel(m);
        extra().insert(QStringLiteral("model"), model);
        return setModel(Model_Custom);
    }
    bool setModel(Model model)
    {
        // if (mModel == model)
        //     return false;
        mModel = model;
        if (mModel != Model_Custom) {
            extra().remove(QStringLiteral("model"));
            switch (mModel) {
            case Model_GptImage1:
                setQuality(Quality_Auto);
                break;
            case Model_DallE2:
                setQuality(Quality_Standard);
                break;
            case Model_DallE3:
                setQuality(Quality_Standard);
                break;
            default:
                break;
            }
        }
        return true;
    }
    bool resetModel() { return setModel(Model_DallE2); }

    [[nodiscard]] Moderation moderation() const { return mModeration; }
    [[nodiscard]] QString moderationAsString() const
    {
        return mModeration != Moderation_Custom
                   ? toString(mModeration)
                   : mExtra.value(QStringLiteral("moderation")).toString();
    }
    bool setModeration(const QString& moderation)
    {
        if (moderationAsString() == moderation)
            return false;
        if (Moderation m = toModeration(moderation); m != Moderation_Custom)
            return setModeration(m);
        extra().insert(QStringLiteral("moderation"), moderation);
        return setModeration(Moderation_Custom);
    }
    bool setModeration(Moderation moderation)
    {
        if (mModeration == moderation)
            return false;
        mModeration = moderation;
        if (mModeration != Moderation_Custom)
            extra().remove(QStringLiteral("moderation"));
        return true;
    }
    bool resetModeration() { return setModeration(Moderation_Auto); }

    [[nodiscard]] int n() const { return mN; }
    bool setN(int n)
    {
        n = std::max(1, std::min(model() == Model_DallE3 ? 1 : 10, n));
        if (mN == n)
            return false;
        mN = n;
        return true;
    }
    void resetN() { setN(1); }

    [[nodiscard]] int outputCompression() const { return mOutputCompression; }
    bool setOutputCompression(int outputCompression)
    {
        outputCompression = std::max(0, std::min(100, outputCompression));
        if (mModel != Model_GptImage1 || mOutputCompression == outputCompression)
            return false;
        mOutputCompression = outputCompression;
        return true;
    }
    void resetOutputCompression() { setOutputCompression(0); }

    [[nodiscard]] OutputFormat outputFormat() const { return mOutputFormat; }
    [[nodiscard]] QString outputFormatAsString() const
    {
        return mOutputFormat != OutputFormat_Custom
                   ? toString(mOutputFormat)
                   : mExtra.value(QStringLiteral("outputFormat")).toString();
    }
    bool setOutputFormat(const QString& outputFormat)
    {
        if (outputFormatAsString() == outputFormat)
            return false;
        if (const auto f = toOutputFormat(outputFormat); f != OutputFormat_Custom)
            return setOutputFormat(f);
        extra().insert(QStringLiteral("output_format"), outputFormat);
        return setOutputFormat(OutputFormat_Custom);
    }
    bool setOutputFormat(OutputFormat outputFormat)
    {
        if (mOutputFormat == outputFormat)
            return false;
        mOutputFormat = outputFormat;
        if (mOutputFormat != OutputFormat_Custom)
            extra().remove(QStringLiteral("output_format"));
        return true;
    }
    bool resetOutputFormat() { return setOutputFormat(OutputFormat_Png); }

    [[nodiscard]] int partialImages() const { return mPartialImages; }
    bool setPartialImages(int partialImages)
    {
        partialImages = std::max(0, std::min(3, partialImages));
        if (mPartialImages == partialImages)
            return false;
        mPartialImages = partialImages;
        return true;
    }
    void resetPartialImages() { setPartialImages(0); }

    [[nodiscard]] Quality quality() const { return mQuality; }
    [[nodiscard]] QString qualityAsString() const
    {
        return mQuality != Quality_Custom ? toString(mQuality)
                                          : mExtra.value(QStringLiteral("quality")).toString();
    }
    bool setQuality(const QString& quality)
    {
        if (qualityAsString() == quality)
            return false;
        if (const auto q = toQuality(quality); q != Quality_Custom)
            return setQuality(q);
        extra().insert(QStringLiteral("quality"), quality);
        return setQuality(Quality_Custom);
    }
    bool setQuality(Quality quality)
    {
        if (mQuality == quality)
            return false;
        mQuality = quality;
        if (mQuality != Quality_Custom)
            extra().remove(QStringLiteral("quality"));
        return true;
    }
    bool resetQuality() { return setQuality(Quality_Auto); }

    [[nodiscard]] ResponseFormat responseFormat() const { return mResponseFormat; }
    [[nodiscard]] QString responseFormatAsString() const
    {
        return mResponseFormat != ResponseFormat_Custom
                   ? toString(mResponseFormat)
                   : mExtra.value(QStringLiteral("responseFormat")).toString();
    }
    bool setResponseFormat(const QString& responseFormat)
    {
        if (responseFormatAsString() == responseFormat)
            return false;
        if (const auto f = toResponseFormat(responseFormat); f != ResponseFormat_Custom)
            return setResponseFormat(f);
        extra().insert(QStringLiteral("response_format"), responseFormat);
        return setResponseFormat(ResponseFormat_Custom);
    }
    bool setResponseFormat(ResponseFormat responseFormat)
    {
        if (mResponseFormat == responseFormat)
            return false;
        mResponseFormat = responseFormat;
        if (mResponseFormat != ResponseFormat_Custom)
            extra().remove(QStringLiteral("response_format"));
        return true;
    }
    bool resetResponseFormat() { return setResponseFormat(ResponseFormat_Url); }

    [[nodiscard]] Size size() const { return mSize; }
    [[nodiscard]] QString sizeAsString() const
    {
        return mSize != Size_Custom ? toString(mSize)
                                    : mExtra.value(QStringLiteral("size")).toString();
    }
    bool setSize(const QString& size)
    {
        if (sizeAsString() == size)
            return false;
        if (const auto s = toSize(size); s != Size_Custom)
            return setSize(s);
        extra().insert(QStringLiteral("size"), size);
        return setSize(Size_Custom);
    }
    bool setSize(Size size)
    {
        if (mSize == size)
            return false;
        mSize = size;
        if (mSize != Size_Custom)
            extra().remove(QStringLiteral("size"));
        return true;
    }
    bool resetSize() { return setSize(Size_Auto); }

    [[nodiscard]] bool isStreaming() const { return mStream; }
    bool setStreaming(bool streaming)
    {
        if (mStream == streaming)
            return false;
        mStream = streaming;
        return true;
    }
    void resetStreaming() { setStreaming(false); }

    [[nodiscard]] Style style() const { return mStyle; }
    [[nodiscard]] QString styleAsString() const
    {
        return mStyle != Style_Custom ? toString(mStyle)
                                      : mExtra.value(QStringLiteral("style")).toString();
    }
    bool setStyle(const QString& style)
    {
        if (styleAsString() == style)
            return false;
        if (const auto s = toStyle(style); s != Style_Custom)
            return setStyle(s);
        extra().insert(QStringLiteral("style"), style);
        return setStyle(Style_Custom);
    }
    bool setStyle(Style style)
    {
        if (mStyle == style)
            return false;
        mStyle = style;
        if (mStyle != Style_Custom)
            extra().remove(QStringLiteral("style"));
        return true;
    }
    bool resetStyle() { return setStyle(Style_Vivid); }

    [[nodiscard]] QString user() const { return mUser; }
    bool setUser(const QString& user)
    {
        if (mUser == user)
            return false;
        mUser = user;
        return true;
    }
    void resetUser() { setUser({}); }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;

    inline static const QMap<Background, QString> BackgroundKV = {{Background_Auto, "auto"},
                                                                  {Background_Transparent,
                                                                   "transparent"},
                                                                  {Background_Opaque, "opaque"}};
    inline static const QMap<Model, QString> ModelKV = {{Model_DallE2, "dall-e-2"},
                                                        {Model_DallE3, "dall-e-3"},
                                                        {Model_GptImage1, "gpt-image-1"}};
    inline static const QMap<Moderation, QString> ModerationKV = {{Moderation_Auto, "auto"},
                                                                  {Moderation_Low, "low"}};
    inline static const QMap<OutputFormat, QString> OutputFormatKV = {{OutputFormat_Png, "png"},
                                                                      {OutputFormat_Jpeg, "jpeg"},
                                                                      {OutputFormat_Webp, "webp"}};
    inline static const QMap<Quality, QString> QualityKV = {{Quality_Auto, "auto"},
                                                            {Quality_Low, "low"},
                                                            {Quality_Medium, "medium"},
                                                            {Quality_High, "high"},
                                                            {Quality_Hd, "hd"},
                                                            {Quality_Standard, "standard"}};
    inline static const QMap<ResponseFormat, QString> ResponseFormatKV
        = {{ResponseFormat_Url, "url"}, {ResponseFormat_B64Json, "b64_json"}};
    inline static const QMap<Size, QString> SizeKV = {{Size_Auto, "auto"},
                                                      {Size_256x256, "256x256"},
                                                      {Size_512x512, "512x512"},
                                                      {Size_1024x1024, "1024x1024"},
                                                      {Size_1024x1536, "1024x1536"},
                                                      {Size_1024x1792, "1024x1792"},
                                                      {Size_1536x1024, "1536x1024"},
                                                      {Size_1792x1024, "1792x1024"}};
    inline static const QMap<Style, QString> StyleKV = {{Style_Vivid, "vivid"},
                                                        {Style_Natural, "natural"}};

    QString mPrompt;
    Size mSize = Size_Auto;
    Style mStyle = Style_Vivid;
    QString mUser;
    int mN = 1;
    int mOutputCompression = 0;
    int mPartialImages = 0;
    Background mBackground = Background_Auto;
    Model mModel = Model_DallE2;
    Moderation mModeration = Moderation_Auto;
    OutputFormat mOutputFormat = OutputFormat_Png;
    Quality mQuality = Quality_Auto;
    ResponseFormat mResponseFormat = ResponseFormat_Url;
    bool mStream = false;
};

} // namespace ai

#endif // LIBAI_IMAGESREQUEST_H
