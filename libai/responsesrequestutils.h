#ifndef LIBAI_RESPONSESREQUESTUTILS_H
#define LIBAI_RESPONSESREQUESTUTILS_H

#include <QJsonArray>
#include <QJsonObject>
#include "responseutils.h"
#include <qqmlintegration.h>

namespace ai {

class Base
{
    Q_GADGET
    // QML_VALUE_TYPE(base)
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    Base(const QJsonObject& extra = {})
        : mExtra{extra}
    {}
    virtual ~Base() = default;

    [[nodiscard]] virtual ai::UtilityType utilityType() const = 0;

    [[nodiscard]] QJsonObject extra() const { return mExtra; }
    void setExtra(const QJsonObject& extra) { mExtra = extra; }

    [[nodiscard]] virtual bool isEmpty() const { return mExtra.isEmpty(); }
    [[nodiscard]] virtual bool isValid() const { return false; }

    [[nodiscard]] QJsonObject toJson() const
    {
        QJsonObject json;
        writeJson(json);
        return json;
    }

    [[nodiscard]] bool operator==(const Base& that) const { return mExtra == that.mExtra; }

protected:
    [[nodiscard]] QJsonObject& extra() { return mExtra; }

    virtual bool readJson(const QJsonObject& json, QStringList* /*errors*/ = nullptr)
    {
        mExtra = json;
        return true;
    }
    virtual bool writeJson(QJsonObject& json, QStringList* /*errors*/ = nullptr) const
    {
        for (auto it = mExtra.constBegin(); it != mExtra.constEnd(); ++it)
            json.insert(it.key(), it.value());
        return true;
    }

    static QJsonObject& mergeJson(QJsonObject& target, const QJsonObject& source)
    {
        for (auto it = source.constBegin(); it != source.constEnd(); ++it)
            target.insert(it.key(), it.value());
        return target;
    }

private:
    QJsonObject mExtra;
};

class AiBase : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(AiBase)
    QML_UNCREATABLE("AiBase is an abstract base class")
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    AiBase(QObject* parent = nullptr, const QJsonObject& extra = {})
        : QObject{parent}
        , mExtra{extra}
    {}
    virtual ~AiBase() = default;

    [[nodiscard]] virtual ai::UtilityType utilityType() const = 0;

    [[nodiscard]] QJsonObject extra() const { return mExtra; }
    void setExtra(const QJsonObject& extra) { mExtra = extra; }

    [[nodiscard]] virtual bool isEmpty() const { return mExtra.isEmpty(); }
    [[nodiscard]] virtual bool isValid() const { return false; }

    [[nodiscard]] virtual QJsonObject toJson() const = 0;

protected:
    [[nodiscard]] QJsonObject& extra() { return mExtra; }

private:
    QJsonObject mExtra;
};

class Conversation : public Base
{
    Q_GADGET
    Q_PROPERTY(QString id READ id WRITE setId FINAL)

public:
    Conversation(const QJsonObject& extra = {})
        : Base{extra}
    {}
    Conversation(const QString& id, const QJsonObject& extra = {})
        : Base{extra}
        , mId{id}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Conversation; }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] bool operator==(const Conversation& that) const
    {
        return mId == that.mId && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mId.isEmpty() && Base::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mId.isEmpty(); }

    static Conversation fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        Conversation conversation;
        conversation.readJson(json, errors);
        return conversation;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("conversation")) {
            if (errors)
                errors->append(QStringLiteral("Conversation::readJson: not a conversation"));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("Conversation::readJson: 'id' is not a string"));
                return false;
            } else {
                setId(v.toString());
                extra().remove(QStringLiteral("id"));
            }
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("conversation"));

        if (!mId.isEmpty())
            json.insert(QStringLiteral("id"), mId);

        return true;
    }

private:
    QString mId;
};

class Message : public Base
{
    Q_GADGET
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(Role role READ role WRITE setRole FINAL)
    Q_PROPERTY(QString roleAsString READ roleAsString WRITE setRole FINAL)
    Q_PROPERTY(Status status READ status WRITE setStatus FINAL)
    Q_PROPERTY(QString statusAsString READ statusAsString WRITE setStatus FINAL)

public:
    enum Status { Status_InProgress, Status_Completed, Status_Incomplete, Status_Custom };
    Q_ENUM(Status)

    [[nodiscard]] static QString statusToString(Status status) { return StatusKV.value(status); }
    [[nodiscard]] static Status stringToStatus(const QString& status)
    {
        return StatusKV.key(status, Status_Custom);
    }

    enum Role { Role_System, Role_Assistant, Role_User, Role_Custom };
    Q_ENUM(Role)

    [[nodiscard]] static QString roleToString(Role role) { return RoleKV.value(role); }
    [[nodiscard]] static Role stringToRole(const QString& role)
    {
        return RoleKV.key(role, Role_Custom);
    }

    Message(const QJsonObject& extra = {})
        : Base{extra}
    {}
    Message(const QString& id, Role role, Status status, const QJsonObject& extra = {})
        : Base{extra}
        , mId{id}
        , mStatus{status}
        , mRole{role}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Message; }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] Role role() const { return mRole; }
    void setRole(Role role)
    {
        mRole = role;
        mCustomRole.clear();
    }
    [[nodiscard]] QString roleAsString() const
    {
        return mRole < Role_Custom ? roleToString(role()) : mCustomRole;
    }
    void setRole(const QString& role)
    {
        setRole(stringToRole(role));
        if (mRole >= Role_Custom)
            mCustomRole = role;
    }

    [[nodiscard]] Status status() const { return mStatus; }
    void setStatus(Status status)
    {
        mStatus = status;
        mCustomStatus.clear();
    }
    [[nodiscard]] QString statusAsString() const
    {
        return mStatus < Status_Custom ? statusToString(status()) : mCustomStatus;
    }
    void setStatus(const QString& status)
    {
        setStatus(stringToStatus(status));
        if (mStatus >= Status_Custom)
            mCustomStatus = status;
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return id().isEmpty()
               && role() == Role_Custom
               && status() == Status_Custom
               && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override
    {
        return role() != Role_Custom && status() != Status_Custom;
    }

    [[nodiscard]] bool operator==(const Message& that) const
    {
        return mId == that.mId
               && mRole == that.mRole
               && mCustomRole == that.mCustomRole
               && mStatus == that.mStatus
               && mCustomStatus == that.mCustomStatus
               && Base::
               operator==(that);
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("message")) {
            if (errors)
                errors->append(QStringLiteral("Message::readJson: not a message"));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (json.contains(QStringLiteral("role"))) {
            if (const auto v = json.value(QStringLiteral("role")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("Message::readJson: 'role' is not a string"));
                return false;
            } else if (const auto r = stringToRole(v.toString()); r == Role::Role_Custom) {
                if (errors)
                    errors->append(
                        QStringLiteral("Message::readJson: 'role' is invalid: '%1'").arg(v.toString()));
                setRole(v.toString());
                extra().remove(QStringLiteral("role"));
            } else {
                setRole(r);
                extra().remove(QStringLiteral("role"));
            }
        }

        if (json.contains(QStringLiteral("status"))) {
            if (const auto v = json.value(QStringLiteral("status")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("Message::readJson: 'status' is not a string"));
                return false;
            } else if (const auto s = stringToStatus(v.toString()); s == Status::Status_Custom) {
                if (errors)
                    errors->append(
                        QStringLiteral("Message::readJson: 'status' is invalid: '%1'").arg(v.toString()));
                setStatus(v.toString());
                extra().remove(QStringLiteral("status"));
            } else {
                setStatus(s);
                extra().remove(QStringLiteral("status"));
            }
        }

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("Message::readJson: 'id' is not a string"));
                return false;
            } else {
                setId(v.toString());
                extra().remove(QStringLiteral("id"));
            }
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("message"));

        json.insert(QStringLiteral("role"),
                    mRole != Role_Custom ? roleToString(mRole) : mCustomRole);

        if (!mId.isEmpty())
            json.insert(QStringLiteral("id"), mId);

        return true;
    }

private:
    QString mId;
    QString mCustomStatus;
    QString mCustomRole;
    Status mStatus = Status_Custom;
    Role mRole = Role_Custom;

    inline static const QMap<Status, QString> StatusKV = {{Status_InProgress, "in_progress"},
                                                          {Status_Completed, "completed"},
                                                          {Status_Incomplete, "incomplete"}};
    inline static const QMap<Role, QString> RoleKV = {{Role_System, "system"},
                                                      {Role_Assistant, "assistant"},
                                                      {Role_User, "user"}};
};

class StringList : public QStringList
{
public:
    StringList(const QStringList& items = {})
        : QStringList{items}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_StringList; }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (const auto& item : *this)
            array.append(item);
        return array;
    }

    static StringList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        StringList list;

        for (const auto& i : json)
            list.append(i.toString());

        return list;
    }
};

class IncludeList : public StringList
{
    Q_GADGET

    unsigned mInclude = 0;

public:
    enum Include {
        NoInclude = 0x0000,
        IncludeWebSearchCallActionSources = 0x0001,
        IncludeCodeInterpreterCallOutputs = 0x0002,
        IncludeMessageInputImageImageUrl = 0x0004,
        IncludeMessageOutputTextLogProbs = 0x0008,
        IncludeReasoningEncryptedContent = 0x0010,
        IncludeComputerCallOutputImageUrl = 0x0020,
        IncludeFileSearchCallResults = 0x0040,
    };
    Q_ENUM(Include)

    [[nodiscard]] static Include toInclude(const QString& include)
    {
        return includeKV.key(include, NoInclude);
    }
    [[nodiscard]] static QString toString(Include include) { return includeKV.value(include); }

    static IncludeList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        IncludeList list;

        for (const auto& i : json)
            list.addInclude(list.toInclude(i.toString()));

        return list;
    }

    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_StringList; }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;

        if (mInclude & IncludeCodeInterpreterCallOutputs)
            array.append(toString(IncludeCodeInterpreterCallOutputs));

        if (mInclude & IncludeWebSearchCallActionSources)
            array.append(toString(IncludeWebSearchCallActionSources));

        if (mInclude & IncludeReasoningEncryptedContent)
            array.append(toString(IncludeReasoningEncryptedContent));

        if (mInclude & IncludeComputerCallOutputImageUrl)
            array.append(toString(IncludeComputerCallOutputImageUrl));

        if (mInclude & IncludeFileSearchCallResults)
            array.append(toString(IncludeFileSearchCallResults));

        if (mInclude & IncludeMessageInputImageImageUrl)
            array.append(toString(IncludeMessageInputImageImageUrl));

        if (mInclude & IncludeMessageOutputTextLogProbs)
            array.append(toString(IncludeMessageOutputTextLogProbs));

        return array;
    }

    unsigned include() const { return mInclude; }
    bool include(Include include) const { return mInclude & include; }
    void setInclude(unsigned include) { mInclude = include; }
    void addInclude(Include include) { mInclude |= include; }
    void removeInclude(Include include) { mInclude &= ~include; }

private:
    inline static const QMap<Include, QString> includeKV
        = {{NoInclude, ""},
           {IncludeWebSearchCallActionSources, "web_search_call.action.sources"},
           {IncludeCodeInterpreterCallOutputs, "code_interpreter_call.outputs"},
           {IncludeMessageInputImageImageUrl, "message.input_image.image_url"},
           {IncludeMessageOutputTextLogProbs, "message.output_text.log_probs"},
           {IncludeReasoningEncryptedContent, "reasoning.encrypted_content"},
           {IncludeComputerCallOutputImageUrl, "computer_call_output.output.image_url"}};
};

class InputText : public Base
{
    Q_GADGET
    Q_PROPERTY(QString text READ text WRITE setText FINAL)

    // annotations and logprobs!!!

    QString mText;

public:
    InputText(const QJsonObject& extra = {})
        : Base{extra}
    {}
    InputText(const QString& text, const QJsonObject& extra = {})
        : Base{extra}
        , mText{text}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_InputText; }

    [[nodiscard]] QString text() const { return mText; }
    void setText(const QString& text) { mText = text; }

    [[nodiscard]] bool operator==(const InputText& that) const
    {
        return mText == that.mText && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mText.isEmpty() && Base::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mText.isEmpty(); }

    static InputText fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        InputText text;
        text.readJson(json, errors);
        return text;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (json.value(QStringLiteral("type")) != QStringLiteral("input_text")) {
            if (errors)
                errors->append(QStringLiteral("InputText::readJson: not an 'input_text'"));
            return false;
        }

        setText(json.value(QStringLiteral("text")).toString());
        extra().remove(QStringLiteral("text"));

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("input_text"));
        json.insert(QStringLiteral("text"), mText);

        return true;
    }
};

class InputImage : public Base
{
    Q_GADGET
    Q_PROPERTY(Detail detail READ detail WRITE setDetail FINAL)
    Q_PROPERTY(QString detailAsString READ detailAsString WRITE setDetail FINAL)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId FINAL)
    Q_PROPERTY(QUrl imageUrl READ imageUrl WRITE setImageUrl FINAL)

public:
    enum Detail { Detail_Auto, Detail_Low, Detail_High, Detail_Custom };
    Q_ENUM(Detail)

    [[nodiscard]] static QString detailToString(Detail detail) { return DetailKV.value(detail); }
    [[nodiscard]] static Detail stringToDetail(const QString& detail)
    {
        return DetailKV.key(detail, Detail_Custom);
    }

private:
    Detail mDetail = Detail::Detail_Auto;
    QString mCustomDetail;
    QString mFileId;
    QUrl mImageUrl;

    inline static const QMap<Detail, QString> DetailKV = {{Detail::Detail_Auto, "auto"},
                                                          {Detail::Detail_Low, "low"},
                                                          {Detail::Detail_High, "high"}};

public:
    InputImage(const QJsonObject& extra = {})
        : Base{extra}
    {}
    InputImage(const QString& fileId, Detail detail = Detail_Auto, const QJsonObject& extra = {})
        : Base{extra}
        , mDetail{detail}
        , mFileId{fileId}
    {}
    InputImage(const QUrl& imageUrl, Detail detail = Detail_Auto, const QJsonObject& extra = {})
        : Base{extra}
        , mDetail{detail}
        , mImageUrl{imageUrl}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_InputImage; }

    [[nodiscard]] Detail detail() const { return mDetail; }
    void setDetail(Detail detail)
    {
        mDetail = detail;
        if (mDetail < Detail_Custom)
            mCustomDetail.clear();
    }
    [[nodiscard]] QString detailAsString() const
    {
        return mDetail < Detail_Custom ? detailToString(mDetail) : mCustomDetail;
    }
    void setDetail(const QString& detail)
    {
        mDetail = stringToDetail(detail);
        if (mDetail >= Detail_Custom)
            mCustomDetail = detail;
    }

    [[nodiscard]] QString fileId() const { return mFileId; }
    void setFileId(const QString& fileId)
    {
        mFileId = fileId;
        mImageUrl.clear();
    }

    [[nodiscard]] QUrl imageUrl() const { return mImageUrl; }
    void setImageUrl(const QUrl& imageUrl)
    {
        mImageUrl = imageUrl;
        mFileId.clear();
    }

    [[nodiscard]] bool operator==(const InputImage& that) const
    {
        return mDetail == that.mDetail
               && mFileId == that.mFileId
               && mImageUrl == that.mImageUrl
               && Base::
               operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return mDetail == Detail::Detail_Custom
               && mCustomDetail.isEmpty()
               && mFileId.isEmpty()
               && mImageUrl.isEmpty()
               && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override
    {
        return !mFileId.isEmpty() || !mImageUrl.isEmpty();
    }

    static InputImage fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        InputImage image;
        image.readJson(json, errors);
        return image;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (extra().value(QStringLiteral("type")) != QStringLiteral("input_image")) {
            if (errors)
                errors->append(QStringLiteral("InputImage::readJson: not an 'input_image'"));
            return false;
        }

        if (extra().contains(QStringLiteral("file_id"))) {
            if (const auto v = extra().value(QStringLiteral("file_id")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'file_id' is not a string"));
                return false;
            } else {
                setFileId(v.toString());
                extra().remove(QStringLiteral("file_id"));
            }
        }

        if (extra().contains(QStringLiteral("image_url"))) {
            if (const auto v = extra().value(QStringLiteral("image_url")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'image_url' is not a string"));
                return false;
            } else {
                setImageUrl(v.toString());
                extra().remove(QStringLiteral("image_url"));
            }
        }

        if (extra().contains(QStringLiteral("detail"))) {
            if (const auto v = extra().value(QStringLiteral("detail")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'detail' is not a string"));
                return false;
            } else {
                setDetail(v.toString());
                extra().remove(QStringLiteral("detail"));
            }
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("input_image"));
        if (!mFileId.isEmpty())
            json.insert(QStringLiteral("file_id"), mFileId);
        if (!mImageUrl.isEmpty())
            json.insert(QStringLiteral("image_url"), mImageUrl.toString());
        json.insert(QStringLiteral("detail"), detailAsString());

        return true;
    }
};

class InputFile : public Base
{
    Q_GADGET
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId FINAL)
    Q_PROPERTY(QUrl fileUrl READ fileUrl WRITE setFileUrl FINAL)
    Q_PROPERTY(QByteArray fileData READ fileData WRITE setFileData FINAL)
    Q_PROPERTY(QString filename READ filename WRITE setFilename FINAL)

private:
    QString mFileId;
    QUrl mFileUrl;
    QByteArray mFileData;
    QString mFilename;

public:
    InputFile(const QJsonObject& extra = {})
        : Base{extra}
    {}
    InputFile(const QString& fileId, const QString& filename = {}, const QJsonObject& extra = {})
        : Base{extra}
        , mFileId{fileId}
        , mFilename{filename}
    {}
    InputFile(const QUrl& fileUrl, const QString& filename = {}, const QJsonObject& extra = {})
        : Base{extra}
        , mFileUrl{fileUrl}
        , mFilename{filename}
    {}
    InputFile(const QByteArray& fileData,
              const QString& filename = {},
              const QJsonObject& extra = {})
        : Base{extra}
        , mFileData{fileData}
        , mFilename{filename}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_InputFile; }

    [[nodiscard]] QString fileId() const { return mFileId; }
    void setFileId(const QString& fileId) { mFileId = fileId; }

    [[nodiscard]] QUrl fileUrl() const { return mFileUrl; }
    void setFileUrl(const QUrl& fileUrl) { mFileUrl = fileUrl; }

    [[nodiscard]] QByteArray fileData() const { return mFileData; }
    void setFileData(const QByteArray& fileData) { mFileData = fileData; }

    [[nodiscard]] QString filename() const { return mFilename; }
    void setFilename(const QString& filename) { mFilename = filename; }

    [[nodiscard]] bool operator==(const InputFile& that) const
    {
        return mFileId == that.mFileId
               && mFileId == that.mFileId
               && mFileUrl == that.mFileUrl
               && mFileData == that.mFileData
               && mFilename == that.mFilename
               && Base::
               operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return mFileId.isEmpty()
               && mFileUrl.isEmpty()
               && mFileData.isEmpty()
               && mFilename.isEmpty()
               && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override
    {
        return !mFileId.isEmpty()
               || !mFileUrl.isEmpty()
               || !mFileData.isEmpty()
               || !mFilename.isEmpty();
    }

    static InputFile fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        InputFile file;
        file.readJson(json, errors);
        return file;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (extra().value(QStringLiteral("type")) != QStringLiteral("input_file")) {
            if (errors)
                errors->append(QStringLiteral("InputFile::readJson: not an 'input_file'"));
            return false;
        }

        if (extra().contains(QStringLiteral("file_id"))) {
            if (const auto v = extra().value(QStringLiteral("file_id")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'file_id' is not a string"));
                return false;
            } else {
                setFileId(v.toString());
                extra().remove(QStringLiteral("file_id"));
            }
        }

        if (extra().contains(QStringLiteral("file_url"))) {
            if (const auto v = extra().value(QStringLiteral("file_url")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'file_url' is not a string"));
                return false;
            } else {
                setFileUrl(v.toString());
                extra().remove(QStringLiteral("file_url"));
            }
        }

        if (extra().contains(QStringLiteral("file_data"))) {
            if (const auto v = extra().value(QStringLiteral("file_data")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'file_data' is not a string"));
                return false;
            } else {
                setFileData(v.toString().toUtf8());
                extra().remove(QStringLiteral("file_data"));
            }
        }

        if (extra().contains(QStringLiteral("filename"))) {
            if (const auto v = extra().value(QStringLiteral("filename")); !v.isString()) {
                if (errors)
                    errors->append(QStringLiteral("'filename' is not a string"));
                return false;
            } else {
                setFilename(v.toString());
                extra().remove(QStringLiteral("filename"));
            }
        }

        return true;
    }
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("type"), QStringLiteral("input_file"));
        if (!mFileId.isEmpty())
            json.insert(QStringLiteral("file_id"), mFileId);
        if (!mFileUrl.isEmpty())
            json.insert(QStringLiteral("file_url"), mFileUrl.toString());
        if (!mFileData.isEmpty())
            json.insert(QStringLiteral("file_data"), QString(mFileData));
        if (!mFilename.isEmpty())
            json.insert(QStringLiteral("filename"), mFilename);

        return true;
    }
};

class InputAudio
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QJsonObject e;

public:
    [[nodiscard]] ai::UtilityType utilityType() const { return UtilityType_InputAudio; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool operator==(const InputAudio& that) const { return e == that.e; }
    [[nodiscard]] bool operator<(const InputAudio& that) const { return false; }

    [[nodiscard]] bool isEmpty() const { return e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return false; }

    QJsonObject toJson() const
    {
        QJsonObject json = e;
        json[QStringLiteral("type")] = QStringLiteral("input_audio");
        return json;
    }

    static InputAudio fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("input_audio")) {
            if (ok)
                *ok = false;
            return {};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        InputAudio input;

        // if (json.contains(QStringLiteral("file_data"))) {
        //     if (const auto v = json.value(QStringLiteral("file_data")); !v.isString()) {
        //         if (ok)
        //             *ok = false;
        //     } else
        //         input.setFileData(v.toString());
        // }

        // if (json.contains(QStringLiteral("file_id"))) {
        //     if (const auto v = json.value(QStringLiteral("file_id")); !v.isString()) {
        //         if (ok)
        //             *ok = false;
        //     } else
        //         input.setFileId(v.toString());
        // }

        // if (json.contains(QStringLiteral("file_url"))) {
        //     if (const auto v = json.value(QStringLiteral("file_url")); !v.isString()) {
        //         if (ok)
        //             *ok = false;
        //     } else
        //         input.setFileUrl(v.toString());
        // }

        // if (json.contains(QStringLiteral("filename"))) {
        //     if (const auto v = json.value(QStringLiteral("filename")); !v.isString()) {
        //         if (ok)
        //             *ok = false;
        //     } else
        //         input.setFilename(v.toString());
        // }

        input.e = extra;
        return input;
    }
};

class InputMessageContent : public Base
{
    Q_GADGET
    Q_PROPERTY(bool isText READ isText FINAL)
    Q_PROPERTY(bool isImage READ isImage FINAL)
    Q_PROPERTY(bool isFile READ isFile FINAL)
    Q_PROPERTY(InputText text READ text WRITE setText FINAL)
    Q_PROPERTY(InputImage image READ image WRITE setImage FINAL)
    Q_PROPERTY(InputFile file READ file WRITE setFile FINAL)
    // Q_PROPERTY(InputAudio audio READ audio WRITE setAudio FINAL)

    using Variant = std::variant<InputText, InputImage, InputFile /*, InputAudio*/>;
    Variant mVariant;

public:
    InputMessageContent(const QJsonObject& extra = {})
        : Base{extra}
    {}
    InputMessageContent(const QString& text, const QJsonObject& extra = {})
        : InputMessageContent{InputText{text}, extra}
    {}
    InputMessageContent(const InputText& inputText, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{inputText}
    {}
    InputMessageContent(const InputImage& inputImage, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{inputImage}
    {}
    InputMessageContent(const InputFile& inputFile, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{inputFile}
    {}
    // InputMessageContent(const InputAudio& inputAudio, const QJsonObject& extra = {})
    //     : Base{extra}
    //     , mVariant{inputAudio}
    // {}
    InputMessageContent(const Variant& input, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{input}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override
    {
        return UtilityType_InputMessageContent;
    }

    [[nodiscard]] bool isText() const { return mVariant.index() == 0; }
    [[nodiscard]] bool isImage() const { return mVariant.index() == 1; }
    [[nodiscard]] bool isFile() const { return mVariant.index() == 2; }
    // [[nodiscard]] bool isAudio() const { return mVariant.index() == 3; }

    [[nodiscard]] InputText text() const
    {
        return isText() ? std::get<InputText>(mVariant) : InputText{};
    }
    void setText(const InputText& text) { mVariant = text; }

    [[nodiscard]] InputImage image() const
    {
        return isImage() ? std::get<InputImage>(mVariant) : InputImage{};
    }
    void setImage(const InputImage& image) { mVariant = image; }

    [[nodiscard]] InputFile file() const
    {
        return isFile() ? std::get<InputFile>(mVariant) : InputFile{};
    }
    void setFile(const InputFile& file) { mVariant = file; }

    // [[nodiscard]] InputAudio audio() const
    // {
    //     return isAudio() ? std::get<InputAudio>(mVariant) : InputAudio{};
    // }
    // void setAudio(const InputAudio& audio) { mVariant = audio; }

    [[nodiscard]] bool isEmpty() const override
    {
        return ((isText() && text().isEmpty())
                || (isImage() && image().isEmpty())
                || (isFile() && file().isEmpty()) /*|| (isAudio() && audio().isEmpty())*/)
               && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override { return !isEmpty(); }

    static InputMessageContent fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        InputMessageContent content;
        content.readJson(json, errors);
        return content;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (const auto type = json.value(QStringLiteral("type")).toString();
            type == QStringLiteral("input_text")) {
            mVariant = InputText::fromJson(json, errors);
            return true;
        } else if (type == QStringLiteral("input_image")) {
            mVariant = InputImage::fromJson(json, errors);
            return true;
        } else if (type == QStringLiteral("input_file")) {
            mVariant = InputFile::fromJson(json, errors);
            return true;
        }
        // else if (type == QStringLiteral("input_audio")) {
        //     mVariant = InputAudio::fromJson(json, errors);
        //     return true;
        // }
        else if (errors)
            errors->append(
                QStringLiteral("InputMessageContent::readJson: unknown input type: '%1'").arg(type));

        Base::readJson(json, errors);

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
            mergeJson(json, image().toJson());
            break;
        case 2:
            mergeJson(json, file().toJson());
            break;
            // case 3:
            //     mergeJson(json, audio().toJson());
            //     break;
        }

        return true;
    }
};

class InputMessage : public Message
{
    Q_GADGET
    Q_PROPERTY(QList<InputMessageContent> content READ content WRITE setContent FINAL)

public:
    InputMessage(const QJsonObject& extra = {})
        : Message{extra}
    {}
    InputMessage(const QString& text,
                 const QString& id = {},
                 Role role = Role_User,
                 Status status = Status_Completed,
                 const QJsonObject& extra = {})
        : Message{id, role, status, extra}
        , mContent{InputText{text}}
    {}
    InputMessage(const QList<InputMessageContent>& content,
                 const QString& id,
                 Role role,
                 Status status = Status_Completed,
                 const QJsonObject& extra = {})
        : Message{id, role, status, extra}
        , mContent{content}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_InputMessage; }

    [[nodiscard]] QList<InputMessageContent> content() const { return mContent; }
    void setContent(const QList<InputMessageContent>& content) { mContent = content; }

    [[nodiscard]] bool operator==(const InputMessage& that) const
    {
        return mContent == that.mContent && Message::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mContent.isEmpty() && Message::isEmpty(); }
    [[nodiscard]] bool isValid() const override
    {
        return !mContent.isEmpty() && Message::isValid();
    }

    static InputMessage fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        InputMessage msg;
        msg.readJson(json, errors);
        return msg;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Message::writeJson(json, errors))
            return false;

        if (!mContent.isEmpty()) {
            QJsonArray a;
            for (const auto& i : mContent)
                a.append(i.toJson());
            json.insert(QStringLiteral("content"), a);
        }

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Message::readJson(json, errors))
            return false;

        if (json.contains(QStringLiteral("content"))) {
            if (const auto v = json.value(QStringLiteral("content")); !v.isArray()) {
                if (errors)
                    errors->append(QStringLiteral("'content' is not an array"));
                return false;
            } else {
                const auto a = v.toArray();
                QList<InputMessageContent> list;
                for (const auto& i : a) {
                    list.append(InputMessageContent::fromJson(i.toObject(), errors));
                    if (errors && !errors->isEmpty())
                        return false;
                }
                setContent(list);
                extra().remove(QStringLiteral("content"));
            }
        }

        return true;
    }

private:
    QList<InputMessageContent> mContent;
};

class AiInputMessage;

class ItemReference : public Base
{
    Q_GADGET
    Q_PROPERTY(QString id READ id WRITE setId FINAL)

    QString mId;

public:
    ItemReference(const QJsonObject& extra = {})
        : ItemReference{{}, extra}
    {}
    ItemReference(const QString& id, const QJsonObject& extra = {})
        : Base{extra}
        , mId{id}

    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_ItemReference; }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] bool operator==(const ItemReference& that) const
    {
        return mId == that.mId && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mId.isEmpty() && Base::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mId.isEmpty(); }

    static ItemReference fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        ItemReference ref;
        ref.readJson(json, errors);
        return ref;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        if (!mId.isEmpty())
            json.insert(QStringLiteral("id"), mId);

        json.insert(QStringLiteral("type"), QStringLiteral("item_reference"));

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v != QStringLiteral("item_reference")) {
            if (errors)
                errors->append(
                    QStringLiteral("ItemReference::readJson: not an 'item_reference': '%1'").arg(v));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (const auto v = json.value(QStringLiteral("id")); v.isString()) {
            extra().remove(QStringLiteral("id"));
            setId(v.toString());
        }

        return true;
    }
};

class AiItemReference : public AiBase
{
    Q_OBJECT
    QML_NAMED_ELEMENT(AiItemReference)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)

public:
    AiItemReference(QObject* parent = nullptr, const QJsonObject& extra = {})
        : AiBase{parent, extra}
    {}
    AiItemReference(const QString& id, QObject* parent = nullptr, const QJsonObject& extra = {})
        : AiBase{parent, extra}
        , mId{id}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_ItemReference; }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] bool operator==(const AiItemReference& that) const { return mId == that.mId; }

    [[nodiscard]] bool isEmpty() const override { return mId.isEmpty() && AiBase::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mId.isEmpty(); }

    QJsonObject toJson() const override
    {
        QJsonObject json = extra();
        json.insert(QStringLiteral("id"), mId);
        json.insert(QStringLiteral("type"), QStringLiteral("item_reference"));
        return json;
    }

    static ItemReference fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("item_reference")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString id;

        if (const auto v = json.value(QStringLiteral("id")); v.isString()) {
            extra.remove(QStringLiteral("id"));
            id = v.toString();
        }

        else if (ok)
            *ok = false;

        return {id, extra};
    }

private:
    QString mId;
};

class InputItem : public Base
{
    Q_GADGET
    Q_PROPERTY(bool isMessage READ isMessage FINAL)
    Q_PROPERTY(bool isItemReference READ isItemReference FINAL)
    Q_PROPERTY(InputMessage message READ message WRITE setMessage FINAL)
    Q_PROPERTY(ItemReference itemReference READ itemReference WRITE setItemReference FINAL)

    using Variant = std::variant<InputMessage, ItemReference>;
    Variant mVariant;

public:
    InputItem(const QJsonObject& extra = {})
        : Base{extra}
    {}
    InputItem(const InputMessage& message, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{message}
    {}
    InputItem(const ItemReference& itemReference, const QJsonObject& extra = {})
        : Base{extra}
        , mVariant{itemReference}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_InputItem; }

    [[nodiscard]] bool isMessage() const { return mVariant.index() == 0; }
    [[nodiscard]] bool isItemReference() const { return mVariant.index() == 1; }

    [[nodiscard]] InputMessage message() const
    {
        return isMessage() ? std::get<InputMessage>(mVariant) : InputMessage{};
    }
    void setMessage(const InputMessage& message) { std::get<InputMessage>(mVariant) = message; }

    [[nodiscard]] ItemReference itemReference() const
    {
        return isItemReference() ? std::get<ItemReference>(mVariant) : ItemReference{};
    }
    void setItemReference(const ItemReference& itemReference)
    {
        std::get<ItemReference>(mVariant) = itemReference;
    }

    [[nodiscard]] bool isEmpty() const override
    {
        if (isMessage())
            return message().isEmpty();

        if (isItemReference())
            return itemReference().isEmpty();

        return true;
    }
    [[nodiscard]] bool isValid() const override
    {
        if (isMessage())
            return message().isValid();

        if (isItemReference())
            return itemReference().isValid();

        return false;
    }

    static InputItem fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        InputItem item;
        item.readJson(json, errors);
        return item;
    }

protected:
    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (const auto type = json.value(QStringLiteral("type")).toString();
            type == QStringLiteral("message")) {
            mVariant = InputMessage::fromJson(json, errors);
            return true;
        } else if (type == QStringLiteral("item_reference")) {
            mVariant = ItemReference::fromJson(json, errors);
            return true;
        } else if (errors)
            errors->append(
                QStringLiteral("InputItem::readJson: unknown input type: '%1'").arg(type));

        Base::readJson(json, errors);

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
            mergeJson(json, itemReference().toJson());
            break;
        }

        return true;
    }
};

// class AiInputItem : public QObject
// {
//     Q_OBJECT
//     QML_NAMED_ELEMENT(AiInput)
// public:
//     AiInputItem(QObject* parent = nullptr)
//         : QObject{parent}
//     {}
//     AiInputItem(AiInputMessage* message, QObject* parent = nullptr)
//         : QObject{parent}
//         , mMessage{message}
//     {}
//     AiInputItem(AiItemReference* itemReference, QObject* parent = nullptr)
//         : QObject{parent}
//         , mItemReference{itemReference}
//     {}

//     [[nodiscard]] bool isMessage() const { return mMessage; }
//     [[nodiscard]] bool isItemReference() const { return mItemReference; }

//     [[nodiscard]] AiInputMessage* message() const { return mMessage; }
//     void setMessage(AiInputMessage* message)
//     {
//         mMessage = message;
//         if (mMessage)
//             mItemReference = nullptr;
//     }

//     [[nodiscard]] AiItemReference* itemReference() const { return mItemReference; }
//     void setItemReference(AiItemReference* itemReference)
//     {
//         mItemReference = itemReference;
//         if (mItemReference)
//             mMessage = nullptr;
//     }

//     [[nodiscard]] bool isEmpty() const
//     {
//         return (!mMessage || mMessage->isEmpty()) && (!mItemReference || mItemReference->isEmpty());
//     }
//     [[nodiscard]] bool isValid() const { return !isEmpty(); }

//     QJsonValue toJson() const
//     {
//         if (isMessage())
//             return mMessage->toJson();

//         if (isItemReference())
//             return mItemReference->toJson();

//         return {};
//     }

//     static InputItem fromJson(const QJsonObject& json, QStringList* errors = nullptr)
//     {
//         if (const auto v = json.value(QStringLiteral("type")).toString();
//             v == QStringLiteral("message"))
//             return {InputMessage::fromJson(json, errors)};

//         else if (v == QStringLiteral("item_reference"))
//             return {ItemReference::fromJson(json, errors)};

//         return {};
//     }

// private:
//     AiInputMessage* mMessage;
//     AiItemReference* mItemReference;
// };

class Input : public Base
{
    Q_GADGET
    QML_VALUE_TYPE(aiInput)
    Q_PROPERTY(QList<InputItem> items READ items WRITE setItems)

    QList<InputItem> mItems;

public:
    Input() {}
    Input(const QList<InputItem>& items) { setItems(items); }

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Input; }

    [[nodiscard]] QList<InputItem> items() const { return mItems; }
    void setItems(const QList<InputItem>& items) { mItems = items; }

    [[nodiscard]] bool isEmpty() const override { return mItems.isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mItems.isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray json;
        writeJson(json);
        return json;
    }

    operator QString() const { return QJsonDocument{toJson()}.toJson(); }

    static Input fromJson(const QJsonArray& json, QStringList* errors = nullptr)
    {
        Input input;
        input.readJson(json, errors);
        return input;
    }

protected:
    bool readJson(const QJsonArray& json, QStringList* errors = nullptr)
    {
        for (const auto i : json)
            mItems.append(InputItem::fromJson(i.toObject(), errors));
        return true;
    }
    bool writeJson(QJsonArray& json, QStringList* errors = nullptr) const
    {
        for (const auto& i : mItems)
            json.append(i.toJson());
        return true;
    }

    // Input merge(const Input& that) const
    // {
    //     QList<InputItem> list = items();
    //     if (isText())
    //         list.append({Message{{text()}, QStringLiteral("user")}});

    //     if (that.isText())
    //         list.append({Message{{that.text()}, QStringLiteral("user")}});
    //     else
    //         list.append(that.items());

    //     return {list};
    // }
    // Input& operator=(const Input& that)
    // {
    //     d = that.d;
    //     return *this;
    // }
};

// class AiInput : public QObject
// {
//     Q_OBJECT
//     QML_NAMED_ELEMENT(AiInput)
//     Q_PROPERTY(QString text READ text WRITE setText)
//     Q_PROPERTY(QList<AiInputItem*> items READ items WRITE setItems)

// public:
//     AiInput(QObject* parent = nullptr)
//         : QObject{parent}
//     {}
//     AiInput(const QString& text, QObject* parent = nullptr)
//         : QObject{parent}
//         , mText{text}
//     {}
//     AiInput(const QList<AiInputItem*>& items, QObject* parent = nullptr)
//         : QObject{parent}
//         , mItems(items)
//     {}
//     AiInput(const Input& input, QObject* parent = nullptr)
//         : QObject{parent}
//         , mItems{input.items()}
//         , mText{input.text()}
//     {}

//     [[nodiscard]] bool isText() const { return !mText.isEmpty(); }
//     [[nodiscard]] bool isInputItemList() const { return !mItems.isEmpty(); }

//     [[nodiscard]] QString text() const { return mText; }
//     void setText(const QString& text)
//     {
//         mText = text;
//         if (!mText.isEmpty())
//             mItems.clear();
//     }

//     [[nodiscard]] QList<InputItem*> items() const { return mItems; }
//     void setItems(const QList<InputItem>& items)
//     {
//         mItems = items;
//         if (!mItems.isEmpty())
//             mText.clear();
//     }

//     [[nodiscard]] bool isEmpty() const { return mText.isEmpty() && mItems.isEmpty(); }
//     [[nodiscard]] bool isValid() const { return !isEmpty(); }

//     QJsonValue toJson() const
//     {
//         if (isText())
//             return text();

//         if (isInputItemList()) {
//             QJsonArray a;
//             for (auto* i : mItems)
//                 a.append(i->toJson());
//             return a;
//         }

//         return {};
//     }

//     static Input fromJson(const QJsonValue& json, bool* ok = nullptr)
//     {
//         if (ok)
//             *ok = true;

//         if (json.isString() && !json.toString().isEmpty())
//             return {json.toString()};

//         else if (json.isArray() && !json.toArray().isEmpty())
//             return AiInput::fromJson(json.toArray(), ok);

//         else if (ok)
//             *ok = false;

//         return {};
//     }

//     static Input fromJson(const QJsonArray& json, bool* ok = nullptr)
//     {
//         if (ok)
//             *ok = true;

//         if (json.isEmpty())
//             return {};

//         QList<AiInputItem*> items;

//         for (const auto& i : json) {
//             items.append(AiInputItem::fromJson(i.toObject()));
//         }

//         return {items};
//     }

//     // Input merge(const Input& that) const
//     // {
//     //     QList<InputItem> list = items();
//     //     if (isText())
//     //         list.append({Message{{text()}, QStringLiteral("user")}});

//     //     if (that.isText())
//     //         list.append({Message{{that.text()}, QStringLiteral("user")}});
//     //     else
//     //         list.append(that.items());

//     //     return {list};
//     // }
//     // Input& operator=(const Input& that)
//     // {
//     //     d = that.d;
//     //     return *this;
//     // }

// private:
//     Input mInput;
//     QList<AiInputItem*> mItems;
//     QString mText;
// };

class Prompt : public Base
{
    Q_GADGET
    Q_PROPERTY(QVariantMap variables READ variables WRITE setVariables FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QString version READ version WRITE setVersion FINAL)

private:
    QString mId;
    QString mVersion;
    QVariantMap mVariables;

public:
    Prompt(const QJsonObject& extra = {})
        : Base{extra}
    {}
    Prompt(const QString& id,
           const QVariantMap& variables = {},
           const QString& version = {},
           const QJsonObject& extra = {})
        : Base{extra}
        , mId{id}
        , mVersion{version}
        , mVariables{variables}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Prompt; }

    [[nodiscard]] QString id() const { return mId; }
    void setId(const QString& id) { mId = id; }

    [[nodiscard]] QString version() const { return mVersion; }
    void setVersion(const QString& version) { mVersion = version; }

    [[nodiscard]] QVariantMap variables() const { return mVariables; }
    void setVariables(const QVariantMap& variables) { mVariables = variables; }

    [[nodiscard]] bool operator==(const Prompt& that) const
    {
        return mId == that.mId
               && mVersion == that.mVersion
               && mVariables == that.mVariables
               && Base::
               operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return mId.isEmpty() && mVersion.isEmpty() && mVariables.isEmpty();
    }
    [[nodiscard]] bool isValid() const override { return !mId.isEmpty(); }

    static Prompt fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        Prompt prompt;
        prompt.readJson(json, errors);
        return prompt;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        if (!mId.isEmpty())
            json.insert(QStringLiteral("id"), mId);

        if (!mVariables.isEmpty())
            json.insert(QStringLiteral("variables"), QJsonObject::fromVariantMap(mVariables));

        if (!mVersion.isEmpty())
            json.insert(QStringLiteral("version"), mVersion);

        json.insert(QStringLiteral("type"), QStringLiteral("prompt"));

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v != QStringLiteral("prompt")) {
            if (errors)
                errors->append(QStringLiteral("Prompt::readJson: not a 'prompt': '%1'").arg(v));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (const auto v = json.value(QStringLiteral("id")); v.isString()) {
            extra().remove(QStringLiteral("id"));
            setId(v.toString());
        }

        if (const auto v = json.value(QStringLiteral("version")); v.isString()) {
            extra().remove(QStringLiteral("version"));
            setVersion(v.toString());
        }

        if (const auto v = json.value(QStringLiteral("variables")); v.isObject()) {
            extra().remove(QStringLiteral("variables"));
            setVariables(v.toVariant().toMap());
        }

        return true;
    }
};

class Reasoning : public Base
{
    Q_GADGET
    Q_PROPERTY(Effort effort READ effort WRITE setEffort)
    Q_PROPERTY(QString effortAsString READ effortAsString WRITE setEffort)
    Q_PROPERTY(Summary summary READ summary WRITE setSummary)
    Q_PROPERTY(QString summaryAsString READ summaryAsString WRITE setSummary)

public:
    enum Effort {
        Effort_Minimal,
        Effort_Low,
        Effort_Medium,
        Effort_High,
        Effort_Custom
    };
    Q_ENUM(Effort)

    enum Summary { Summary_Auto, Summary_Concise, Summary_Detailed, Summary_Custom };
    Q_ENUM(Summary)

private:
    Effort mEffort;
    Summary mSummary;
    QString mCustomEffort;
    QString mCustomSummary;

    inline static const QMap<Effort, QString> effortKV = {{Effort::Effort_Minimal, "minimal"},
                                                          {Effort::Effort_Low, "low"},
                                                          {Effort::Effort_Medium, "medium"},
                                                          {Effort::Effort_High, "high"}};
    inline static const QMap<Summary, QString> summaryKV = {{Summary::Summary_Auto, "auto"},
                                                            {Summary::Summary_Concise, "concise"},
                                                            {Summary::Summary_Detailed, "detailed"}};

public:
    Reasoning(const QJsonObject& extra = {})
        : Reasoning{{}, {}, extra}
    {}
    Reasoning(Effort effort, Summary summary = Summary::Summary_Auto, const QJsonObject& extra = {})
        : Base(extra)
        , mEffort(effort)
        , mSummary(summary)

    {}
    Reasoning(const QString& effort,
              const QString& summary = summaryToString(Summary::Summary_Auto),
              const QJsonObject& extra = {})
        : Base(extra)
        , mEffort(stringToEffort(effort))
        , mSummary(stringToSummary(summary))
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Reasoning; }

    [[nodiscard]] Effort effort() const { return mEffort; }
    void setEffort(Effort effort)
    {
        mEffort = effort;
        if (mEffort < Effort_Custom)
            mCustomEffort.clear();
    }
    [[nodiscard]] QString effortAsString() const
    {
        return mEffort < Effort_Custom ? effortToString(mEffort) : mCustomEffort;
    }
    void setEffort(const QString& effort)
    {
        mEffort = stringToEffort(effort);
        if (mEffort >= Effort_Custom)
            mCustomEffort = effort;
    }

    [[nodiscard]] Summary summary() const { return mSummary; }
    void setSummary(Summary summary)
    {
        mSummary = summary;
        if (mSummary < Summary_Custom)
            mCustomSummary.clear();
    }
    [[nodiscard]] QString summaryAsString() const
    {
        return mSummary < Summary_Custom ? summaryToString(mSummary) : mCustomSummary;
    }
    void setSummary(const QString& summary)
    {
        mSummary = stringToSummary(summary);
        if (mSummary >= Summary_Custom)
            mCustomSummary = summary;
    }

    [[nodiscard]] bool operator==(const Reasoning& that) const
    {
        return mEffort == that.mEffort && mSummary == that.mSummary && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return mEffort == Effort_Custom && mSummary == Summary_Custom && Base::isEmpty();
    }
    [[nodiscard]] bool isValid() const override
    {
        return mEffort != Effort::Effort_Custom || mSummary != Summary::Summary_Custom;
    }

    static Effort stringToEffort(const QString& effort)
    {
        return effortKV.key(effort, Effort::Effort_Custom);
    }
    static QString effortToString(Effort effort) { return effortKV.value(effort); }

    static Summary stringToSummary(const QString& summary)
    {
        return summaryKV.key(summary, Summary::Summary_Auto);
    }
    static QString summaryToString(Summary summary) { return summaryKV.value(summary); }

    static Reasoning fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        Reasoning reasoning;
        reasoning.readJson(json, errors);
        return reasoning;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("effort"), effortAsString());

        json.insert(QStringLiteral("summary"), summaryAsString());

        // json.insert(QStringLiteral("type"), QStringLiteral("reasoning"));

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        // if (const auto v = json.value(QStringLiteral("type")).toString();
        //     v != QStringLiteral("reasoning")) {
        //     if (errors)
        //         errors->append(
        //             QStringLiteral("Reasoning::readJson: not a 'reasoning': '%1'").arg(v));
        //     return false;
        // } else
        //     extra().remove(QStringLiteral("type"));

        if (json.contains(QStringLiteral("effort"))) {
            if (const auto v = json.value(QStringLiteral("effort")); v.isString()) {
                setEffort(v.toString());
                extra().remove(QStringLiteral("effort"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        if (json.contains(QStringLiteral("summary"))) {
            if (const auto v = json.value(QStringLiteral("summary")); v.isString()) {
                setSummary(v.toString());
                extra().remove(QStringLiteral("summary"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        return true;
    }
};

class Refusal : public Base
{
    Q_GADGET
    Q_PROPERTY(QString refusal READ refusal WRITE setRefusal FINAL)

    QString mRefusal;

public:
    Refusal(const QJsonObject& extra = {})
        : Base{extra}
    {}
    Refusal(const QString& refusal, const QJsonObject& extra = {})
        : Base{extra}
        , mRefusal{refusal}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Refusal; }

    [[nodiscard]] QString refusal() const { return mRefusal; }
    void setRefusal(const QString& refusal) { mRefusal = refusal; }

    [[nodiscard]] bool operator==(const Refusal& that) const
    {
        return mRefusal == that.mRefusal && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return mRefusal.isEmpty() && Base::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return !mRefusal.isEmpty(); }

    static Refusal fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        Refusal refusal;
        refusal.readJson(json, errors);
        return refusal;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        if (!mRefusal.isEmpty())
            json.insert(QStringLiteral("refusal"), mRefusal);
        json.insert(QStringLiteral("type"), QStringLiteral("refusal"));

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v != QStringLiteral("refusal")) {
            if (errors)
                errors->append(QStringLiteral("Refusal::readJson: not a 'refusal': '%1'").arg(v));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (json.contains(QStringLiteral("refusal"))) {
            if (const auto v = json.value(QStringLiteral("refusal")); v.isString()) {
                setRefusal(v.toString());
                extra().remove(QStringLiteral("refusal"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        return true;
    }
};

class StreamOptions : public Base
{
    Q_GADGET
    Q_PROPERTY(bool includeObfuscation READ includeObfuscation WRITE setIncludeObfuscation)

public:
    StreamOptions(const QJsonObject& extra = {})
        : StreamOptions{false, extra}
    {}
    StreamOptions(bool includeObfuscation, const QJsonObject& extra = {})
        : Base{extra}
        , mIncludeObfuscation{includeObfuscation}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_StreamOptions; }

    [[nodiscard]] bool includeObfuscation() const { return mIncludeObfuscation; }
    void setIncludeObfuscation(bool includeObfuscation)
    {
        mIncludeObfuscation = includeObfuscation;
    }

    [[nodiscard]] bool operator==(const StreamOptions& that) const
    {
        return mIncludeObfuscation == that.mIncludeObfuscation && Base::operator==(that);
    }

    [[nodiscard]] bool isEmpty() const override { return !mIncludeObfuscation && Base::isEmpty(); }
    [[nodiscard]] bool isValid() const override { return true; }

    static StreamOptions fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        StreamOptions streamOptions;
        streamOptions.readJson(json, errors);
        return streamOptions;
    }

protected:
    bool writeJson(QJsonObject& json, QStringList* errors = nullptr) const override
    {
        if (!Base::writeJson(json, errors))
            return false;

        json.insert(QStringLiteral("include_obfuscation"), mIncludeObfuscation);
        json.insert(QStringLiteral("type"), QStringLiteral("stream_options"));

        return true;
    }

    bool readJson(const QJsonObject& json, QStringList* errors = nullptr) override
    {
        if (!Base::readJson(json, errors))
            return false;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v != QStringLiteral("stream_options")) {
            if (errors)
                errors->append(
                    QStringLiteral("StreamOptions::readJson: not a 'stream_options': '%1'").arg(v));
            return false;
        } else
            extra().remove(QStringLiteral("type"));

        if (json.contains(QStringLiteral("include_obfuscation"))) {
            if (const auto v = json.value(QStringLiteral("include_obfuscation")); v.isBool()) {
                setIncludeObfuscation(v.toBool());
                extra().remove(QStringLiteral("include_obfuscation"));
            } else if (errors) {
                errors->append(QStringLiteral(""));
                return false;
            }
        }

        return true;
    }

private:
    bool mIncludeObfuscation = false;
};

class ImageGenerationTool : public Base
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

    enum InputFidelity { InputFidelity_High, InputFidelity_Low, InputFidelity_Custom };
    Q_ENUM(InputFidelity)

    enum OutputFormat {
        OutputFormat_Png,
        OutputFormat_Jpeg,
        OutputFormat_Webp,
        OutputFormat_Custom
    };
    Q_ENUM(OutputFormat)

    enum Model {
        Model_DallE2,
        Model_DallE3,
        Model_GptImage1,
        Model_Custom,
    };
    Q_ENUM(Model)

    enum Moderation { Moderation_Auto, Moderation_Low, Moderation_Custom };
    Q_ENUM(Moderation)

    enum Quality { Quality_Auto, Quality_Low, Quality_Medium, Quality_High, Quality_Custom };
    Q_ENUM(Quality)

    enum Size { Size_Auto, Size_1024x1024, Size_1024x1536, Size_1536x1024, Size_Custom };
    Q_ENUM(Size)

    static Background toBackground(const QString& background)
    {
        return BackgroundKV.key(background, Background_Auto);
    }
    static QString toString(Background background) { return BackgroundKV.value(background); }

    static InputFidelity toInputFidelity(const QString& InputFidelity)
    {
        return InputFidelityKV.key(InputFidelity, InputFidelity_High);
    }
    static QString toString(InputFidelity InputFidelity)
    {
        return InputFidelityKV.value(InputFidelity);
    }

    static Model toModel(const QString& model) { return ModelKV.key(model, Model_DallE2); }
    static QString toString(Model model) { return ModelKV.value(model); }

    static Moderation toModeration(const QString& moderation)
    {
        return ModerationKV.key(moderation, Moderation_Auto);
    }
    static QString toString(Moderation moderation) { return ModerationKV.value(moderation); }

    static OutputFormat toOutputFormat(const QString& outputFormat)
    {
        return OutputFormatKV.key(outputFormat, OutputFormat_Png);
    }
    static QString toString(OutputFormat outputFormat)
    {
        return OutputFormatKV.value(outputFormat);
    }

    static Quality toQuality(const QString& quality)
    {
        return QualityKV.key(quality, Quality_Auto);
    }
    static QString toString(Quality quality) { return QualityKV.value(quality); }

    static Size toSize(const QString& size) { return SizeKV.key(size, Size_Auto); }
    static QString toString(Size size) { return SizeKV.value(size); }

    ImageGenerationTool(const QJsonObject& extra = {})
        : Base{extra}
    {}

    [[nodiscard]] QString type() const { return QStringLiteral("image_generation"); }

    [[nodiscard]] ai::UtilityType utilityType() const override
    {
        return UtilityType_ImageGenerationTool;
    }

    [[nodiscard]] Background background() const { return mBackground; }
    void setBackground(Background background)
    {
        mBackground = background;
        if (mBackground < Background_Custom)
            mCustomBackground.clear();
    }
    [[nodiscard]] QString backgroundAsString() const
    {
        return mBackground < Background_Custom ? toString(mBackground) : mCustomBackground;
    }
    void setBackground(const QString& background)
    {
        mBackground = toBackground(background);
        if (mBackground >= Background_Custom)
            mCustomBackground = background;
    }

    [[nodiscard]] InputFidelity inputFidelity() const { return mInputFidelity; }
    void setInputFidelity(InputFidelity inputFidelity)
    {
        mInputFidelity = inputFidelity;
        if (mInputFidelity < InputFidelity_Custom)
            mCustomInputFidelity.clear();
    }
    [[nodiscard]] QString inptFidelityAsString() const
    {
        return mInputFidelity < InputFidelity_Custom ? toString(mInputFidelity)
                                                     : mCustomInputFidelity;
    }
    void setInputFidelity(const QString& inputFidelity)
    {
        mInputFidelity = toInputFidelity(inputFidelity);
        if (mInputFidelity >= InputFidelity_Custom)
            mCustomInputFidelity = inputFidelity;
    }

    [[nodiscard]] QString inputImageMaskFile() const { return mInputImageMaskFile; }
    void setInputImageMaskFile(const QString& inputImageMaskFile)
    {
        mInputImageMaskFile = inputImageMaskFile;
    }

    [[nodiscard]] QString inputImageMaskUrl() const { return mInputImageMaskUrl; }
    void setInputImageMaskUrl(const QString& inputImageMaskUrl)
    {
        mInputImageMaskUrl = inputImageMaskUrl;
    }

    [[nodiscard]] Model model() const { return mModel; }
    void setModel(Model model)
    {
        mModel = model;
        if (mModel < Model_Custom)
            mCustomModel.clear();
    }
    [[nodiscard]] QString modelAsString() const
    {
        return mModel < Model_Custom ? toString(mModel) : mCustomModel;
    }
    void setModel(const QString& model)
    {
        mModel = toModel(model);
        if (mModel >= Model_Custom)
            mCustomModel = model;
    }

    [[nodiscard]] Moderation moderation() const { return mModeration; }
    void setModeration(Moderation moderation)
    {
        mModeration = moderation;
        if (mModeration < Moderation_Custom)
            mCustomModeration.clear();
    }
    [[nodiscard]] QString moderationAsString() const
    {
        return mModeration < Moderation_Custom ? toString(mModeration) : mCustomModeration;
    }
    void setModeration(const QString& moderation)
    {
        mModeration = toModeration(moderation);
        if (mModeration >= Moderation_Custom)
            mCustomModeration = moderation;
    }

    [[nodiscard]] int outputCompression() const { return mOutputCompression; }
    void setOutputCompression(int outputCompression) { mOutputCompression = outputCompression; }

    [[nodiscard]] OutputFormat outputFormat() const { return mOutputFormat; }
    void setOutputFormat(OutputFormat outputFormat)
    {
        mOutputFormat = outputFormat;
        if (mOutputFormat < OutputFormat_Custom)
            mCustomOutputFormat.clear();
    }
    [[nodiscard]] QString outputFormatAsString() const
    {
        return mOutputFormat < OutputFormat_Custom ? toString(mOutputFormat) : mCustomOutputFormat;
    }
    void setOutputFormat(const QString& outputFormat)
    {
        mOutputFormat = toOutputFormat(outputFormat);
        if (mOutputFormat >= OutputFormat_Custom)
            mCustomOutputFormat = outputFormat;
    }

    [[nodiscard]] int partialImages() const { return mPartialImages; }
    void setPartialImages(int partialImages) { mPartialImages = partialImages; }

    [[nodiscard]] Quality quality() const { return mQuality; }
    void setQuality(Quality quality)
    {
        mQuality = quality;
        if (mQuality < Quality_Custom)
            mCustomQuality.clear();
    }
    [[nodiscard]] QString qualityAsString() const
    {
        return mQuality < Quality_Custom ? toString(mQuality) : mCustomQuality;
    }
    void setQuality(const QString& quality)
    {
        mQuality = toQuality(quality);
        if (mQuality >= Quality_Custom)
            mCustomQuality = quality;
    }

    [[nodiscard]] Size size() const { return mSize; }
    void setSize(Size size)
    {
        mSize = size;
        if (mSize < Size_Custom)
            mCustomSize.clear();
    }
    [[nodiscard]] QString sizeAsString() const
    {
        return mSize < Size_Custom ? toString(mSize) : mCustomSize;
    }
    void setSize(const QString& size)
    {
        mSize = toSize(size);
        if (mSize >= Size_Custom)
            mCustomSize = size;
    }

    [[nodiscard]] bool operator==(const ImageGenerationTool& that) const
    {
        return background() == that.background() && inputFidelity() == that.inputFidelity()
               && inputImageMaskFile() == that.inputImageMaskFile()
               && inputImageMaskUrl() == that.inputImageMaskUrl() && model() == that.model()
               && moderation() == that.moderation()
               && outputCompression() == that.outputCompression()
               && outputFormat() == that.outputFormat() && partialImages() == that.partialImages()
               && quality() == that.quality() && size() == that.size();
    }
    [[nodiscard]] bool operator<(const ImageGenerationTool& /*that*/) const { return false; }

    [[nodiscard]] bool isEmpty() const override
    {
        return background() == Background_Auto && inputFidelity() == InputFidelity_High
               && inputImageMaskFile().isEmpty() && inputImageMaskUrl().isEmpty()
               && model() == Model_GptImage1 && moderation() == Moderation_Auto
               && outputCompression() == 0 && outputFormat() == OutputFormat_Png
               && partialImages() == 0 && quality() == Quality_Auto && size() == Size_Auto;
    }
    [[nodiscard]] bool isValid() const override { return !isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = extra();
        json.insert(QStringLiteral("type"), QStringLiteral("image_generation"));
        json.insert(QStringLiteral("background"), toString(background()));
        json.insert(QStringLiteral("input_fidelity"), toString(inputFidelity()));
        json.insert(QStringLiteral("model"), toString(model()));
        json.insert(QStringLiteral("moderation"), toString(moderation()));
        json.insert(QStringLiteral("output_compression"), outputCompression());
        json.insert(QStringLiteral("output_format"), toString(outputFormat()));
        json.insert(QStringLiteral("partial_images"), partialImages());
        json.insert(QStringLiteral("quality"), toString(quality()));
        json.insert(QStringLiteral("size"), toString(size()));
        QJsonObject m;
        if (!inputImageMaskFile().isEmpty())
            m.insert(QStringLiteral("file_id"), inputImageMaskFile());
        if (!inputImageMaskUrl().isEmpty())
            m.insert(QStringLiteral("image_url"), inputImageMaskUrl());
        if (!m.isEmpty())
            json.insert(QStringLiteral("input_image_mask"), m);
        return json;
    }

    static ImageGenerationTool fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("image_generation")) {
            if (ok)
                *ok = false;
            return {json};
        }

        QJsonObject x = json;
        x.remove(QStringLiteral("type"));

        ImageGenerationTool tool;

        // if (const auto v = json.value(QStringLiteral("background")); v.isString()) {
        //     tool.b = v.toString();
        //     x.remove(QStringLiteral("background"));
        // } else if (ok)
        //     *ok = false;

        tool.setExtra(x);

        return tool;
    }

private:
    QString mInputImageMaskFile;
    QString mInputImageMaskUrl;
    QString mCustomBackground;
    QString mCustomInputFidelity;
    QString mCustomModel;
    QString mCustomModeration;
    QString mCustomOutputFormat;
    QString mCustomQuality;
    QString mCustomSize;
    Background mBackground = Background_Auto;
    InputFidelity mInputFidelity = InputFidelity_High;
    Model mModel = Model_GptImage1;
    Moderation mModeration = Moderation_Auto;
    OutputFormat mOutputFormat = OutputFormat_Png;
    Quality mQuality = Quality_Auto;
    Size mSize = Size_Auto;
    int mOutputCompression = 100;
    int mPartialImages = 0;

    inline static const QMap<Background, QString> BackgroundKV = {{Background_Auto, "auto"},
                                                                  {Background_Transparent,
                                                                   "transparent"},
                                                                  {Background_Opaque, "opaque"}};
    inline static const QMap<InputFidelity, QString> InputFidelityKV = {{InputFidelity_High, "high"},
                                                                        {InputFidelity_Low, "low"}};
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
                                                            {Quality_High, "high"}};
    inline static const QMap<Size, QString> SizeKV = {{Size_Auto, "auto"},
                                                      {Size_1024x1024, "1024x1024"},
                                                      {Size_1024x1536, "1024x1536"},
                                                      {Size_1536x1024, "1536x1024"}};
};

class Tool : public Base
{
    Q_GADGET
    Q_PROPERTY(ImageGenerationTool imageGeneration READ imageGeneration WRITE setImageGeneration)

    using Variant = std::variant<ImageGenerationTool>;
    Variant mVariant;

public:
    Tool() {}
    Tool(const ImageGenerationTool& imageGeneration)
        : mVariant{imageGeneration}
    {}

    [[nodiscard]] ai::UtilityType utilityType() const override { return UtilityType_Tool; }

    [[nodiscard]] bool isImageGeneration() const { return mVariant.index() == 0; }

    [[nodiscard]] ImageGenerationTool imageGeneration() const
    {
        return isImageGeneration() ? std::get<ImageGenerationTool>(mVariant)
                                   : ImageGenerationTool{};
    }
    void setImageGeneration(const ImageGenerationTool& imageGeneration)
    {
        mVariant = imageGeneration;
    }

    [[nodiscard]] bool isEmpty() const override
    {
        return (isImageGeneration() && imageGeneration().isEmpty());
    }
    [[nodiscard]] bool isValid() const override
    {
        return (isImageGeneration() && !imageGeneration().isValid());
    }

    QJsonValue toJson() const
    {
        if (isImageGeneration())
            return imageGeneration().toJson();

        return {};
    }

    static Tool fromJson(const QJsonObject& json, QStringList* errors = nullptr)
    {
        Tool tool;
        tool.fromJson(json, errors);
        return tool;
    }
};

} // namespace ai

#endif // LIBAI_RESPONSESREQUESTUTILS_H
