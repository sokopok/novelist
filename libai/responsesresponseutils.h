#ifndef LIBAI_RESPONSESRESPONSEUTILS_H
#define LIBAI_RESPONSESRESPONSEUTILS_H

#include <QImage>
#include <QJsonArray>
#include <QJsonObject>

#include "responsesrequestutils.h"

namespace ai {

class ReasoningOutput : public Base
{
    Q_GADGET
    Q_PROPERTY(Status status READ status WRITE setStatus)
    Q_PROPERTY(QString statusAsString READ statusAsString WRITE setStatus)

public:
    enum Status { Status_InProgress, Status_Incomplete, Status_Completed, Status_Custom };
    Q_ENUM(Status)

private:
    Status mStatus;
    QString mCustomStatus;
    QString mId;
    QStringList mSummary;
    QStringList mContent;
    QString mEncryptedContent;

    inline static const QMap<Status, QString> StatusKV = {{Status_InProgress, "in_progress"},
                                                          {Status_Incomplete, "incomplete"},
                                                          {Status_Completed, "completed"}};

public:
    ReasoningOutput(const QJsonObject& extra = {})
        : ReasoningOutput{Status_Completed, extra}
    {}
    ReasoningOutput(Status effort, const QJsonObject& extra = {})
        : Base(extra)
        , mStatus(effort)
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override
    {
        return UtilityType_ReasoningOutput;
    }

    [[nodiscard]] Status status() const { return mStatus; }
    void setStatus(Status status)
    {
        mStatus = status;
        if (mStatus < Status_Custom)
            mCustomStatus.clear();
    }
    [[nodiscard]] QString statusAsString() const
    {
        return mStatus < Status_Custom ? statusToString(mStatus) : mCustomStatus;
    }
    void setStatus(const QString& status)
    {
        mStatus = stringToStatus(status);
        if (mStatus >= Status_Custom)
            mCustomStatus = status;
    }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] QStringList summary() const { return mSummary; }
    void setSummary(const QStringList& summary) { mSummary = summary; }

    [[nodiscard]] QStringList content() const { return mContent; }
    void setContent(const QStringList& content) { mContent = content; }

    [[nodiscard]] QString encryptedContent() const { return mEncryptedContent; }
    void setEncryptedContent(const QString& encryptedContent)
    {
        mEncryptedContent = encryptedContent;
    }

    [[nodiscard]] bool operator==(const ReasoningOutput& that) const
    {
        return mStatus == that.mStatus && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return mStatus == Status_Custom && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override { return mStatus != Status_Custom; }

    static Status stringToStatus(const QString& effort)
    {
        return StatusKV.key(effort, Status_Custom);
    }
    static QString statusToString(Status status) { return StatusKV.value(status); }

    static ReasoningOutput fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        ReasoningOutput reasoning;
        reasoning.readJson(json, errors);
        return reasoning;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        if (const auto v = statusAsString(); !v.isEmpty())
            json.insert(QStringLiteral("status"), v);

        if (!mId.isEmpty())
            json.insert(QStringLiteral("id"), mId);

        if (!mEncryptedContent.isEmpty())
            json.insert(QStringLiteral("encrypted_content"), mEncryptedContent);

        if (!mSummary.isEmpty()) {
            QJsonArray a;
            for (const auto& s : mSummary)
                a.append(QJsonObject{{{"type", "summary_text"}, {"text", s}}});
            json.insert(QStringLiteral("summary"), a);
        }

        if (!mContent.isEmpty()) {
            QJsonArray a;
            for (const auto& c : mContent)
                a.append(QJsonObject{{{"type", "reasoning_text"}, {"text", c}}});
            json.insert(QStringLiteral("content"), a);
        }

        json.insert(QStringLiteral("type"), QStringLiteral("reasoning"));

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v != QStringLiteral("reasoning")) {
            if (errors)
                errors->append(
                    QStringLiteral("Reasoning::readJson: not a 'reasoning': '%1'").arg(v));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (json.contains(QStringLiteral("status"))) {
            if (const auto v = json.value(QStringLiteral("status")); v.isString()) {
                setStatus(v.toString());
                extra().remove(QStringLiteral("status"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); v.isString()) {
                setId(v.toString());
                extra().remove(QStringLiteral("id"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        if (json.contains(QStringLiteral("encrypted_content"))) {
            if (const auto v = json.value(QStringLiteral("encrypted_content")); v.isString()) {
                setEncryptedContent(v.toString());
                extra().remove(QStringLiteral("encrypted_content"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        if (json.contains(QStringLiteral("summary"))) {
            if (const auto v = json.value(QStringLiteral("summary")); v.isArray()) {
                QStringList s;
                const auto a = v.toArray();
                for (const auto o : a)
                    s.append(o.toObject().value("text").toString());
                setSummary(s);
                extra().remove(QStringLiteral("summary"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        if (json.contains(QStringLiteral("content"))) {
            if (const auto v = json.value(QStringLiteral("content")); v.isArray()) {
                QStringList s;
                const auto a = v.toArray();
                for (const auto o : a)
                    s.append(o.toObject().value("text").toString());
                setContent(s);
                extra().remove(QStringLiteral("content"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        return true;
    }
};

class ImageGenerationCall : public Base
{
    Q_GADGET
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(Status status READ status WRITE setStatus FINAL)
    Q_PROPERTY(QImage result READ result WRITE setResult FINAL)

public:
    enum Status { Status_Custom };
    Q_ENUM(Status)

    [[nodiscard]] static QString statusToString(Status status) { return StatusKV.value(status); }
    [[nodiscard]] static Status stringToStatus(const QString& status)
    {
        return StatusKV.key(status, Status_Custom);
    }

    ImageGenerationCall(const QJsonObject& extra = {})
        : ImageGenerationCall{{}, {}, {}, extra}
    {}
    ImageGenerationCall(const QString& id,
                        const QString& status,
                        const QImage& result,
                        const QJsonObject& extra = {})
        : Base{extra}
        , mId{id}
        , mCustomStatus{status}
        , mResult{result}
        , mStatus{Status_Custom}
    {}
    ImageGenerationCall(const QString& id,
                        Status status,
                        const QImage& result,
                        const QJsonObject& extra = {})
        : Base{extra}
        , mId{id}
        , mResult{result}
        , mStatus{status}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override
    {
        return UtilityType_ImageGenerationCall;
    }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] QImage result() const { return mResult; }
    void setResult(const QImage& result) { mResult = result; }

    [[nodiscard]] Status status() const { return mStatus; }
    void setStatus(Status status)
    {
        mStatus = status;
        mCustomStatus.clear();
    }
    [[nodiscard]] QString statusAsString() const { return mCustomStatus; }
    void setStatus(const QString& status)
    {
        setStatus(stringToStatus(status));
        if (mStatus >= Status_Custom)
            mCustomStatus = status;
    }

    [[nodiscard]] bool operator==(const ImageGenerationCall& that) const
    {
        return mId == that.mId && mStatus == that.mStatus && mResult == that.mResult
               && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return mId.isEmpty() && mStatus == Status_Custom && mCustomStatus.isEmpty()
               && mResult.isNull() && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override { return !mId.isEmpty(); }

    static ImageGenerationCall fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        ImageGenerationCall call;
        call.readJson(json, errors);
        return call;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (extra().value(QStringLiteral("type")) != QStringLiteral("image_generation_call")) {
            if (errors)
                errors->append(QStringLiteral(
                    "ImageGenerationCall::readJson: not an 'image_generation_call'"));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
            if (errors)
                errors->append(
                    QStringLiteral("ImageGenerationCall::readJson: 'id' is not a string"));
            return false;
        } else {
            setId(v.toString());
            extra().remove(QStringLiteral("id"));
        }

        if (const auto v = json.value(QStringLiteral("result")); !v.isString()) {
            if (errors)
                errors->append(
                    QStringLiteral("ImageGenerationCall::readJson: 'result' is not a string"));
            return false;
        } else {
            const auto decoded = QByteArray::fromBase64(v.toVariant().toByteArray());
            setResult(QImage::fromData(decoded));
            extra().remove(QStringLiteral("result"));
        }

        if (const auto v = json.value(QStringLiteral("status")); !v.isString()) {
            if (errors)
                errors->append(
                    QStringLiteral("ImageGenerationCall::readJson: 'status' is not a string"));
            return false;
        } else {
            setStatus(v.toString());
            extra().remove(QStringLiteral("status"));
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("image_generation_call"));
        if (!mId.isEmpty())
            json.insert(QStringLiteral("id"), mId);
        if (!mResult.isNull())
            json.insert(QStringLiteral("result"),
                        QString{QByteArray{mResult.constBits()}.toBase64()});
        if (const auto v = statusAsString(); !v.isEmpty())
            json.insert(QStringLiteral("status"), v);

        return true;
    }

private:
    QString mId;
    QString mCustomStatus;
    QImage mResult;
    Status mStatus = Status_Custom;

    inline static const QMap<Status, QString> StatusKV = {};
};

class OutputText : public Base
{
    Q_GADGET
    Q_PROPERTY(QString text READ text WRITE setText FINAL)

    // annotations and logprobs!!!

    QString mText;

public:
    OutputText(const QJsonObject& extra = {})
        : Base{extra}
    {}
    OutputText(const QString& text, const QJsonObject& extra = {})
        : Base{extra}
        , mText{text}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_OutputText; }

    [[nodiscard]] QString text() const { return mText; }
    void setText(const QString& text) { mText = text; }

    [[nodiscard]] bool operator==(const OutputText& that) const
    {
        return mText == that.mText && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mText.isEmpty() && Base::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mText.isEmpty(); }

    static OutputText fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        OutputText text;
        text.readJson(json, errors);
        return text;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (extra().value(QStringLiteral("type")) != QStringLiteral("output_text")) {
            if (errors)
                errors->append(QStringLiteral("OutputText::readJson: not an 'output_text'"));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (const auto v = json.value(QStringLiteral("text")); !v.isString()) {
            if (errors)
                errors->append(QStringLiteral("OutputText::readJson: 'text' is not a string"));
            return false;
        } else {
            setText(v.toString());
            extra().remove(QStringLiteral("text"));
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("output_text"));
        if (!mText.isEmpty())
            json.insert(QStringLiteral("text"), mText);

        return true;
    }
};

class OutputMessageContent : public Base
{
    Q_GADGET
    Q_PROPERTY(OutputText text READ text WRITE setText FINAL)
    Q_PROPERTY(Refusal refusal READ refusal WRITE setRefusal FINAL)

    using Variant = std::variant<OutputText, Refusal>;
    Variant mVariant;

public:
    OutputMessageContent(const QJsonObject& extra = {})
        : Base{extra}
    {}
    OutputMessageContent(const OutputText& text, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{text}
    {}
    OutputMessageContent(const Refusal& refusal, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{refusal}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override
    {
        return UtilityType_OutputMessageContent;
    }

    [[nodiscard]] bool isText() const { return mVariant.index() == 0; }
    [[nodiscard]] bool isRefusal() const { return mVariant.index() == 1; }

    [[nodiscard]] OutputText text() const
    {
        return isText() ? std::get<OutputText>(mVariant) : OutputText{};
    }
    void setText(const OutputText& text) { mVariant = text; }

    [[nodiscard]] Refusal refusal() const
    {
        return isRefusal() ? std::get<Refusal>(mVariant) : Refusal{};
    }
    void setRefusal(const Refusal& refusal) { mVariant = refusal; }

    [[nodiscard]] bool operator==(const OutputMessageContent& that) const
    {
        return mVariant == that.mVariant && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return ((isText() && text().isEmpty()) || (isRefusal() && refusal().isEmpty()))
               && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override
    {
        return (isText() && text().isValid()) || (isRefusal() && refusal().isValid());
    }

    static OutputMessageContent fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        OutputMessageContent content;
        content.readJson(json, errors);
        return content;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto type = extra().value(QStringLiteral("type")).toString();
            type == QStringLiteral("output_text")) {
            mVariant = OutputText::fromJson(json, errors);
            return true;
        } else if (type == QStringLiteral("refusal")) {
            mVariant = Refusal::fromJson(json, errors);
            return true;
        } else if (errors)
            errors->append(QStringLiteral("OutputText::readJson: invalid type: '%1'").arg(type));

        return false;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        switch (mVariant.index()) {
        case 0:
            mergeJson(json, text().toJson());
            break;
        case 1:
            mergeJson(json, refusal().toJson());
            break;
        }

        return true;
    }
};

class OutputMessage : public Message
{
    Q_GADGET
    Q_PROPERTY(QList<OutputMessageContent> content READ content WRITE setContent FINAL)

private:
    QList<OutputMessageContent> mContent;

public:
    OutputMessage(const QJsonObject& extra = {})
        : Message{extra}
    {}
    OutputMessage(const QString& text,
                  const QString& id = {},
                  Role role = Role_User,
                  Status status = Status_Completed,
                  const QJsonObject& extra = {})
        : Message{id, role, status, extra}
        , mContent{OutputText{text}}
    {}
    OutputMessage(const QList<OutputMessageContent>& content,
                  const QString& id,
                  Role role,
                  Status status = Status_Completed,
                  const QJsonObject& extra = {})
        : Message{id, role, status, extra}
        , mContent{content}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_OutputMessage; }

    [[nodiscard]] QList<OutputMessageContent> content() const { return mContent; }
    void setContent(const QList<OutputMessageContent>& content) { mContent = content; }

    [[nodiscard]] bool operator==(const OutputMessage& that) const
    {
        return mContent == that.mContent && Message::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mContent.isEmpty() && Message::isEmpty(); }
    [[nodiscard]] bool isValid() const override
    {
        return !mContent.isEmpty() && Message::isValid();
    }

    static OutputMessage fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        OutputMessage msg;
        msg.readJson(json, errors);
        return msg;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Message::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("content")); !v.isArray()) {
            if (errors)
                errors->append(
                    QStringLiteral("OutputMessage::readJson: 'content' is not an object"));
            return false;
        } else {
            mContent.clear();
            const auto a = v.toArray();
            for (const auto o : a)
                mContent.append(OutputMessageContent::fromJson(o.toObject(), errors));
            extra().remove(QStringLiteral("content"));
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Message::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("status"), statusAsString());

        if (!mContent.isEmpty()) {
            QJsonArray a;
            for (const auto& c : mContent) {
                a.append(c.toJson());
            }
            json.insert(QStringLiteral("content"), a);
        }

        return true;
    }
};

class OutputItem : public Base
{
    Q_GADGET
    Q_PROPERTY(OutputMessage message READ message WRITE setMessage FINAL)
    Q_PROPERTY(ImageGenerationCall imageGenerationCall READ imageGenerationCall WRITE
                   setImageGenerationCall FINAL)
    Q_PROPERTY(ReasoningOutput reasoning READ reasoning WRITE setReasoning FINAL)

    using Variant = std::variant<OutputMessage, ImageGenerationCall, ReasoningOutput>;
    Variant mVariant;

public:
    OutputItem(const QJsonObject& extra = {})
        : Base{extra}
    {}
    OutputItem(const OutputMessage& message, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{message}
    {}
    OutputItem(const ImageGenerationCall& imageGeneration, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{imageGeneration}
    {}
    OutputItem(const ReasoningOutput& reasoning, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{reasoning}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_OutputItem; }

    [[nodiscard]] bool isMessage() const { return mVariant.index() == 0; }
    [[nodiscard]] bool isImageGenerationCall() const { return mVariant.index() == 1; }
    [[nodiscard]] bool isReasoning() const { return mVariant.index() == 2; }

    [[nodiscard]] OutputMessage message() const { return std::get<OutputMessage>(mVariant); }
    void setMessage(const OutputMessage& message) { mVariant = message; }

    [[nodiscard]] ImageGenerationCall imageGenerationCall() const
    {
        return std::get<ImageGenerationCall>(mVariant);
    }
    void setImageGenerationCall(const ImageGenerationCall& imageGenerationCall)
    {
        mVariant = imageGenerationCall;
    }

    [[nodiscard]] ReasoningOutput reasoning() const
    {
        return isReasoning() ? std::get<ReasoningOutput>(mVariant) : ReasoningOutput{};
    }
    void setReasoning(const ReasoningOutput& reasoning) { mVariant = reasoning; }

    [[nodiscard]] bool operator==(const OutputItem& that) const
    {
        return mVariant == that.mVariant && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return ((isMessage() && message().isEmpty())
                || (isImageGenerationCall() && imageGenerationCall().isEmpty())
                || (isReasoning() && reasoning().isEmpty()))
               && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override
    {
        return ((isMessage() && message().isValid())
                || (isImageGenerationCall() && imageGenerationCall().isValid())
                || (isReasoning() && reasoning().isValid()));
    }

    static OutputItem fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        OutputItem item;
        item.readJson(json, errors);
        return item;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto type = extra().value(QStringLiteral("type")).toString();
            type == QStringLiteral("message")) {
            mVariant = OutputMessage::fromJson(json, errors);
            return true;
        } else if (type == QStringLiteral("image_generation_call")) {
            mVariant = ImageGenerationCall::fromJson(json, errors);
            return true;
        } else if (type == QStringLiteral("reasoning")) {
            mVariant = ReasoningOutput::fromJson(json, errors);
            return true;
        } else if (errors)
            errors->append(QStringLiteral("OutputText::readJson: invalid type: '%1'").arg(type));

        return false;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        switch (mVariant.index()) {
        case 0:
            mergeJson(json, message().toJson());
            break;
        case 1:
            mergeJson(json, imageGenerationCall().toJson());
            break;
        case 2:
            mergeJson(json, reasoning().toJson());
            break;
        }

        return true;
    }
};

} // namespace ai

#endif // LIBAI_RESPONSESRESPONSEUTILS_H
