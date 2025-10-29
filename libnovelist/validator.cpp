#include "validator.h"
#include "element.h"
#include "field.h"

namespace novelist {

/*
QJsonObject StringValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("string");

    schema["minLength"] = minLength;
    schema["maxLength"] = maxLength;

    if (error)
        *error = false;

    return schema;
}

QJsonObject IntValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("int");

    schema["min"] = min;
    schema["max"] = max;

    if (error)
        *error = false;

    return schema;
}

QJsonObject DoubleValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("double");

    schema["min"] = min;
    schema["max"] = max;

    if (error)
        *error = false;

    return schema;
}

QJsonObject BoolValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("bool");

    if (error)
        *error = false;

    return schema;
}

QJsonObject DateValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("date");

    schema["min"] = min.toString();
    schema["max"] = max.toString();

    if (error)
        *error = false;

    return schema;
}

QJsonObject TimeValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("time");

    schema["min"] = min.toString();
    schema["max"] = max.toString();

    if (error)
        *error = false;

    return schema;
}

QJsonObject DateTimeValidator::toSchema(bool *error) const
{
    auto schema = Field::typeSchema("datetime");

    schema["min"] = min.toString();
    schema["max"] = max.toString();

    if (error)
        *error = false;

    return schema;
}
*/

} // namespace novelist
