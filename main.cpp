#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "opencvimageprovider.h"
#include "videostreamer.h"
#include "whiteboardmanager.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    VideoStreamer videoStreamer;
    WhiteboardManager whiteboardManager;

    OpencvImageProvider *liveImageProvider(new OpencvImageProvider);
    OpencvImageProvider *whiteboardImageProvider(new OpencvImageProvider);

    engine.rootContext()->setContextProperty("VideoStreamer", &videoStreamer);
    engine.rootContext()->setContextProperty("WhiteboardManager", &whiteboardManager);
    engine.rootContext()->setContextProperty("liveImageProvider", liveImageProvider);
    engine.rootContext()->setContextProperty("whiteboardImageProvider", whiteboardImageProvider);

    engine.addImageProvider("live", liveImageProvider);
    engine.addImageProvider("whiteboard", whiteboardImageProvider);

    const QUrl url(QStringLiteral("qrc:/whiteboard/main.qml"));
    engine.load(url);

    QObject::connect(&videoStreamer, &VideoStreamer::newImage, liveImageProvider, &OpencvImageProvider::updateImage);
    QObject::connect(&videoStreamer, &VideoStreamer::newImage, &whiteboardManager, &WhiteboardManager::processFrame);
    QObject::connect(&whiteboardManager, &WhiteboardManager::newWhiteboardImage, whiteboardImageProvider, &OpencvImageProvider::updateImage);



    return app.exec();
}
