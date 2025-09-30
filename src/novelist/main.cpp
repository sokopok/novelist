#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "libai/responses/client.h"
#include "libai/responses/response.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ai::responses::Request request{};
    request.setInput({"Hello!"});

    ai::responses::Client client;
    QObject::connect(&client, &ai::responses::Client::errorOccurred, [](const ai::Error &e) {
        qDebug() << e.toJson();
    });

    if (auto *response = client.post(request)) {
        QObject::connect(response, &ai::responses::Response::errorOccurred, [](const ai::Error &e) {
            qDebug() << e.toJson();
        });

        qDebug() << response->toJson();
    }

    // client.

    // requestDataprivate
    //     .setInput(ai::Input{ai::InputItemList{{ai::InputItem{ai::Message{ai::MessageContent{"Hello"
    //                                                                                         "."}}},
    //                                            {ai::ItemReference{"sjqsgcjhsg"}},
    //                                            {ai::Message{}}}}})
    //     .setModel("...")
    //     .setStreamOptions(ai::StreamOptions{false});

    // request.setRequestData(requestData);

    // qDebug() << request.requestData().toJson();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("be.oncruyt.novelist", "Main");

    return app.exec();
}
