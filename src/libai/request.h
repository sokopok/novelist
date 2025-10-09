#ifndef AI_REQUEST_H
#define AI_REQUEST_H

#include <QNetworkReply>
#include <QObject>
#include "config.h"

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

namespace ai {

class Client;
class Response;
class RequestData;

class Request : public QNetworkRequest
{
    Q_GADGET

public:
    enum Attribute {
        IdAttribute,
        ApiKeyAttribute,
        UrlAttribute,
        MetadataAttribute,
        ModelAttribute,
        StreamingAttribute,
        StreamOptionsAttribute,
        NumAttributes
    };
    Q_ENUM(Attribute)

    enum ExplicitHandling { LeaveExplicit, SetExplicit, ClearExplicit };
    Q_ENUM(ExplicitHandling)

    enum Error { NoError, NetworkError, SslError };
    Q_ENUM(Error)

    enum Model {
        NoModel,
        UnknownModel,
        Gpt5Model,
        Gpt5NanoModel,
        Gpt5MiniModel,
        Gpt5ProModel,
        Gpt41Model,
        Gpt41MiniModel,
    };
    Q_ENUM(Model)

protected:
    QSharedDataPointer<RequestData> d;
    QMap<int, QVariant> mAttributes;
    ExplicitHandling mExplicitHandling = LeaveExplicit;
    inline static const QMap<Model, QString> ModelKV = {
  {NoModel,""},{UnknownModel,""},{Gpt5Model, "gpt-5"},{Gpt5NanoModel, "gpt-5-nano"}, {Gpt5MiniModel,"gpt-5-mini"},{Gpt5ProModel,"gpt-5-pro"},{Gpt41Model, "gpt-4.1"},{Gpt41MiniModel,  "gpt-4.1-mini"},
    };

public:
    Request();

    [[nodiscard]] QVariant attribute(Attribute code) const;
    Request& setAttribute(Attribute code, const QVariant& value);

    Request& setAttribute(QNetworkRequest::Attribute code, const QVariant& value);
    Request& setDecompressedSafetyCheckThreshold(qint64 threshold);
    Request& setHeader(QNetworkRequest::KnownHeaders header, const QVariant& value);
    Request& setHeaders(QHttpHeaders&& newHeaders);
    Request& setHeaders(const QHttpHeaders& newHeaders);
    Request& setHttp1Configuration(const QHttp1Configuration& configuration);
    Request& setHttp2Configuration(const QHttp2Configuration& configuration);
    Request& setMaximumRedirectsAllowed(int maxRedirectsAllowed);
    Request& setOriginatingObject(QObject* object);
    Request& setPeerVerifyName(const QString& peerName);
    Request& setPriority(QNetworkRequest::Priority priority);
    Request& setRawHeader(const QByteArray& headerName, const QByteArray& headerValue);
    Request& setSslConfiguration(const QSslConfiguration& config);
    Request& setTransferTimeout(int timeout);
    Request& setTransferTimeout(std::chrono::milliseconds duration = DefaultTransferTimeout);
    Request& setUrl(const QUrl& url);
    Request& resetUrl();

    [[nodiscard]] QString id() const;
    Request& setId(const QString& id);

    [[nodiscard]] QByteArray apiKey() const;
    Request& setApiKey(const QByteArray& apiKey);
    Request& resetApiKey();

    [[nodiscard]] QVariantMap metadata() const;
    Request& setMetadata(const QVariantMap& metadata);
    Request& resetMetadata();

    bool putMetadata(const QString& key, const QVariant& value);
    bool putMetadata(const QVariantMap& map);
    QVariant takeMetadata(const QString& key);

    [[nodiscard]] QString model() const;
    Request& setModel(const QString& model);
    Request& setModel(Model model);
    Request& resetModel();

    [[nodiscard]] bool isStreaming() const;
    Request& setStreaming(bool streaming);
    Request& resetStreaming();

    [[nodiscard]] StreamOptions streamOptions() const;
    Request& setStreamOptions(const StreamOptions& streamOptions);
    Request& resetStreamOptions();

    QJsonObject toJson(bool full = false) const;
    QString formattedJson(bool full = false) const;

    [[nodiscard]] ExplicitHandling explicitHandling() const { return mExplicitHandling; }
    Request& setExplicitHandling(const ExplicitHandling& explicitHandling)
    {
        mExplicitHandling = explicitHandling;
        return *this;
    }
    Request& resetExplicitHandling() { return setExplicitHandling(LeaveExplicit); }

    static Model toModel(const QString& model)
    {
        return Model(ModelKV.key(model, Model::UnknownModel));
    }
    static Model toModel(int model)
    {
        const auto metaEnum = QMetaEnum::fromType<Model>();
        for (int i = 0; i < metaEnum.keyCount(); ++i)
            if (metaEnum.value(i) == model)
                return Model(i);
        return Model::UnknownModel;
    }
    static QString toString(Model model) { return ModelKV.value(model, QString::number(model)); }
    static int toInt(Model model) { return std::to_underlying(model); }

protected:
    Request(RequestData* data);

    virtual bool readJson(const QJsonObject& json, QStringList* errors = nullptr);
    virtual bool writeJson(QJsonObject& json, bool full = false) const;

    [[nodiscard]] bool isExplicit(int attribute) const;

    friend class Client;
};

class RequestData : public QSharedData
{
    StreamOptions mStreamOptions;
    QVariantMap mMetadata;
    QString mModelName;
    Request::Model mModel = Request::NoModel;
    QString mId;
    QByteArray mApiKey;
    bool mStreaming = false;
    QJsonObject mExtra;
    QBitArray mExplicits{32};

public:
    [[nodiscard]] bool operator==(const RequestData& that) const
    {
        return apiKey() == that.apiKey() && metadata() == that.metadata() && model() == that.model()
               && isStreaming() == that.isStreaming() && streamOptions() == that.streamOptions();
    }

    [[nodiscard]] QString id() const { return mId; }
    bool setId(const QString& id)
    {
        if (mId == id)
            return false;
        mId = id;
        return true;
    }

    /** metadata
        map
        Optional
        Set of 16 key-value pairs that can be attached to an object. This can be useful for storing additional information about the object in a structured format, and querying for objects via API or the dashboard.
        Keys are strings with a maximum length of 64 characters. Values are strings with a maximum length of 512 characters.
    */
    [[nodiscard]] QVariantMap metadata() const { return mMetadata; }
    bool setMetadata(const QVariantMap& metadata,
                     Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::MetadataAttribute, explicitHandling);

        if (mMetadata == metadata)
            return false;
        mMetadata = metadata;
        return true;
    }
    void resetMetadata(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setMetadata({}, explicitHandling);
    }

    [[nodiscard]] QVariant metadata(const QString& key) const { return mMetadata.value(key); }
    bool putMetadata(const QString& key,
                     const QVariant& value,
                     Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::MetadataAttribute, explicitHandling);

        if (key.isEmpty())
            return false;
        mMetadata[key] = value;
        return true;
    }
    QVariant takeMetadata(const QString& key,
                          Request::ExplicitHandling explicitHandling = Request::LeaveExplicit)
    {
        updateExplicit(Request::MetadataAttribute, explicitHandling);

        return mMetadata.take(key);
    }

    /** model
        string
        Optional
        Model ID used to generate the response, like gpt-4o or o3. OpenAI offers a wide range of models with different capabilities, performance characteristics, and price points. Refer to the model guide to browse and compare available models.
    */
    [[nodiscard]] QString model() const { return mModelName; }
    bool setModel(const QString& model,
                  Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ModelAttribute, explicitHandling);

        if (mModelName == model)
            return false;
        mModelName = model;
        return setModel(Request::toModel(model));
    }
    bool setModel(Request::Model model,
                  Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ModelAttribute, explicitHandling);

        if (mModel == model)
            return false;
        mModel = model;
        if (model != Request::UnknownModel)
            mModelName = Request::toString(model);
        return true;
    }
    void resetModel(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setModel(Request::Gpt5Model, Request::SetExplicit);
    }

    /** stream
        boolean
        Optional
        Defaults to false
        If set to true, the model response data will be streamed to the client as it is generated using server-sent events. See the Streaming section below for more information.
    */
    [[nodiscard]] bool isStreaming() const { return mStreaming; }
    bool setStreaming(bool streaming,
                      Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::StreamingAttribute, explicitHandling);

        if (mStreaming == streaming)
            return false;
        mStreaming = streaming;
        return true;
    }
    void resetStreaming(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setStreaming(false, explicitHandling);
    }

    /** stream_options
        object
        Optional
        Defaults to null
        Options for streaming responses. Only set this when you set stream: true.
    */
    [[nodiscard]] StreamOptions streamOptions() const { return mStreamOptions; }
    bool setStreamOptions(const StreamOptions& streamOptions,
                          Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::StreamOptionsAttribute, explicitHandling);

        if (mStreamOptions == streamOptions)
            return false;
        mStreamOptions = streamOptions;
        return true;
    }
    void resetStreamOptions(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setStreamOptions({}, explicitHandling);
    }

    [[nodiscard]] QByteArray apiKey() const { return mApiKey; }
    bool setApiKey(const QByteArray& apiKey,
                   Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        updateExplicit(Request::ApiKeyAttribute, explicitHandling);

        if (mApiKey == apiKey)
            return false;
        mApiKey = apiKey;
        return true;
    }
    void resetApiKey(Request::ExplicitHandling explicitHandling = Request::ClearExplicit)
    {
        setApiKey({}, explicitHandling);
    }

    [[nodiscard]] QJsonObject extra() const { return mExtra; }
    bool setExtra(const QJsonObject& extra)
    {
        if (mExtra == extra)
            return false;
        mExtra = extra;
        return true;
    }
    bool resetExtra() { return setExtra({}); }

    [[nodiscard]] QBitArray explicits() const { return mExplicits; }
    bool setExplicits(const QBitArray& explicits)
    {
        if (mExplicits == explicits)
            return false;
        mExplicits = explicits;
        return true;
    }
    bool resetExplicits() { return setExplicits({}); }

    QJsonObject toJson(bool full = false) const
    {
        QJsonObject json;
        return writeJson(json, full) ? json : QJsonObject{};
    }

    virtual bool readJson(const QJsonObject& json, QStringList* errors = nullptr);
    virtual bool writeJson(QJsonObject& json, bool full = false) const;

    [[nodiscard]] QJsonObject& extra() { return mExtra; }
    [[nodiscard]] QBitArray& explicits() { return mExplicits; }

    [[nodiscard]] bool isExplicit(int attribute) const { return mExplicits.testBit(attribute); }
    void updateExplicit(int attribute,
                        Request::ExplicitHandling explicitHandling = Request::SetExplicit)
    {
        switch (explicitHandling) {
        case Request::SetExplicit:
            explicits().setBit(attribute);
            break;
        case Request::ClearExplicit:
            explicits().clearBit(attribute);
            break;
        default:
            break;
        }
    }
};

} // namespace ai

#endif // AI_REQUEST_H
