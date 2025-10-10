#ifndef AI_CONFIG_TOOLS_H
#define AI_CONFIG_TOOLS_H

#include "empty.h"

namespace ai {

/*
class ImageGenerationTool
{
    Q_GADGET
    Q_PROPERTY(ai::UtilityType utilityType READ utilityType CONSTANT FINAL)
    Q_PROPERTY(QString type READ type CONSTANT FINAL)
    Q_PROPERTY(QString refusal READ refusal WRITE setImageGenerationTool FINAL)
    Q_PROPERTY(QJsonObject extra READ extra FINAL)
    Q_PROPERTY(bool empty READ isEmpty FINAL)
    Q_PROPERTY(bool valid READ isValid FINAL)

public:
    enum Background { Background_Auto, Background_Transparent, Background_Opaque };
    enum InputFidelity { InputFidelity_High, InputFidelity_Low };
    enum OutputFormat { OutputFormat_Png, OutputFormat_Jpeg, OutputFormat_Webp };
    enum Quality { Quality_Auto, Quality_Low, Quality_Medium, Quality_High };
    enum Size { Size_Auto, Size_1024x1024, Size_1024x1536, Size_1536x1024 };

    ImageGenerationTool(const QJsonObject& extra = {})
        : x{extra}
    {}
    ImageGenerationTool(const QString& refusal, const QJsonObject& extra = {})
        : r{refusal}
        , x{extra}
    {}

    [[nodiscard]] QString type() const { return QStringLiteral("image_generation"); }

    [[nodiscard]] ai::Type utilityType() const { return UtilityType_ImageGenerationTool; }

    [[nodiscard]] QJsonObject extra() const { return x; }

    [[nodiscard]] Background background() const { return b; }
    void setBackground(Background background) { b = background; }

    [[nodiscard]] InputFidelity inputFidelity() const { return i; }
    void setInputFidelity(InputFidelity inputFidelity) { i = inputFidelity; }

    [[nodiscard]] QString inputImageMaskFile() const { return iimF; }
    void setInputImageMaskFile(const QString& inputImageMaskFile) { iimF = inputImageMaskFile; }

    [[nodiscard]] QString inputImageMaskUrl() const { return iimU; }
    void setInputImageMaskUrl(const QString& inputImageMaskUrl) { iimU = inputImageMaskUrl; }

    [[nodiscard]] QString model() const { return mModel; }
    void setModel(const QString& model) { mModel = model; }

    [[nodiscard]] QString moderation() const { return mModeration; }
    void setModeration(const QString& moderation) { mModeration = moderation; }

    [[nodiscard]] int outputCompression() const { return oc; }
    void setOutputCompression(int outputCompression) { oc = outputCompression; }

    [[nodiscard]] OutputFormat outputFormat() const { return of; }
    void setOutputFormat(OutputFormat outputFormat) { of = outputFormat; }

    [[nodiscard]] int partialImages() const { return pi; }
    void setPartialImages(int partialImages) { pi = partialImages; }

    [[nodiscard]] Quality quality() const { return q; }
    void setQuality(Quality quality) { q = quality; }

    [[nodiscard]] Size size() const { return s; }
    void setSize(Size size) { s = size; }

    [[nodiscard]] bool operator==(const ImageGenerationTool& that) const
    {
        return b == that.b
               && i == that.i
               && of == that.of
               && q == that.q
               && s == that.s
               && iimF == that.iimF
               && iimU == that.iimU
               && mModel == that.mModel
               && mModeration == that.mModeration
               && oc == that.oc
               && pi == that.pi;
    }

    [[nodiscard]] bool isEmpty() const { return r.isEmpty() && e.isEmpty(); }
    [[nodiscard]] bool isValid() const { return true; }

    QJsonObject toJson() const
    {
        QJsonObject json = x;
        json[QStringLiteral("type")] = QStringLiteral("image_generation");
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

        if (const auto v = json.value(QStringLiteral("background")); v.isString()) {
            tool.b = v.toString();
            x.remove(QStringLiteral("background"));
        } else if (ok)
            *ok = false;

        tool.x = x;

        return tool;
    }

private:
    Background b = Background_Auto;
    InputFidelity i = InputFidelity_High;
    OutputFormat of = OutputFormat_Png;
    Quality q = Quality_Auto;
    Size s = Size_Auto;
    QString iimF;
    QString iimU;
    QString mModel;
    QString mModeration;
    int oc = 0;
    int pi = 0;
    QJsonObject x;
};

class Tool
{
    Q_GADGET
    Q_PROPERTY(ImageGenerationTool imageGeneration READ imageGeneration WRITE setImageGeneration)

    using Variant = std::variant<Empty, ImageGenerationTool>;

    Variant d;

public:
    Tool()
        : Tool{Empty{}}
    {}
    Tool(const Variant& data)
        : d{data}
    {}

    [[nodiscard]] bool isImageGeneration() const { return d.index() == 1; }

    [[nodiscard]] ImageGenerationTool imageGeneration() const
    {
        return isImageGeneration() ? std::get<ImageGenerationTool>(d) : ImageGenerationTool{};
    }
    void setImageGeneration(const ImageGenerationTool& imageGeneration)
    {
        if (imageGeneration.isEmpty())
            d = Empty{};
        else
            d = imageGeneration;
    }

    [[nodiscard]] bool operator==(const Tool& that) const { return d == that.d; }

    [[nodiscard]] bool isEmpty() const
    {
        return d.index() == 0 || (isImageGeneration() && imageGeneration().isEmpty());
    }
    [[nodiscard]] bool isValid() const
    {
        return (isImageGeneration() && !imageGeneration().isValid());
    }

    QJsonValue toJson() const
    {
        if (isImageGeneration())
            return imageGeneration().toJson();

        return {};
    }

    static Tool fromJson(const QJsonObject& json, bool* ok = nullptr)
    {
        if (ok)
            *ok = false;

        Tool tool;

        if (const auto v = json.value(QStringLiteral("type")); v.isString()) {
            if (const auto type = v.toString(); type == "image_generation") {
                tool.d = ImageGenerationTool::fromJson(json, ok);
                if (ok)
                    *ok = true;
            }
        }

        return tool;
    }
};

class Tools : public QList<Tool>
{
    Q_GADGET
};
*/

} // namespace ai

#endif // AI_CONFIG_TOOLS_H
