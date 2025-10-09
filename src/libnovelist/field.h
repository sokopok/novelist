#ifndef NOVELIST_FIELD_H
#define NOVELIST_FIELD_H

#include <QObject>
#include "node.h"
#include "projectstore.h"

namespace novelist {

class Validator;

class Field : public Node
{
    Q_OBJECT

public:
    explicit Field(QObject *parent = nullptr)
        : Field{{}, {}, parent}
    {}
    explicit Field(const QString &type, Element *element = nullptr, QObject *parent = nullptr)
        : Node{parent}
        , mElement{element}
        , mType{type}
        , mTypes{{type}}
    {}

    [[nodiscard]] Element *element() const { return mElement; }
    void setElement(Element *element);

    [[nodiscard]] bool isDefault() const { return flags() & DefaultFlag; }

    bool validate(const QVariant &value, QStringList *messages = nullptr) const;
    bool validate(QStringList *messages = nullptr)
    {
        QStringList m;
        if (!messages)
            messages = &m;
        if (!validate(mValue, messages)) {
            setValid(false);
            emit validationErrorOccurred(m, QPrivateSignal{});
            return false;
        }
        setValid(true);
        emit validated(QPrivateSignal{});
        return true;
    }

    QVariant fixup(const QVariant &value, QStringList *messages = nullptr) const;
    bool fixup(QStringList *messages = nullptr)
    {
        QStringList m;
        if (!messages)
            messages = &m;
        mValue = fixup(mValue, messages);
        if (!m.isEmpty()) {
            emit validationErrorOccurred(m, QPrivateSignal{});
            return false;
        }
        emit fixedUp(QPrivateSignal{});
        return true;
    }

    virtual QVariant toDisplay(const QVariant &value) const { return value; }
    virtual QVariant toStorage(const QVariant &value) const { return value; }

    [[nodiscard]] QVariant value() const { return mValue; }
    void setValue(const QVariant &value) { setValue(value, SetExplicit); }
    void resetValue() { resetValue(SetExplicit); }

    virtual void setValue(const QVariant &value, ExplicitHandling e);
    virtual void resetValue(ExplicitHandling e) { setValue(defaultValue(), e); }

    [[nodiscard]] QVariant defaultValue() const { return mDefaultValue; }
    virtual void setDefaultValue(const QVariant &defaultValue);

    [[nodiscard]] QString type() const { return mType; }
    void setType(const QString &type);

    [[nodiscard]] QStringList types() const { return mTypes; }
    void setTypes(const QStringList &types);

    [[nodiscard]] QMap<QString, Validator *> validators() const { return mValidators; }
    void setValidators(const QMap<QString, Validator *> &validators)
    {
        if (mValidators == validators)
            return;
        mValidators = validators;
        emit validatorsChanged(QPrivateSignal{});
    }

    [[nodiscard]] Q_INVOKABLE Validator *validator(const QString &type) const
    {
        return mValidators.value(type);
    }
    Q_INVOKABLE bool addValidator(const QString &type, Validator *validator)
    {
        if (type.isEmpty()) {
            setError({ai::Error::InternalErrorType, ai::Error::InternalError, "addValidator"});
            return false;
        }

        if (!validator) {
            setError({ai::Error::InternalErrorType, ai::Error::InternalError, "addValidator"});
            return false;
        }

        if (mValidators.contains(type)) {
            if (this->validator(type) == validator)
                return true;
            setError({ai::Error::InternalErrorType, ai::Error::InternalError, "addValidator"});
            return false;
        }

        mValidators[type] = validator;

        emit validatorsChanged(QPrivateSignal{});
        return true;
    }
    [[nodiscard]] Q_INVOKABLE Validator *takeValidator(const QString &type)
    {
        if (auto *v = mValidators.take(type)) {
            emit validatorsChanged(QPrivateSignal{});
            return v;
        }
        return nullptr;
    }

    [[nodiscard]] Q_INVOKABLE QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json = Node::toJson(error);

        if (error && *error)
            return {};

        json["type"] = mType;

        if (explicits().testBit(ValueTag))
            json["value"] = QJsonValue::fromVariant(mValue);

        if (explicits().testBit(DefaultTag))
            json["default"] = QJsonValue::fromVariant(mDefaultValue);

        json["valid"] = isValid();
        json["empty"] = isEmpty();

        if (error)
            *error = false;

        return json;
    }
    Q_INVOKABLE bool setJson(const QJsonObject &json) override;

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;
    bool setSchema(const QJsonObject &json) override
    {
        if (!Node::setSchema(json))
            return false;

        // if (const auto v = json.value("icon"); v.isString())
        //     setIcon(v.toString());

        return true;
    }

    bool reload() override;
    bool save() override;

    static QJsonObject typeSchema(const QString type) { return mTypeSchemas.value(type); }
    static bool addTypeSchema(const QString &type, const QJsonObject &schema)
    {
        if (type.isEmpty() || schema.isEmpty() || mTypeSchemas.contains(type))
            return false;
        mTypeSchemas[type] = schema;
        return true;
    }
    static bool putTypeSchema(const QString &type, const QJsonObject &schema)
    {
        if (type.isEmpty() || schema.isEmpty())
            return false;
        mTypeSchemas[type] = schema;
        return true;
    }
    static QJsonObject takeTypeSchema(const QString &type) { return mTypeSchemas.take(type); }

signals:
    void elementChanged(QPrivateSignal);
    void valueChanged(QPrivateSignal);
    void defaultValueChanged(QPrivateSignal);

    void validationErrorOccurred(const QStringList &messages, QPrivateSignal);
    void validated(QPrivateSignal);
    void fixedUp(QPrivateSignal);

    void defaultChanged(QPrivateSignal);
    void typesChanged(QPrivateSignal);
    void typeChanged(QPrivateSignal);
    void validatorsChanged(QPrivateSignal);

protected:
    enum Tag { ValueTag = Node::NumTags, DefaultTag };
    enum Flag { DefaultFlag = bit(std::to_underlying(Node::NumFlags)), NumFlags };

    inline static QMap<QString, QJsonObject> mTypeSchemas;

private:
    Element *mElement = nullptr;
    QVariant mValue;
    QVariant mDefaultValue;
    QString mType;
    QStringList mTypes;
    int mVersion = 0;
    QDateTime mLastModified;
    QString mAuthor;
    QMap<QString, Validator *> mValidators;

    Q_PROPERTY(Element *element READ element WRITE setElement NOTIFY elementChanged FINAL)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY
                   defaultValueChanged FINAL)
    Q_PROPERTY(QStringList types READ types WRITE setTypes NOTIFY typesChanged FINAL)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QMap<QString, Validator *> validators READ validators WRITE setValidators NOTIFY
                   validatorsChanged FINAL)
};

} // namespace novelist

#endif // NOVELIST_FIELD_H
