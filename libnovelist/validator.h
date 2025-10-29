#ifndef LIBNOVELIST_VALIDATOR_H
#define LIBNOVELIST_VALIDATOR_H

#include <QJsonObject>
#include <QObject>
#include "field.h"

namespace novelist {

/*
class Validator : public QObject
{
    Q_OBJECT

public:
    Validator(QObject *parent = nullptr)
        : QObject{parent}
    {}

    QLocale locale() const { return mLocale; }
    void setLocale(const QLocale &locale)
    {
        if (mLocale == locale)
            return;
        mLocale = locale;
    }

    virtual bool fixup(FieldRow &row, QStringList *messages = nullptr) const = 0;
    virtual bool validate(FieldRow &row, QStringList *messages = nullptr) const = 0;

    [[nodiscard]] virtual QJsonObject toJson(bool *error = nullptr) const = 0;
    virtual bool setJson(const QJsonObject &json) = 0;

    [[nodiscard]] virtual QJsonObject toSchema(bool *error = nullptr) const = 0;

    [[nodiscard]] bool required() const { return mRequired; }
    void setRequired(bool required)
    {
        if (mRequired == required)
            return;
        mRequired = required;
    }

private:
    QLocale mLocale;
    bool mRequired = false;
};

class StringValidator : public Validator
{
public:
    StringValidator(QObject *parent = nullptr)
        : StringValidator{-1, -1, parent}
    {}
    StringValidator(int minLength, int maxLength, QObject *parent = nullptr)
        : Validator{parent}
        , minLength{minLength}
        , maxLength{maxLength}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        auto string = row.value.toString();

        bool valid = true;

        if (minLength >= 0 && string.size() < minLength) {
            if (messages)
                messages->append(QStringLiteral("Too short, needs at least %1 characters.")
                                     .arg(minLength));
            valid = false;
        }

        if (maxLength >= 0 && string.size() > maxLength) {
            string.resize(maxLength);
            if (messages)
                messages->append("Too long: enforced maxLength");
            string.resize(maxLength);
        }

        row.value = string;

        return valid;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        auto string = row.value.toString().trimmed();

        if (minLength >= 0 && string.size() < minLength) {
            if (messages)
                messages
                    ->append(QStringLiteral("Too short, at least %1 characters.").arg(minLength));
            return false;
        }

        if (maxLength >= 0 && string.size() > maxLength) {
            if (messages)
                messages->append(QStringLiteral("Too long, at most %1 characters.").arg(maxLength));
            return false;
        }

        if (required() && string.isEmpty()) {
            if (messages)
                messages->append(QStringLiteral("Required."));
            return false;
        }

        row.value = string;
        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "StringValidator";
        json["minLength"] = minLength;
        json["maxLength"] = maxLength;
        json["locale"] = locale().name();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "StringValidator")
            return false;

        if (const auto v = json.value("minLength"); v.isDouble())
            minLength = std::max(-1, std::min(1024 * 1024 * 128, v.toInt()));
        else
            minLength = -1;

        if (const auto v = json.value("maxLength"); v.isDouble())
            maxLength = std::max(-1, std::min(1024 * 1024 * 128, v.toInt()));
        else
            maxLength = -1;

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;

    int minLength = -1;
    int maxLength = -1;
};

class IntValidator : public Validator
{
public:
    IntValidator(QObject *parent = nullptr)
        : IntValidator{-1, -1, parent}
    {}
    IntValidator(int minLength, int maxLength, QObject *parent = nullptr)
        : Validator{parent}
        , min{minLength}
        , max{maxLength}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        int value = row.value.toInt();
        bool valid = true;

        if (value < min) {
            if (messages)
                messages->append("Enforced minimum");
            value = min;
        }

        if (value > max) {
            if (messages)
                messages->append("Enforced maximum");
            value = max;
        }

        row.value = value;

        return valid;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        int value = row.value.toInt();

        if (value < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min));
            return false;
        }

        if (value > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max));
            return false;
        }

        row.value = value;
        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "IntValidator";
        json["min"] = min;
        json["max"] = max;
        json["locale"] = locale().name();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "IntValidator")
            return false;

        if (const auto v = json.value("min"); v.isDouble())
            min = v.toInt();
        else
            min = std::numeric_limits<int>::min();

        if (const auto v = json.value("max"); v.isDouble())
            max = v.toInt();
        else
            max = std::numeric_limits<int>::max();

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;

    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();
};

class DoubleValidator : public Validator
{
public:
    DoubleValidator(QObject *parent = nullptr)
        : DoubleValidator{-1, -1, parent}
    {}
    DoubleValidator(double minLength, double maxLength, QObject *parent = nullptr)
        : Validator{parent}
        , min{minLength}
        , max{maxLength}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        double value = row.value.toDouble();
        bool valid = false;

        if (value < min) {
            value = min;
            if (messages)
                messages->append("Enforced minimum");
            value = min;
        }

        if (value > max) {
            if (messages)
                messages->append("Enforced maximum");
            value = max;
        }

        row.value = value;

        return valid;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        double value = row.value.toDouble();

        if (value < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min));
            return false;
        }

        if (value > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max));
            return false;
        }

        row.value = value;
        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "DoubleValidator";
        json["min"] = min;
        json["max"] = max;
        json["locale"] = locale().name();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "DoubleValidator")
            return false;

        if (const auto v = json.value("min"); v.isDouble())
            min = v.toDouble();
        else
            min = std::numeric_limits<double>::min();

        if (const auto v = json.value("max"); v.isDouble())
            max = v.toDouble();
        else
            max = std::numeric_limits<double>::max();

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;

    double min = -1;
    double max = -1;
};

class BoolValidator : public Validator
{
public:
    BoolValidator(QObject *parent = nullptr)
        : Validator{parent}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        if (required() && !row.value.isValid()) {
            if (messages)
                messages->append(QStringLiteral("Required."));
            row.value = false;
        }

        if (row.value.typeId() != qMetaTypeId<bool>()) {
            if (messages)
                messages->append(QStringLiteral("Converted."));
            row.value = row.value.toBool();
        }

        return true;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        if (required() && !row.value.isValid()) {
            if (messages)
                messages->append(QStringLiteral("Required."));
            return false;
        }

        if (row.value.typeId() != qMetaTypeId<bool>()) {
            if (messages)
                messages->append(QStringLiteral("Converted."));
            row.value = row.value.toBool();
        }

        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "BoolValidator";
        json["locale"] = locale().name();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "BoolValidator")
            return false;

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;
};

class DateValidator : public Validator
{
public:
    DateValidator(QObject *parent = nullptr)
        : DateValidator{{}, {}, parent}
    {}
    DateValidator(const QDate &min, const QDate &max, QObject *parent = nullptr)
        : Validator{parent}
        , min{min}
        , max{max}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        QDate date = row.value.toDate();

        if (date.isNull()) {
            if (required()) {
                if (messages)
                    messages->append(QStringLiteral("Date is required."));
                return false;
            }
            return true;
        }

        if (!date.isValid()) {
            if (messages)
                messages->append("Date is invalid: clearing date.");
            row.value = {};
            return true;
        }

        if (min.isValid() && date < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min.toString()));
            row.value = min;
        }

        if (max.isValid() && date > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max.toString()));
            row.value = max;
        }

        return true;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        QDate date = row.value.toDate();

        if (date.isNull()) {
            if (required()) {
                if (messages)
                    messages->append(QStringLiteral("Required."));
                return false;
            }
            return true;
        }

        if (!date.isValid()) {
            if (messages)
                messages->append("Date is invalid.");
            return false;
        }

        if (min.isValid() && date < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min.toString()));
            return false;
        }

        if (max.isValid() && date > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max.toString()));
            return false;
        }

        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "DateValidator";
        json["locale"] = locale().name();

        if (min.isValid())
            json["min"] = min.toString();

        if (max.isValid())
            json["max"] = max.toString();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "DateValidator")
            return false;

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        if (const auto v = json.value("min"); v.isString())
            min = QDate::fromString(v.toString());

        if (const auto v = json.value("max"); v.isString())
            max = QDate::fromString(v.toString());

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;

    QDate min;
    QDate max;
};

class TimeValidator : public Validator
{
public:
    TimeValidator(QObject *parent = nullptr)
        : TimeValidator{{}, {}, parent}
    {}
    TimeValidator(const QTime &min, const QTime &max, QObject *parent = nullptr)
        : Validator{parent}
        , min{min}
        , max{max}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        QTime time = row.value.toTime();

        if (time.isNull()) {
            if (required()) {
                if (messages)
                    messages->append(QStringLiteral("Time is required."));
                return false;
            }
            return true;
        }

        if (!time.isValid()) {
            if (messages)
                messages->append("Time is invalid: clearing time.");
            row.value = {};
            return true;
        }

        if (min.isValid() && time < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min.toString()));
            row.value = min;
        }

        if (max.isValid() && time > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max.toString()));
            row.value = max;
        }

        return true;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        QTime time = row.value.toTime();

        if (time.isNull()) {
            if (required()) {
                if (messages)
                    messages->append(QStringLiteral("Required."));
                return false;
            }
            return true;
        }

        if (!time.isValid()) {
            if (messages)
                messages->append("Time is invalid.");
            return false;
        }

        if (min.isValid() && time < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min.toString()));
            return false;
        }

        if (max.isValid() && time > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max.toString()));
            return false;
        }

        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "TimeValidator";
        json["locale"] = locale().name();

        if (min.isValid())
            json["min"] = min.toString();

        if (max.isValid())
            json["max"] = max.toString();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "TimeValidator")
            return false;

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        if (const auto v = json.value("min"); v.isString())
            min = QTime::fromString(v.toString());

        if (const auto v = json.value("max"); v.isString())
            max = QTime::fromString(v.toString());

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;

    QTime min;
    QTime max;
};

class DateTimeValidator : public Validator
{
public:
    DateTimeValidator(QObject *parent = nullptr)
        : DateTimeValidator{{}, {}, parent}
    {}
    DateTimeValidator(const QDateTime &min, const QDateTime &max, QObject *parent = nullptr)
        : Validator{parent}
        , min{min}
        , max{max}
    {}

    bool fixup(FieldRow &row, QStringList *messages = nullptr) const override
    {
        QDateTime dateTime = row.value.toDateTime();

        if (dateTime.isNull()) {
            if (required()) {
                if (messages)
                    messages->append(QStringLiteral("DateTime is required."));
                return false;
            }
            return true;
        }

        if (!dateTime.isValid()) {
            if (messages)
                messages->append("DateTime is invalid: clearing dateTime.");
            row.value = {};
            return true;
        }

        if (min.isValid() && dateTime < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min.toString()));
            row.value = min;
        }

        if (max.isValid() && dateTime > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max.toString()));
            row.value = max;
        }

        return true;
    }
    bool validate(FieldRow &row, QStringList *messages = nullptr) const override
    {
        QDateTime dateTime = row.value.toDateTime();

        if (dateTime.isNull()) {
            if (required()) {
                if (messages)
                    messages->append(QStringLiteral("Required."));
                return false;
            }
            return true;
        }

        if (!dateTime.isValid()) {
            if (messages)
                messages->append("DateTime is invalid.");
            return false;
        }

        if (min.isValid() && dateTime < min) {
            if (messages)
                messages->append(QStringLiteral("Too low, minimum is %1.").arg(min.toString()));
            return false;
        }

        if (max.isValid() && dateTime > max) {
            if (messages)
                messages->append(QStringLiteral("Too high, maximum is %1.").arg(max.toString()));
            return false;
        }

        return true;
    }

    [[nodiscard]] QJsonObject toJson(bool *error = nullptr) const override
    {
        QJsonObject json;

        json["type"] = "DateTimeValidator";
        json["locale"] = locale().name();

        if (min.isValid())
            json["min"] = min.toString();

        if (max.isValid())
            json["max"] = max.toString();

        if (error)
            *error = false;

        return json;
    }
    bool setJson(const QJsonObject &json) override
    {
        if (json.value("type").toString() != "DateTimeValidator")
            return false;

        if (const auto v = json.value("locale"); v.isString())
            setLocale(QLocale{v.toString()});

        if (const auto v = json.value("min"); v.isString())
            min = QDateTime::fromString(v.toString());

        if (const auto v = json.value("max"); v.isString())
            max = QDateTime::fromString(v.toString());

        return true;
    }

    [[nodiscard]] QJsonObject toSchema(bool *error = nullptr) const override;

    QDateTime min;
    QDateTime max;
};
*/

} // namespace novelist

#endif // LIBNOVELIST_VALIDATOR_H
