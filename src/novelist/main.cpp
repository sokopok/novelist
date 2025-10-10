#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "libai/images/client.h"
#include "libai/images/request.h"
#include "libai/images/response.h"
#include "libai/responses/client.h"
#include "libai/responses/response.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // ai::responses::Request request;
    // request.setInput({"Hello!"}).setTemperature(1.5);

    // // qDebug() << request.toJson(true);

    // auto *client = ai::responses::Client::create();
    // QObject::connect(client, &ai::responses::Client::errorOccurred, [](const ai::Error &e) {
    //     qDebug() << e.toJson();
    // });

    // if (auto *response = client->post(request)) {
    //     QObject::connect(response, &ai::responses::Response::errorOccurred, [](const ai::Error &e) {
    //         qDebug() << e.toJson();
    //     });

    //     qDebug() << response->toJson();
    // }

    ai::images::Request imageRequest;
    imageRequest.resetModel();
    imageRequest.setSize(ai::images::Request::Size_256x256);
    imageRequest.setPrompt(
        "A monkey wearing a tracksuit showing off his brand new unicycle on the moon.");
    qDebug() << imageRequest.toJson(true);

    auto *imageClient = ai::images::Client::create();
    QObject::connect(imageClient, &ai::responses::Client::errorOccurred, [](const ai::Error &e) {
        qDebug() << e.toJson();
    });

    if (auto *response = imageClient->post(imageRequest)) {
        QObject::connect(response, &ai::images::Response::errorOccurred, [](const ai::Error &e) {
            qDebug() << e.toJson();
        });

        qDebug() << response->toJson();
    }

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
