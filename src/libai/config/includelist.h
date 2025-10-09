#ifndef AI_CONFIG_INCLUDELIST_H
#define AI_CONFIG_INCLUDELIST_H

#include "stringlist.h"

namespace ai {

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

    static StringList fromJson(const QJsonArray& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = true;

        IncludeList list;

        for (const auto& i : json)
            list.addInclude(list.toInclude(i.toString()));

        return list;
    }

    [[nodiscard]] ai::AiObjectType objectType() const { return ai::AiObjectType::StringList; }

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

} // namespace ai

#endif // AI_CONFIG_INCLUDELIST_H
