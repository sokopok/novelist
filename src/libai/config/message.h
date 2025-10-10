#ifndef AI_CONFIG_MESSAGE_H
#define AI_CONFIG_MESSAGE_H

#include "empty.h"

namespace ai::config {

class InputText
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QString t;
    QJsonObject e;

public:
    InputText(const QJsonObject& extra = {})
        : e{extra}
    {}
    InputText(const QString& text, const QJsonObject& extra = {})
        : t{text}
        , e{extra}
    {}

    [[nodiscard]] ai::config::Type objectType() const
    {
        return ai::config::Type::Type_Type_InputText;
    }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString text() const { return t; }
    InputText& setText(const QString& text)
    {
        t = text;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputText& that) const
    {
        return t == that.t && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const { return t.isEmpty() && e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return !t.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        if (!t.isEmpty())
            json.insert(QStringLiteral("text"), t);

        json.insert(QStringLiteral("type"), QStringLiteral("input_text"));

        return json;
    }

    static InputText fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("input_text")) {
            if (ok)
                *ok = false;
            return {};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        QString text;

        if (json.contains(QStringLiteral("text"))) {
            if (const auto v = json.value(QStringLiteral("text")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                text = v.toString();
                extra.remove(QStringLiteral("text"));
            }
        }

        else if (ok)
            *ok = false;

        return {text, extra};
    }
};

class InputImage
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(Detail detail READ detail WRITE setDetail FINAL)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId FINAL)
    Q_PROPERTY(QUrl imageUrl READ imageUrl WRITE setImageUrl FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    enum Detail { Auto, Low, High };
    Q_ENUM(Detail)

    [[nodiscard]] static QString toString(Detail detail) { return DetailKV.value(detail); }
    [[nodiscard]] static Detail toDetail(const QString& detail)
    {
        return DetailKV.key(detail, Detail::Auto);
    }

private:
    Detail d = Detail::Auto;
    QString fi;
    QUrl iu;
    QJsonObject e;

    inline static const QMap<Detail, QString> DetailKV = {{Detail::Auto, "auto"},
                                                          {Detail::Low, "low"},
                                                          {Detail::High, "high"}};

public:
    InputImage(const QString& imageUrl = {}, const QJsonObject& extra = {})
        : iu{imageUrl}
        , e{extra}
    {}

    [[nodiscard]] ai::config::Type objectType() const
    {
        return ai::config::Type::Type_Type_InputImage;
    }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] Detail detail() const { return d; }
    InputImage& setDetail(Detail detail)
    {
        d = detail;
        return *this;
    }
    InputImage& setDetail(const QString& detail)
    {
        d = toDetail(detail);
        return *this;
    }

    [[nodiscard]] QString fileId() const { return fi; }
    InputImage& setFileId(const QString& fileId)
    {
        fi = fileId;
        return *this;
    }

    [[nodiscard]] QUrl imageUrl() const { return iu; }
    InputImage& setImageUrl(const QUrl& imageUrl)
    {
        iu = imageUrl;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputImage& that) const
    {
        return d == that.d && fi == that.fi && iu == that.iu && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return d == Detail::Auto && fi.isEmpty() && iu.isEmpty() && e.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return !fi.isEmpty() || !iu.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        if (d != Detail::Auto)
            json.insert(QStringLiteral("detail"), toString(d));

        if (!fi.isEmpty())
            json.insert(QStringLiteral("file_id"), fi);

        if (!iu.isEmpty())
            json.insert(QStringLiteral("image_url"), iu.toString());

        json.insert(QStringLiteral("type"), QStringLiteral("input_image"));

        return json;
    }

    static InputImage fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("input_image")) {
            if (ok)
                *ok = false;
            return {};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        InputImage image;

        if (json.contains(QStringLiteral("detail"))) {
            if (const auto v = json.value(QStringLiteral("detail")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                image.setDetail(toDetail(v.toString()));
                extra.remove(QStringLiteral("detail"));
            }
        }

        if (json.contains(QStringLiteral("file_id"))) {
            if (const auto v = json.value(QStringLiteral("file_id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                image.setFileId(v.toString());
                extra.remove(QStringLiteral("file_id"));
            }
        }

        if (json.contains(QStringLiteral("image_url"))) {
            if (const auto v = json.value(QStringLiteral("image_url")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                image.setImageUrl(v.toString());
                extra.remove(QStringLiteral("image_url"));
            }
        }

        image.e = extra;

        return image;
    }
};

class InputFile
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QString fileData READ fileData WRITE setFileData FINAL)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId FINAL)
    Q_PROPERTY(QString filename READ filename WRITE setFilename FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QString fd;
    QString fi;
    QString fn;
    QUrl fu;
    QJsonObject e;

public:
    InputFile(const QString& fileId = {}, const QJsonObject& extra = {})
        : fi{fileId}
        , e{extra}
    {}

    InputFile(const QUrl& fileUrl, const QJsonObject& extra = {})
        : fu{fileUrl}
        , e{extra}
    {}

    [[nodiscard]] ai::config::Type objectType() const
    {
        return ai::config::Type::Type_Type_InputFile;
    }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString fileData() const { return fd; }
    InputFile& setFileData(const QString& fileData)
    {
        fd = fileData;
        return *this;
    }

    [[nodiscard]] QString fileId() const { return fi; }
    InputFile& setFileId(const QString& fileId)
    {
        fi = fileId;
        return *this;
    }

    [[nodiscard]] QString filename() const { return fn; }
    InputFile& setFilename(const QString& filename)
    {
        fn = filename;
        return *this;
    }

    [[nodiscard]] QUrl fileUrl() const { return fu; }
    InputFile& setFileUrl(const QUrl& fileUrl)
    {
        fu = fileUrl;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputFile& that) const
    {
        return fd == that.fd && fi == that.fi && fu == that.fu && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return fd.isEmpty() && fi.isEmpty() && fu.isEmpty() && e.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return !fd.isEmpty() || !fi.isEmpty() || !fu.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = e;

        if (!fd.isEmpty())
            json.insert(QStringLiteral("file_data"), fd);

        if (!fi.isEmpty())
            json.insert(QStringLiteral("file_id"), fi);

        if (!fu.isEmpty())
            json.insert(QStringLiteral("file_url"), fu.toString());

        if (!fn.isEmpty())
            json.insert(QStringLiteral("filename"), fn);

        json.insert(QStringLiteral("type"), QStringLiteral("input_file"));

        return json;
    }

    static InputFile fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("input_file")) {
            if (ok)
                *ok = false;
            return {};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        InputFile input;

        if (json.contains(QStringLiteral("file_data"))) {
            if (const auto v = json.value(QStringLiteral("file_data")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                input.setFileData(v.toString());
                extra.remove(QStringLiteral("file_data"));
            }
        }

        if (json.contains(QStringLiteral("file_id"))) {
            if (const auto v = json.value(QStringLiteral("file_id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                input.setFileId(v.toString());
                extra.remove(QStringLiteral("file_id"));
            }
        }

        if (json.contains(QStringLiteral("file_url"))) {
            if (const auto v = json.value(QStringLiteral("file_url")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                input.setFileUrl(v.toString());
                extra.remove(QStringLiteral("file_url"));
            }
        }

        if (json.contains(QStringLiteral("filename"))) {
            if (const auto v = json.value(QStringLiteral("filename")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                input.setFilename(v.toString());
                extra.remove(QStringLiteral("filename"));
            }
        }

        input.e = extra;
        return input;
    }
};

class InputAudio
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    QJsonObject e;

public:
    [[nodiscard]] ai::config::Type objectType() const
    {
        return ai::config::Type::Type_Type_InputAudio;
    }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool operator==(const InputAudio& that) const { return e == that.e; }

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

class MessageContentInputItem
{
    Q_GADGET
    Q_PROPERTY(InputText text READ text WRITE setText FINAL)
    Q_PROPERTY(InputImage image READ image WRITE setImage FINAL)
    Q_PROPERTY(InputFile file READ file WRITE setFile FINAL)
    Q_PROPERTY(InputAudio audio READ audio WRITE setAudio FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    using Variant = std::variant<Empty, InputText, InputImage, InputFile, InputAudio>;
    Variant d;
    QJsonObject e;

public:
    MessageContentInputItem(const QJsonObject& extra = {})
        : e{extra}
    {}
    MessageContentInputItem(const Variant& input = {}, const QJsonObject& extra = {})
        : d{input}
        , e{extra}
    {}

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool isText() const { return d.index() == 1; }
    [[nodiscard]] bool isImage() const { return d.index() == 2; }
    [[nodiscard]] bool isFile() const { return d.index() == 3; }
    [[nodiscard]] bool isAudio() const { return d.index() == 4; }

    [[nodiscard]] InputText text() const { return isText() ? std::get<InputText>(d) : InputText{}; }
    MessageContentInputItem& setText(const InputText& text)
    {
        std::get<InputText>(d) = text;
        return *this;
    }

    [[nodiscard]] InputImage image() const
    {
        return isImage() ? std::get<InputImage>(d) : InputImage{};
    }
    MessageContentInputItem& setImage(const InputImage& image)
    {
        std::get<InputImage>(d) = image;
        return *this;
    }

    [[nodiscard]] InputFile file() const { return isFile() ? std::get<InputFile>(d) : InputFile{}; }
    MessageContentInputItem& setFile(const InputFile& file)
    {
        std::get<InputFile>(d) = file;
        return *this;
    }

    [[nodiscard]] InputAudio audio() const
    {
        return isAudio() ? std::get<InputAudio>(d) : InputAudio{};
    }
    MessageContentInputItem& setAudio(const InputAudio& audio)
    {
        std::get<InputAudio>(d) = audio;
        return *this;
    }

    [[nodiscard]] bool operator==(const MessageContentInputItem& that) const
    {
        return d == that.d && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return d.index() == 0
               || (isText() && text().isEmpty() && e.isEmpty())
               || (isImage() && image().isEmpty() && e.isEmpty())
               || (isFile() && file().isEmpty() && e.isEmpty())
               || (isAudio() && audio().isEmpty() && e.isEmpty());
    }
    [[nodiscard]] bool isValid() const
    {
        return (isText() && text().isValid()) || (isImage() && image().isValid())
               || (isFile() && file().isValid()) || (isAudio() && audio().isValid());
    }

    QJsonObject toJson() const
    {
        switch (d.index()) {
        case 0:
            return text().toJson();
        case 1:
            return image().toJson();
        case 2:
            return file().toJson();
        case 3:
            return audio().toJson();
        default:
            return {};
        }
    }

    static MessageContentInputItem fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (const auto v = json.value(QStringLiteral("type")).toString();
            v == QStringLiteral("input_text"))
            return {InputText::fromJson(json, ok)};

        else if (v == QStringLiteral("input_image"))
            return {InputImage::fromJson(json, ok)};

        else if (v == QStringLiteral("input_file"))
            return {InputFile::fromJson(json, ok)};

        else if (v == QStringLiteral("input_audio"))
            return {InputAudio::fromJson(json, ok)};

        if (ok)
            *ok = false;

        return {json};
    }
};

class MessageContentInputItemList : public QList<MessageContentInputItem>
{
    Q_GADGET
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(int count READ count FINAL)

public:
    MessageContentInputItemList(const QList<MessageContentInputItem>& items = {})
        : QList<MessageContentInputItem>{items}
    {}

    [[nodiscard]] ai::config::Type objectType() const
    {
        return ai::config::Type::Type_MessageContentInputItemList;
    }

    [[nodiscard]] bool isValid() const { return !isEmpty(); }

    QJsonArray toJson() const
    {
        QJsonArray array;
        for (const auto& item : *this)
            array.append(item.toJson());
        return array;
    }

    static MessageContentInputItemList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        MessageContentInputItemList list;

        for (const auto& i : json)
            list.append(MessageContentInputItem::fromJson(i.toObject(), ok));

        return list;
    }
};

class MessageContent
{
    Q_GADGET
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(bool isText READ isText FINAL)
    Q_PROPERTY(bool isItemList READ isItemList FINAL)
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    Q_PROPERTY(MessageContentInputItemList items READ items WRITE setItems FINAL)

    using Variant = std::variant<Empty, QString, MessageContentInputItemList>;
    Variant d;
    QJsonObject e;

public:
    MessageContent(const Variant& data = {}, const QJsonObject& extra = {})
        : d{data}
        , e{extra}
    {}

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] bool isText() const { return d.index() == 1; }
    [[nodiscard]] bool isItemList() const { return d.index() == 2; }

    [[nodiscard]] QString text() const { return isText() ? std::get<QString>(d) : QString{}; }
    MessageContent& setText(const QString& text)
    {
        if (isItemList())
            std::get<QString>(d) = text;
        return *this;
    }

    [[nodiscard]] MessageContentInputItemList items() const
    {
        return isItemList() ? std::get<MessageContentInputItemList>(d)
                            : MessageContentInputItemList{};
    }
    MessageContent& setItems(const MessageContentInputItemList& items)
    {
        if (isItemList())
            std::get<MessageContentInputItemList>(d) = items;
        return *this;
    }

    [[nodiscard]] bool operator==(const MessageContent& that) const
    {
        return d == that.d && e == that.e;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return d.index() == 0
               || (isText() && text().isEmpty())
               || (isItemList() && items().isEmpty());
    }
    [[nodiscard]] bool isValid() const
    {
        return (isText() && !text().isEmpty()) || (isItemList() && !items().isEmpty());
    }

    QJsonValue toJson() const
    {
        if (isText())
            return text();

        if (isItemList())
            return items().toJson();

        return {};
    }

    static MessageContent fromJson(const QJsonValue& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.isString())
            return {json.toString()};

        if (json.isArray())
            return {MessageContentInputItemList::fromJson(json.toArray(), ok)};

        if (ok)
            *ok = false;

        return {};
    }
};

class Message
{
    Q_GADGET
    Q_PROPERTY(ai::config::Type objectType READ objectType CONSTANT FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)
    Q_PROPERTY(QString role READ role WRITE setRole FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(MessageContent content READ content WRITE setContent FINAL)
    Q_PROPERTY(Status status READ status WRITE setStatus FINAL)

public:
    enum struct Status { InProgress, Completed, Incomplete };
    Q_ENUM(Status)

    [[nodiscard]] static QString toString(Status status) { return StatusKV.value(status); }
    [[nodiscard]] static Status toStatus(const QString& status) { return StatusKV.key(status); }

private:
    QString r = QStringLiteral("user");
    Status s = Status::InProgress;
    QString i;
    MessageContent c;
    QJsonObject e;

    inline static const QMap<Status, QString> StatusKV = {{Status::InProgress, "in_progress"},
                                                          {Status::Completed, "completed"},
                                                          {Status::Incomplete, "incomplete"}};

public:
    Message(const QJsonObject& extra = {})
        : e{extra}
    {}
    Message(const MessageContent& content,
            const QString& role,
            Status status,
            const QJsonObject& extra = {})
        : r{role}
        , s{status}
        , c{content}
        , e{extra}
    {}
    Message(const MessageContent& content,
            const QString& role = QStringLiteral("user"),
            const QString& id = {},
            Status status = Status::InProgress,
            const QJsonObject& extra = {})
        : r{role}
        , s{status}
        , i{id}
        , c{content}
        , e{extra}
    {}
    Message(const QString& role, Status status, const QJsonObject& extra = {})
        : r{role}
        , s{status}
        , e{extra}
    {}
    Message(const QString& role, const QString& id, Status status, const QJsonObject& extra)
        : r{role}
        , s{status}
        , i{id}
        , e{extra}
    {}

    [[nodiscard]] ai::config::Type objectType() const { return ai::config::Type::Type_Message; }

    [[nodiscard]] QJsonObject extra() const { return e; }

    [[nodiscard]] QString role() const { return r; }
    Message& setRole(const QString& role)
    {
        if (role == QStringLiteral("assistant") || role == QStringLiteral("user")
            || role == QStringLiteral("tool") || role == QStringLiteral("system"))
            r = role;
        return *this;
    }

    [[nodiscard]] QString id() const { return i; }
    Message& setId(const QString& id)
    {
        i = id;
        return *this;
    }

    [[nodiscard]] Status status() const { return s; }
    Message& setStatus(Status status)
    {
        s = status;
        return *this;
    }
    Message& setStatus(const QString& status) { return setStatus(toStatus(status)); }

    [[nodiscard]] MessageContent content() const { return c; }
    Message& setContent(const MessageContent& content)
    {
        c = content;
        return *this;
    }

    [[nodiscard]] bool operator==(const Message& that) const { return e == that.e; }

    [[nodiscard]] bool isEmpty() const
    {
        return role().isEmpty() && content().isEmpty() && id().isEmpty()
               && status() == Status::InProgress;
    }
    [[nodiscard]] bool isValid() const { return !role().isEmpty() && !content().isValid(); }

    QJsonValue toJson() const
    {
        QJsonObject json = e;

        json[QStringLiteral("type")] = QStringLiteral("message");

        if (!r.isEmpty())
            json[QStringLiteral("role")] = r;

        if (s != Status::InProgress)
            json[QStringLiteral("status")] = toString(s);

        if (!c.isEmpty())
            json[QStringLiteral("content")] = c.toJson();

        if (!i.isEmpty())
            json[QStringLiteral("id")] = i;

        return json;
    }

    static Message fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("message")) {
            if (ok)
                *ok = false;
            return {};
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        Message message;

        if (json.contains(QStringLiteral("role"))) {
            if (const auto v = json.value(QStringLiteral("role")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                message.r = v.toString();
                extra.remove(QStringLiteral("role"));
            }
        }

        if (json.contains(QStringLiteral("status"))) {
            if (const auto v = json.value(QStringLiteral("status")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                message.s = StatusKV.key(v.toString(), Status::Completed);
                extra.remove(QStringLiteral("status"));
            }
        }

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                message.i = v.toString();
                extra.remove(QStringLiteral("id"));
            }
        }

        if (json.contains(QStringLiteral("content"))) {
            if (const auto v = json.value(QStringLiteral("content")); v.isArray()) {
                message.c = MessageContent::fromJson(v.toArray());
                extra.remove(QStringLiteral("content"));
            } else if (v.isString()) {
                message.c = MessageContent::fromJson(v.toString());
                extra.remove(QStringLiteral("content"));
            } else {
                if (ok)
                    *ok = false;
            }
        }

        message.e = extra;
        return message;
    }
};

} // namespace ai::config

#endif // AI_CONFIG_MESSAGE_H
