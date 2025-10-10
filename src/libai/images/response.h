#ifndef AI_IMAGES_RESPONSE_H
#define AI_IMAGES_RESPONSE_H

#include "../response.h"
#include "request.h"

namespace ai::images {

class Client;

class ImageResponseData
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(QString b64Json READ b64Json WRITE setB64Json FINAL)
    Q_PROPERTY(QString revisedPrompt READ revisedPrompt WRITE setRevisedPrompt FINAL)
    Q_PROPERTY(QString url READ url WRITE setUrl FINAL)

    QString j;
    QString p;
    QString u;
    QJsonObject e;

public:
    ImageResponseData(const QJsonObject& extra = {})
        : e{extra}
    {}
    ImageResponseData(const QString& b64Json,
                      const QString& revisedPrompt = {},
                      const QString& url = {},
                      const QJsonObject& extra = {})
        : j{b64Json}
        , p{revisedPrompt}
        , u{url}
        , e{extra}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_ImageResponseData; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString b64Json() const { return j; }
    ImageResponseData& setB64Json(const QString& b64Json)
    {
        j = b64Json;
        return *this;
    }

    [[nodiscard]] QString revisedPrompt() const { return p; }
    ImageResponseData& setRevisedPrompt(const QString& revisedPrompt)
    {
        p = revisedPrompt;
        return *this;
    }

    [[nodiscard]] QString url() const { return u; }
    ImageResponseData& setUrl(const QString& url)
    {
        u = url;
        return *this;
    }

    [[nodiscard]] bool operator==(const ImageResponseData& that) const
    {
        return j == that.j && p == that.p && u == that.u;
    }

    [[nodiscard]] bool isEmpty() const { return j.isEmpty() && p.isEmpty() && u.isEmpty(); }
    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        if (!j.isEmpty())
            json.insert(QStringLiteral("b64_json"), j);

        if (!p.isEmpty())
            json.insert(QStringLiteral("revised_prompt"), p);

        if (!u.isEmpty())
            json.insert(QStringLiteral("url"), u);

        return json;
    }

    static ImageResponseData fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        // if (json.value(QStringLiteral("type")).toString() != QStringLiteral("error")) {
        //     if (ok)
        //         *ok = false;
        //     return {};
        // }

        QJsonObject x = json;
        // extra.remove(QStringLiteral("type"));

        QString j;
        QString p;
        QString u;

        if (json.contains(QStringLiteral("b64_json"))) {
            if (const auto v = json.value(QStringLiteral("b64_json")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                j = v.toString();
                x.remove(QStringLiteral("b64_json"));
            }
        }

        if (json.contains(QStringLiteral("revised_prompt"))) {
            if (const auto v = json.value(QStringLiteral("revised_prompt")); v.isString()) {
                p = v.toString();
                x.remove(QStringLiteral("revised_prompt"));
            } else if (ok)
                *ok = false;
        }

        if (json.contains(QStringLiteral("url"))) {
            if (const auto v = json.value(QStringLiteral("url")); v.isString()) {
                u = v.toString();
                x.remove(QStringLiteral("url"));
            } else if (ok)
                *ok = false;
        }

        return {j, p, u, x};
    }
};

class ImageResponseUsage
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(int inputTokens READ inputTokens WRITE setInputTokens FINAL)
    Q_PROPERTY(int imageTokens READ imageTokens WRITE setImageTokens FINAL)
    Q_PROPERTY(int textTokens READ textTokens WRITE setTextTokens FINAL)
    Q_PROPERTY(int outputTokens READ outputTokens WRITE setOutputTokens FINAL)
    Q_PROPERTY(int totalTokens READ totalTokens WRITE setTotalTokens FINAL)

    int in_t = 0;
    int im_t = 0;
    int te_t = 0;
    int ou_t = 0;
    int to_t = 0;
    QJsonObject e;

public:
    ImageResponseUsage(const QJsonObject& extra = {})
        : e{extra}
    {}
    ImageResponseUsage(int imageTokens,
                       int textTokens = 0,
                       int outputTokens = 0,
                       const QJsonObject& extra = {})
        : in_t{imageTokens + textTokens}
        , im_t{imageTokens}
        , te_t{textTokens}
        , ou_t{outputTokens}
        , to_t{imageTokens + textTokens + outputTokens}
        , e{extra}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_ImageResponseUsage; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] int inputTokens() const { return in_t; }
    ImageResponseUsage& setInputTokens(int inputTokens)
    {
        in_t = inputTokens;
        return *this;
    }

    [[nodiscard]] int imageTokens() const { return im_t; }
    ImageResponseUsage& setImageTokens(int imageTokens)
    {
        im_t = imageTokens;
        return *this;
    }

    [[nodiscard]] int textTokens() const { return te_t; }
    ImageResponseUsage& setTextTokens(int textTokens)
    {
        te_t = textTokens;
        return *this;
    }

    [[nodiscard]] int outputTokens() const { return ou_t; }
    ImageResponseUsage& setOutputTokens(int outputTokens)
    {
        ou_t = outputTokens;
        return *this;
    }

    [[nodiscard]] int totalTokens() const { return to_t; }
    ImageResponseUsage& setTotalTokens(int totalTokens)
    {
        to_t = totalTokens;
        return *this;
    }

    [[nodiscard]] bool operator==(const ImageResponseUsage& that) const
    {
        return in_t == that.in_t
               && im_t == that.im_t
               && te_t == that.te_t
               && ou_t == that.ou_t
               && to_t == that.to_t;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return in_t == 0 && im_t == 0 && te_t == 0 && ou_t == 0 && to_t == 0;
    }
    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        json.insert(QStringLiteral("input_tokens"), in_t);

        QJsonObject itd;
        itd[QStringLiteral("image_tokens")] = im_t;
        itd[QStringLiteral("text_tokens")] = te_t;
        json.insert(QStringLiteral("input_token_details"), itd);

        json.insert(QStringLiteral("output_tokens"), ou_t);
        json.insert(QStringLiteral("total_tokens"), to_t);

        return json;
    }

    static ImageResponseUsage fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        // if (json.value(QStringLiteral("type")).toString() != QStringLiteral("error")) {
        //     if (ok)
        //         *ok = false;
        //     return {};
        // }

        QJsonObject x = json;
        // extra.remove(QStringLiteral("type"));

        ImageResponseUsage u;

        if (json.contains(QStringLiteral("input_tokens"))) {
            if (const auto v = json.value(QStringLiteral("input_tokens")); !v.isDouble()) {
                if (ok)
                    *ok = false;
            } else {
                u.setInputTokens(v.toInt());
                x.remove(QStringLiteral("input_tokens"));
            }
        }

        if (json.contains(QStringLiteral("input_token_details"))) {
            if (const auto v = json.value(QStringLiteral("input_token_details")); v.isObject()) {
                const auto d = v.toObject();
                if (const auto v = d.value(QStringLiteral("image_tokens")); v.isDouble())
                    u.setImageTokens(v.toInt());
                if (const auto v = d.value(QStringLiteral("text_tokens")); v.isDouble())
                    u.setTextTokens(v.toInt());
                x.remove(QStringLiteral("input_token_details"));
            }
        }

        if (json.contains(QStringLiteral("output_tokens"))) {
            if (const auto v = json.value(QStringLiteral("output_tokens")); !v.isDouble()) {
                if (ok)
                    *ok = false;
            } else {
                u.setOutputTokens(v.toInt());
                x.remove(QStringLiteral("output_tokens"));
            }
        }

        if (json.contains(QStringLiteral("total_tokens"))) {
            if (const auto v = json.value(QStringLiteral("total_tokens")); !v.isDouble()) {
                if (ok)
                    *ok = false;
            } else {
                u.setTotalTokens(v.toInt());
                x.remove(QStringLiteral("total_tokens"));
            }
        }

        return u;
    }
};

class Response : public ai::Response
{
    Q_OBJECT

public:
    [[nodiscard]] Client* client() const;
    [[nodiscard]] const Request& request() const { return mRequest; }

    [[nodiscard]] Request::Background background() const { return mBackground; }
    [[nodiscard]] QString backgroundAsString() const
    {
        return mBackground != Request::Background_Custom
                   ? Request::toString(mBackground)
                   : mExtra.value(QStringLiteral("background")).toString();
    }
    bool setBackground(const QString& background)
    {
        if (backgroundAsString() == background)
            return false;
        if (const auto b = Request::toBackground(background); b != Request::Background_Custom)
            return setBackground(b);
        extra().insert(QStringLiteral("background"), background);
        return setBackground(Request::Background_Custom);
    }
    bool setBackground(Request::Background background)
    {
        if (mBackground == background)
            return false;
        mBackground = background;
        if (mBackground != Request::Background_Custom)
            extra().remove(QStringLiteral("background"));
        return true;
    }
    bool resetBackground() { return setBackground(Request::Background_Auto); }

    [[nodiscard]] int created() const { return mCreated; }
    bool setCreated(int created)
    {
        if (mCreated == created)
            return false;
        mCreated = created;
        return true;
    }
    bool resetCreated() { return setCreated(0); }

    [[nodiscard]] ImageResponseData data() const { return mData; }
    bool setData(const ImageResponseData& data)
    {
        if (mData == data)
            return false;
        mData = data;
        return true;
    }
    bool resetData() { return setData({}); }

    [[nodiscard]] Request::OutputFormat outputFormat() const { return mOutputFormat; }
    [[nodiscard]] QString outputFormatAsString() const
    {
        return mOutputFormat != Request::OutputFormat_Custom
                   ? Request::toString(mOutputFormat)
                   : mExtra.value(QStringLiteral("outputFormat")).toString();
    }
    bool setOutputFormat(const QString& outputFormat)
    {
        if (outputFormatAsString() == outputFormat)
            return false;
        if (const auto f = Request::toOutputFormat(outputFormat); f != Request::OutputFormat_Custom)
            return setOutputFormat(f);
        extra().insert(QStringLiteral("output_format"), outputFormat);
        return setOutputFormat(Request::OutputFormat_Custom);
    }
    bool setOutputFormat(Request::OutputFormat outputFormat)
    {
        if (mOutputFormat == outputFormat)
            return false;
        mOutputFormat = outputFormat;
        if (mOutputFormat != Request::OutputFormat_Custom)
            extra().remove(QStringLiteral("output_format"));
        return true;
    }
    bool resetOutputFormat() { return setOutputFormat(Request::OutputFormat_Png); }

    [[nodiscard]] Request::Quality quality() const { return mQuality; }
    [[nodiscard]] QString qualityAsString() const
    {
        return mQuality != Request::Quality_Custom
                   ? Request::toString(mQuality)
                   : mExtra.value(QStringLiteral("quality")).toString();
    }
    bool setQuality(const QString& quality)
    {
        if (qualityAsString() == quality)
            return false;
        if (const auto q = Request::toQuality(quality); q != Request::Quality_Custom)
            return setQuality(q);
        extra().insert(QStringLiteral("quality"), quality);
        return setQuality(Request::Quality_Custom);
    }
    bool setQuality(Request::Quality quality)
    {
        if (mQuality == quality)
            return false;
        mQuality = quality;
        if (mQuality != Request::Quality_Custom)
            extra().remove(QStringLiteral("quality"));
        return true;
    }
    bool resetQuality() { return setQuality(Request::Quality_Auto); }

    [[nodiscard]] Request::Size size() const { return mSize; }
    [[nodiscard]] QString sizeAsString() const
    {
        return mSize != Request::Size_Custom ? Request::toString(mSize)
                                             : mExtra.value(QStringLiteral("size")).toString();
    }
    bool setSize(const QString& size)
    {
        if (sizeAsString() == size)
            return false;
        if (const auto s = Request::toSize(size); s != Request::Size_Custom)
            return setSize(s);
        extra().insert(QStringLiteral("size"), size);
        return setSize(Request::Size_Custom);
    }
    bool setSize(Request::Size size)
    {
        if (mSize == size)
            return false;
        mSize = size;
        if (mSize != Request::Size_Custom)
            extra().remove(QStringLiteral("size"));
        return true;
    }
    bool resetSize() { return setSize(Request::Size_Auto); }

    [[nodiscard]] ImageResponseUsage usage() const { return mUsage; }
    bool setUsage(const ImageResponseUsage& usage)
    {
        if (mUsage == usage)
            return false;
        mUsage = usage;
        return true;
    }
    bool resetUsage() { return setUsage({}); }

protected:
    Response(const Request& request, QNetworkReply* reply, Client* client);

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override;
    bool writeJson(QJsonObject& json, bool full = false) const override;

    Request mRequest;
    Request::Background mBackground;
    int mCreated = 0;
    ImageResponseData mData;
    Request::OutputFormat mOutputFormat;
    Request::Quality mQuality;
    Request::Size mSize;
    ImageResponseUsage mUsage;

    friend class Client;
};

} // namespace ai::images

#endif // AI_IMAGES_RESPONSE_H
