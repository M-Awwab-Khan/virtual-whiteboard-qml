#ifndef WHITEBOARDMANAGER_H
#define WHITEBOARDMANAGER_H
#include <QObject>
#include <QImage>
#include <QTimer>
#include <opencv2/opencv.hpp>

class WhiteboardManager : public QObject
{
    Q_OBJECT

public:
    explicit WhiteboardManager(QObject *parent = nullptr);
    ~WhiteboardManager();

    QImage getWhiteboardImage() const;

signals:
    void newWhiteboardImage(const QImage &image);

public slots:
    void processFrame(const QImage &frame);
    void clearWhiteboard();
    void saveSnapshot(const QString &filePath);

private:
    cv::Mat whiteboard;
    QImage qtWhiteboardImage;
    cv::Scalar lowerColor;
    cv::Scalar upperColor;
    cv::Point prevPoint;
    bool isDrawing;
};

#endif // WHITEBOARDMANAGER_H
