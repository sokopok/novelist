#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "libai/imagesclient.h"
#include "libai/responsesclient.h"
#include "libnovelist/novelist.h"
#include "libnovelist/storage.h"

#include <QtQml/QQmlExtensionPlugin>
#include <qsqldatabase.h>
Q_IMPORT_QML_PLUGIN(libaiPlugin)

void testStorage1(Storage *storage)
{
    ElementType *storyElement = storage->elementTypeStorage()->createElementType("story", "Story");

    FieldType *titleField = storage->fieldTypeStorage()->createFieldType("title", "Title");
    titleField->setAllowedTypes({qMetaTypeId<QString>()});
    storyElement->appendFieldType(titleField);

    FieldType *subtitleField = storage->fieldTypeStorage()->createFieldType("subtitle", "Subtitle");
    subtitleField->setAllowedTypes({qMetaTypeId<QString>()});
    storyElement->appendFieldType(subtitleField);

    ValueType *valueType = storage->valueTypeStorage()->createValueType("value", "Value");
    titleField->appendValueType(valueType);
    subtitleField->appendValueType(valueType);

    storyElement->save();

    Element *story = storage->elementStorage()->createElement(storyElement);

    Field *field = storage->fieldStorage()->createField(titleField);
    story->appendField(field);

    Value *value = storage->valueStorage()->createValue(valueType);
    value->setValue("An interesting story...");
    field->appendValue(value);

    value = storage->valueStorage()->createValue(valueType);
    value->setValue("An interesting story...");
    field->appendValue(value);

    field = storage->fieldStorage()->createField(subtitleField);
    story->appendField(field);

    story->save();
}

void testStorage2(Storage *storage)
{
    Element *story = storage->elementStorage()->element(4);
    Value *value = story->field(0)->value(0);
    value->setValue(QDateTime::currentDateTime());
    value->save();
}

void testAi()
{
    // ai::ResponsesRequest request;
    // request.setModel(ai::ResponsesRequest::Model_Gpt5);
    // request.setInput(
    //     {"Burn! A monkey wearing a tracksuit wants to show off his brand new unicycle on "
    //      "the moon, but there is no gravity so he floats around, sprawling awkwardly."});

    // // ai::ImageGenerationTool imageGeneration;
    // // imageGeneration.setQuality(ai::ImageGenerationTool::Quality_Low);
    // // request.setTools({{imageGeneration}});

    // ai::ResponsesClient client;
    // QObject::connect(&client, &ai::ResponsesClient::errorOccurred, [](const ai::Error &e) {
    //     qDebug().noquote().nospace()
    //         << "ai::responses::Client::errorOccurred "
    //         << QJsonDocument{e.toJson()}.toJson();
    // });
    // QObject::connect(&client,
    //                  &ai::ResponsesClient::responseTextGenerated,
    //                  [](ai::Response *response, const QString &text) {
    //                      qDebug().noquote().nospace() << text;
    //                  });
    // QObject::connect(
    //     &client,
    //     &ai::ResponsesClient::responseImageGenerated,
    //     [](ai::Response *response, const QImage &image) {
    //         qDebug().noquote().nospace() << image.format();
    //         image.save(
    //             QStringLiteral("../../../%1.%2").arg(QDateTime::currentMSecsSinceEpoch()).arg("png"));
    //     });

    // if (auto *response = client.post(request)) {
    //     QObject::connect(response, &ai::ResponsesResponse::errorOccurred, [](const ai::Error &e) {
    //         qDebug().noquote().nospace()
    //             << "ai::responses::Response::errorOccurred "
    //             << QJsonDocument{e.toJson()}.toJson();
    //     });
    //     QObject::connect(response, &ai::ResponsesResponse::finished, [response]() {
    //         qDebug().noquote().nospace()
    //             << "ai::responses::Response::errorOccurred "
    //             << QJsonDocument{response->toJson()}.toJson();
    //     });
    // }

    // ai::images::Request imageRequest;
    // imageRequest.resetModel();
    // imageRequest.setSize(ai::images::Request::Size_256x256);
    // imageRequest.setPrompt(
    //     "A monkey wearing a tracksuit showing off his brand new unicycle on the moon.");
    // // qDebug() << imageRequest.toJson(true);

    // auto *imageClient = ai::images::Client::create();
    // QObject::connect(imageClient, &ai::images::Client::errorOccurred, [](const ai::Error &e) {
    //     qDebug().noquote().nospace()
    //         << "ai::images::Client::errorOccurred "
    //         << QJsonDocument{e.toJson()}.toJson();
    // });

    // if (auto *response = imageClient->post(imageRequest)) {
    //     QObject::connect(response, &ai::images::Response::errorOccurred, [](const ai::Error &e) {
    //         qDebug().noquote().nospace()
    //             << "ai::images::Response::errorOccurred "
    //             << QJsonDocument{e.toJson()}.toJson();
    //     });

    //     // qDebug() << response->toJson();
    // }
}

void testNovelist1(Storage *storage)
{
    FieldType *titleFieldType = storage->fieldTypeStorage()->createFieldType("Title", "Title");
    titleFieldType->setAllowedTypes({qMetaTypeId<QString>()});

    FieldType *subtitleFieldType = storage->fieldTypeStorage()->createFieldType("Subtitle",
                                                                                "Subtitle");
    subtitleFieldType->setAllowedTypes({qMetaTypeId<QString>()});

    ValueType *stringValueType = storage->valueTypeStorage()->createValueType("String", "String");
    titleFieldType->appendValueType(stringValueType);
    subtitleFieldType->appendValueType(stringValueType);

    FieldType *storiesFieldType = storage->fieldTypeStorage()->createFieldType("Stories", "Stories");
    storiesFieldType->setAllowedTypes({qMetaTypeId<QList<Element *>>()});

    ValueType *storyValueType = storage->valueTypeStorage()->createValueType("Story", "Story");
    storiesFieldType->appendValueType(storyValueType);

    ElementType *storyElementType = storage->elementTypeStorage()->createElementType("Story",
                                                                                     "Story");
    storyElementType->appendFieldType(titleFieldType);
    storyElementType->appendFieldType(subtitleFieldType);

    ProjectType *projectType = storage->projectTypeStorage()->createProjectType("Project",
                                                                                "Project");
    projectType->appendFieldType(titleFieldType);
    projectType->appendFieldType(subtitleFieldType);
    projectType->appendFieldType(storiesFieldType);

    storyElementType->save();
    projectType->save();
}
void testNovelist2(Novelist *novelist)
{
    Project *project = novelist->storage()->projectStorage()->createProject("Project");
    novelist->setProject(project);

    project->field("Title")->appendValue("String", "Kira");
    project->field("Title")->appendValue("String", "A space novella");

    Element *storyElement = project->addElement(project->elementType("Story"));

    storyElement->field("Title")->appendValue("String", "An interesting story...");
    storyElement->field("Title")->appendValue("String", "An extremely interesting story...");

    project->field("Stories")->appendValue("Story", QVariant::fromValue(storyElement));

    qDebug() << "BEFORE SAVE";
    project->save();
    qDebug() << "AFTER SAVE";
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFile::remove("../../project.sqlite");

    Storage storage;

    if (!storage.openDatabase("../../project.sqlite"))
        return -1;

    Novelist novelist;
    novelist.setStorage(&storage);

    testNovelist1(&storage);
    testNovelist2(&novelist);

    Project *project = novelist.project();

    project->elementFromStorage(11)->field("Subtitle")->appendValue("String", "A space novella");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("storage", &storage);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("appnovelist", "Main");

    return app.exec();
}
