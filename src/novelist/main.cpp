#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "libai/responses/client.h"
#include "libai/responses/response.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ai::responses::Request request{};
    request.setBackground(true);
    request.setInput({ai::InputItemList{{{{ai::MessageContent{"Hello"
                                                              "."}}},
                                         {ai::ItemReference{"sjqsgcjhsg"}},
                                         {ai::Message{}}}}});
    request.setStreaming(true);
    request.setStreamOptions(true);
    qDebug() << request.toJson();

    ai::responses::Client client;
    if (auto *response = client.post(request)) {
        qDebug() << response->toJson();
    } else {
        qDebug() << "failed to post request";
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
