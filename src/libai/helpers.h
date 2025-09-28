#ifndef HELPERS_H
#define HELPERS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QObject>

namespace ai {

enum struct Type {
    InputText,
    InputImage,
    InputFile,
    InputAudio,
    MessageContentInputItemList,
    InputItemList,
    ItemReference,
    Conversation,
    Message
};

class Conversation
{
    Q_GADGET
    Q_PROPERTY(Type type READ type CONSTANT FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

    class Data : public QSharedData
    {
    public:
        Data(const QString& id = {}, const QJsonObject& extra = {})
            : id{id}
            , extra{extra}
        {}

        QString id;
        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;

public:
    Conversation(const QString& id = {}, const QJsonObject& extra = {})
        : d{new Data{id, extra}}
    {}
    Conversation(const Conversation& rhs)
        : d{rhs.d}
    {}
    Conversation(Conversation&& rhs)
        : d{std::move(rhs.d)}
    {}
    Conversation& operator=(const Conversation& rhs)
    {
        if (this != &rhs)
            d = rhs.d;
        return *this;
    }
    Conversation& operator=(Conversation&& rhs)
    {
        if (this != &rhs)
            d = std::move(rhs.d);
        return *this;
    }

    [[nodiscard]] Type type() const { return Type::Conversation; }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] QString id() const { return d->id; }
    Conversation& setId(const QString& id)
    {
        d->id = id;
        return *this;
    }

    [[nodiscard]] bool operator==(const Conversation& that) const
    {
        return d->id == that.d->id && d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return !d.data() || (d->id.isEmpty() && d->extra.isEmpty());
    }
    [[nodiscard]] bool isValid() const { return !d->id.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = d->extra;
        json.insert(QStringLiteral("id"), d->id);
        json.insert(QStringLiteral("type"), QStringLiteral("conversation"));
        return json;
    }

    static Conversation fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        if (json.value(QStringLiteral("type")).toString() != QStringLiteral("conversation")) {
            if (ok)
                *ok = false;
            return {};
        }

        QString id;

        if (const auto v = json.value(QStringLiteral("id")); v.isString())
            id = v.toString();
        else if (ok)
            *ok = false;

        QJsonObject extra = json;
        extra.remove(QStringLiteral("id"));
        extra.remove(QStringLiteral("type"));

        return {id, extra};
    }
};

class InputText
{
    Q_GADGET
    Q_PROPERTY(Type type READ type CONSTANT FINAL)
    Q_PROPERTY(QString text READ text WRITE setText FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    InputText(const QString& text = {}, const QJsonObject& extra = {})
        : d{new Data{text, extra}}
    {}

    [[nodiscard]] Type type() const { return Type::InputText; }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] QString text() const { return d->text; }
    InputText& setText(const QString& text)
    {
        d->text = text;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputText& that) const
    {
        return d->text == that.d->text && d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const { return d->text.isEmpty() && d->extra.isEmpty(); }
    [[nodiscard]] bool isValid() const { return !d->text.isEmpty(); }

    QJsonObject toJson() const
    {
        QJsonObject json = d->extra;
        json.insert(QStringLiteral("text"), d->text);
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

        QString text;

        if (const auto v = json.value(QStringLiteral("text")); v.isString())
            text = v.toString();
        else if (ok)
            *ok = false;

        QJsonObject extra = json;
        extra.remove(QStringLiteral("text"));
        extra.remove(QStringLiteral("type"));

        return {text, extra};
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const QString& text = {}, const QJsonObject& extra = {})
            : text{text}
            , extra{extra}
        {}

        QString text;
        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;
};

class InputImage
{
    Q_GADGET
    Q_PROPERTY(Type type READ type CONSTANT FINAL)
    Q_PROPERTY(Detail detail READ detail WRITE setDetail FINAL)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId FINAL)
    Q_PROPERTY(QUrl imageUrl READ imageUrl WRITE setImageUrl FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    enum Detail { Auto, Low, High };
    Q_ENUM(Detail)

    InputImage(const QString& imageUrl = {}, const QJsonObject& extra = {})
        : d{new Data{imageUrl, extra}}
    {}

    [[nodiscard]] Type type() const { return Type::InputImage; }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] Detail detail() const { return d->detail; }
    InputImage& setDetail(Detail detail)
    {
        d->detail = detail;
        return *this;
    }

    [[nodiscard]] QString fileId() const { return d->fileId; }
    InputImage& setFileId(const QString& fileId)
    {
        d->fileId = fileId;
        return *this;
    }

    [[nodiscard]] QUrl imageUrl() const { return d->imageUrl; }
    InputImage& setImageUrl(const QUrl& imageUrl)
    {
        d->imageUrl = imageUrl;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputImage& that) const
    {
        return d->detail == that.d->detail && d->fileId == that.d->fileId
               && d->imageUrl == that.d->imageUrl && d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return d->detail == Detail::Auto && d->fileId.isEmpty() && d->imageUrl.isEmpty()
               && d->extra.isEmpty();
    }
    [[nodiscard]] bool isValid() const { return !d->fileId.isEmpty() || !d->imageUrl.isEmpty(); }

    QJsonObject toJson() const
    {
        const auto detail = QString(QMetaEnum::fromType<Detail>().valueToKey(d->detail)).toLower();

        QJsonObject json = d->extra;
        json.insert(QStringLiteral("detail"), detail);
        json.insert(QStringLiteral("file_id"), d->fileId);
        json.insert(QStringLiteral("image_url"), d->imageUrl.toString());
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

        InputImage image;

        if (json.contains(QStringLiteral("detail"))) {
            if (const auto v = json.value(QStringLiteral("detail")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else {
                bool ok2 = false;
                if (int value = QMetaEnum::fromType<Detail>()
                                    .keyToValue(v.toString().toLocal8Bit(), &ok2);
                    !ok2) {
                    if (ok)
                        *ok = false;
                } else
                    image.setDetail(Detail(value));
            }
        }

        if (json.contains(QStringLiteral("file_id"))) {
            if (const auto v = json.value(QStringLiteral("file_id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                image.setFileId(v.toString());
        }

        if (json.contains(QStringLiteral("image_url"))) {
            if (const auto v = json.value(QStringLiteral("image_url")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                image.setImageUrl(v.toString());
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("detail"));
        extra.remove(QStringLiteral("file_id"));
        extra.remove(QStringLiteral("image_url"));
        extra.remove(QStringLiteral("type"));

        return image;
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const QString& imageUrl = {}, const QJsonObject& extra = {})
            : imageUrl{imageUrl}
            , extra{extra}
        {}

        Detail detail;
        QString fileId;
        QUrl imageUrl;
        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;
};

class InputFile
{
    Q_GADGET
    Q_PROPERTY(Type type READ type CONSTANT FINAL)
    Q_PROPERTY(QString fileData READ fileData WRITE setFileData FINAL)
    Q_PROPERTY(QString fileId READ fileId WRITE setFileId FINAL)
    Q_PROPERTY(QString filename READ filename WRITE setFilename FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    InputFile(const QString& fileId = {}, const QJsonObject& extra = {})
        : d{new Data{fileId, extra}}
    {}

    InputFile(const QUrl& fileUrl, const QJsonObject& extra = {})
        : d{new Data{fileUrl, extra}}
    {}

    [[nodiscard]] Type type() const { return Type::InputFile; }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] QString fileData() const { return d->fileData; }
    InputFile& setFileData(const QString& fileData)
    {
        d->fileData = fileData;
        return *this;
    }

    [[nodiscard]] QString fileId() const { return d->fileId; }
    InputFile& setFileId(const QString& fileId)
    {
        d->fileId = fileId;
        return *this;
    }

    [[nodiscard]] QString filename() const { return d->filename; }
    InputFile& setFilename(const QString& filename)
    {
        d->filename = filename;
        return *this;
    }

    [[nodiscard]] QUrl fileUrl() const { return d->fileUrl; }
    InputFile& setFileUrl(const QUrl& fileUrl)
    {
        d->fileUrl = fileUrl;
        return *this;
    }

    [[nodiscard]] bool operator==(const InputFile& that) const
    {
        return d->fileData == that.d->fileData && d->fileId == that.d->fileId
               && d->fileUrl == that.d->fileUrl && d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return d->fileData.isEmpty() && d->fileId.isEmpty() && d->fileUrl.isEmpty()
               && d->extra.isEmpty();
    }
    [[nodiscard]] bool isValid() const
    {
        return !d->fileData.isEmpty() || !d->fileId.isEmpty() || !d->fileUrl.isEmpty();
    }

    QJsonObject toJson() const
    {
        QJsonObject json = d->extra;
        json.insert(QStringLiteral("file_data"), d->fileData);
        json.insert(QStringLiteral("file_id"), d->fileId);
        json.insert(QStringLiteral("file_url"), d->fileUrl.toString());
        json.insert(QStringLiteral("filename"), d->filename);
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

        InputFile input;

        if (json.contains(QStringLiteral("file_data"))) {
            if (const auto v = json.value(QStringLiteral("file_data")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                input.setFileData(v.toString());
        }

        if (json.contains(QStringLiteral("file_id"))) {
            if (const auto v = json.value(QStringLiteral("file_id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                input.setFileId(v.toString());
        }

        if (json.contains(QStringLiteral("file_url"))) {
            if (const auto v = json.value(QStringLiteral("file_url")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                input.setFileUrl(v.toString());
        }

        if (json.contains(QStringLiteral("filename"))) {
            if (const auto v = json.value(QStringLiteral("filename")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                input.setFilename(v.toString());
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("file_data"));
        extra.remove(QStringLiteral("file_id"));
        extra.remove(QStringLiteral("file_url"));
        extra.remove(QStringLiteral("type"));

        return input;
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const QString& fileId = {}, const QJsonObject& extra = {})
            : fileId{fileId}
            , extra{extra}
        {}
        Data(const QUrl& fileUrl = {}, const QJsonObject& extra = {})
            : fileUrl{fileUrl}
            , extra{extra}
        {}

        QString fileData;
        QString fileId;
        QString filename;
        QUrl fileUrl;
        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;
};

class InputAudio
{
public:
    [[nodiscard]] Type type() const { return Type::InputAudio; }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] bool operator==(const InputAudio& that) const
    {
        return d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const { return d->extra.isEmpty(); }
    [[nodiscard]] bool isValid() const { return false; }

    QJsonObject toJson() const
    {
        QJsonObject json = d->extra;
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

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));

        return input;
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const QJsonObject& extra = {})
            : extra{extra}
        {}

        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;
};

class MessageContentInputItem
{
public:
    MessageContentInputItem(
        const std::variant<InputText, InputImage, InputFile, InputAudio>& input = {},
        const QJsonObject& extra = {})
        : d{new Data{input, extra}}
    {}

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] bool isText() const { return d->input.index() == 0; }
    [[nodiscard]] bool isImage() const { return d->input.index() == 1; }
    [[nodiscard]] bool isFile() const { return d->input.index() == 2; }
    [[nodiscard]] bool isAudio() const { return d->input.index() == 3; }

    [[nodiscard]] InputText text() const
    {
        return isText() ? std::get<InputText>(d->input) : InputText{};
    }
    MessageContentInputItem& setText(const InputText& text)
    {
        std::get<InputText>(d->input) = text;
        return *this;
    }

    [[nodiscard]] InputImage image() const
    {
        return isImage() ? std::get<InputImage>(d->input) : InputImage{};
    }
    MessageContentInputItem& setImage(const InputImage& image)
    {
        std::get<InputImage>(d->input) = image;
        return *this;
    }

    [[nodiscard]] InputFile file() const
    {
        return isFile() ? std::get<InputFile>(d->input) : InputFile{};
    }
    MessageContentInputItem& setFile(const InputFile& file)
    {
        std::get<InputFile>(d->input) = file;
        return *this;
    }

    [[nodiscard]] InputAudio audio() const
    {
        return isAudio() ? std::get<InputAudio>(d->input) : InputAudio{};
    }
    MessageContentInputItem& setAudio(const InputAudio& audio)
    {
        std::get<InputAudio>(d->input) = audio;
        return *this;
    }

    [[nodiscard]] bool operator==(const MessageContentInputItem& that) const
    {
        return d->input == that.d->input && d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return (isText() && text().isEmpty()) || (isImage() && image().isEmpty())
               || (isFile() && file().isEmpty()) || (isAudio() && audio().isEmpty());
    }
    [[nodiscard]] bool isValid() const
    {
        return (isText() && text().isValid()) || (isImage() && image().isValid())
               || (isFile() && file().isValid()) || (isAudio() && audio().isValid());
    }

    QJsonObject toJson() const
    {
        if (isText())
            return text().toJson();
        if (isImage())
            return image().toJson();
        if (isFile())
            return file().toJson();
        if (isAudio())
            return audio().toJson();
        return {};
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

        return {};
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const std::variant<InputText, InputImage, InputFile, InputAudio>& input = {},
             const QJsonObject& extra = {})
            : input{input}
            , extra{extra}
        {}

        std::variant<InputText, InputImage, InputFile, InputAudio> input;
        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;
};

class MessageContentInputItemList : public QList<MessageContentInputItem>
{
public:
    MessageContentInputItemList(const QList<MessageContentInputItem>& items = {})
        : QList<MessageContentInputItem>{items}
    {}

    [[nodiscard]] ai::Type type() const { return ai::Type::MessageContentInputItemList; }

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
public:
    MessageContent(const std::variant<QString, MessageContentInputItemList>& data = {},
                   const QJsonObject& extra = {})
        : d{new Data{data, extra}}
    {}

    [[nodiscard]] Type type() const;

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] bool isText() const { return d->data.index() == 0; }
    [[nodiscard]] bool isItemList() const { return d->data.index() == 1; }

    [[nodiscard]] QString text() const { return isText() ? std::get<QString>(d->data) : QString{}; }
    MessageContent& setText(const QString& text)
    {
        if (isItemList())
            std::get<QString>(d->data) = text;
        return *this;
    }

    [[nodiscard]] MessageContentInputItemList items() const
    {
        return isItemList() ? std::get<MessageContentInputItemList>(d->data)
                            : MessageContentInputItemList{};
    }
    MessageContent& setItems(const MessageContentInputItemList& items)
    {
        if (isItemList())
            std::get<MessageContentInputItemList>(d->data) = items;
        return *this;
    }

    [[nodiscard]] bool operator==(const MessageContent& that) const
    {
        return d->data == that.d->data && d->extra == that.d->extra;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return (isText() && text().isEmpty()) || (isItemList() && items().isEmpty());
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
            return std::variant<QString, MessageContentInputItemList>{json.toString()};

        if (json.isArray())
            return {MessageContentInputItemList::fromJson(json.toArray(), ok)};

        if (ok)
            *ok = false;

        return {};
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const std::variant<QString, MessageContentInputItemList>& data = {},
             const QJsonObject& extra = {})
            : data(data)
            , extra{extra}
        {}

        std::variant<QString, MessageContentInputItemList> data;
        QJsonObject extra;
    };

    QSharedDataPointer<Data> d;
};

class Message
{
    Q_GADGET

public:
    enum struct Status { InProgress, Completed, Incomplete };
    Q_ENUM(Status)

    Message(const QJsonObject& extra = {})
        : Message{{}, {}, {}, {}, extra}
    {}
    Message(const MessageContent& content,
            const QString& role,
            Status status,
            const QJsonObject& extra = {})
        : Message{content, role, {}, status, extra}
    {}
    Message(const MessageContent& content,
            const QString& role = QStringLiteral("user"),
            const QString& id = {},
            Status status = Status::InProgress,
            const QJsonObject& extra = {})
        : d{new Data{content, role, id, status, extra}}
    {}

    [[nodiscard]] Type type() const { return Type::Message; }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }

    [[nodiscard]] QString role() const { return d->role; }
    Message& setRole(const QString& role)
    {
        if (role == QStringLiteral("assistant") || role == QStringLiteral("user")
            || role == QStringLiteral("tool") || role == QStringLiteral("system"))
            d->role = role;
        return *this;
    }

    [[nodiscard]] QString id() const { return d->id; }
    Message& setId(const QString& id)
    {
        d->id = id;
        return *this;
    }

    [[nodiscard]] Status status() const { return d->status; }
    Message& setStatus(Status status)
    {
        d->status = status;
        return *this;
    }
    Message& setStatus(const QString& status) { return setStatus(stringToStatus(status)); }

    [[nodiscard]] MessageContent content() const { return d->content; }
    Message& setContent(const MessageContent& content)
    {
        d->content = content;
        return *this;
    }

    [[nodiscard]] bool operator==(const Message& that) const { return d->extra == that.d->extra; }

    [[nodiscard]] bool isEmpty() const
    {
        return role().isEmpty() && content().isEmpty() && id().isEmpty()
               && status() == Status::InProgress;
    }
    [[nodiscard]] bool isValid() const { return !role().isEmpty() && !content().isValid(); }

    QJsonValue toJson() const
    {
        QJsonObject json = d->extra;
        json[QStringLiteral("type")] = QStringLiteral("message");
        json[QStringLiteral("role")] = d->role;
        json[QStringLiteral("status")] = statusToString(d->status);
        json[QStringLiteral("content")] = d->content.toJson();
        if (!d->id.isEmpty())
            json[QStringLiteral("id")] = d->id;
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

        QString id;
        MessageContent content;
        QString role;
        QString status;
        Message message;

        if (json.contains(QStringLiteral("role"))) {
            if (const auto v = json.value(QStringLiteral("role")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                role = v.toString();
        }

        if (json.contains(QStringLiteral("status"))) {
            if (const auto v = json.value(QStringLiteral("status")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                status = v.toString();
        }

        if (json.contains(QStringLiteral("id"))) {
            if (const auto v = json.value(QStringLiteral("id")); !v.isString()) {
                if (ok)
                    *ok = false;
            } else
                id = v.toString();
        }

        if (json.contains(QStringLiteral("content"))) {
            if (const auto v = json.value(QStringLiteral("content")); !v.isArray())
                content = MessageContent::fromJson(v.toArray());
            else if (v.isString())
                content = MessageContent::fromJson(v.toString());
            else {
                if (ok)
                    *ok = false;
            }
        }

        QJsonObject extra = json;
        extra.remove(QStringLiteral("type"));
        extra.remove(QStringLiteral("role"));
        extra.remove(QStringLiteral("id"));
        extra.remove(QStringLiteral("status"));
        extra.remove(QStringLiteral("content"));

        return {content, role, id, stringToStatus(status), extra};
    }

    [[nodiscard]] static QString statusToString(Status status) { return mStatuses.value(status); }
    [[nodiscard]] static Status stringToStatus(const QString& status)
    {
        return mStatuses.key(status);
    }

private:
    class Data : public QSharedData
    {
    public:
        Data(const MessageContent& content = {},
             const QString& role = {},
             const QString& id = {},
             Status status = Status::InProgress,
             const QJsonObject& extra = {})
            : role{role}
            , status{status}
            , id{id}
            , content{content}
            , extra{extra}
        {}

        QString role = QStringLiteral("user");
        Status status = Status::InProgress;
        QString id;
        MessageContent content;
        QJsonObject extra;
    };

    inline static const QMap<Status, QString> mStatuses = {{Status::InProgress, "in_progress"},
                                                           {Status::Completed, "completed"},
                                                           {Status::Incomplete, "incomplete"}};

    QSharedDataPointer<Data> d;
};

class StreamOptions
{
    Q_GADGET
    Q_PROPERTY(bool includeObfuscation READ includeObfuscation WRITE setIncludeObfuscation)

public:
    StreamOptions(const QJsonObject& extra = {})
        : StreamOptions{false, extra}
    {}
    StreamOptions(bool includeObfuscation, const QJsonObject& extra = {})
        : d{new Data{includeObfuscation, extra}}
    {}

    [[nodiscard]] bool includeObfuscation() const { return d->includeObfuscation; }
    void setIncludeObfuscation(bool includeObfuscation)
    {
        d->includeObfuscation = includeObfuscation;
    }

    [[nodiscard]] QJsonObject extra() const { return d->extra; }
    // void setExtra(const QJsonObject& extra) { d->extra = extra; }

    [[nodiscard]] bool operator==(const StreamOptions& that) const
    {
        return d->includeObfuscation == that.d->includeObfuscation;
    }

    [[nodiscard]] bool isEmpty() const { return !d->includeObfuscation && d->extra.isEmpty(); }
    [[nodiscard]] bool isValid() const { return true; }

    QJsonObject toJson() const
    {
        QJsonObject json = d->extra;
        json.insert(QStringLiteral("include_obfuscation"), d->includeObfuscation);
        return json;
    }

    static StreamOptions fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        bool includeObfuscation = false;

        if (const auto v = json.value(QStringLiteral("include_obfuscation")); v.isBool())
            includeObfuscation = v.toBool();
        else if (ok)
            *ok = false;

        QJsonObject extra = json;
        extra.remove(QStringLiteral("include_obfuscation"));

        return {includeObfuscation, extra};
    }

private:
    struct Data : public QSharedData
    {
        Data(bool includeObfuscation = false, const QJsonObject& extra = {})
            : includeObfuscation{includeObfuscation}
            , extra{extra}
        {}

        bool includeObfuscation = false;
        QJsonObject extra;
    };

    QSharedPointer<Data> d;
};

} // namespace ai

#endif // HELPERS_H
