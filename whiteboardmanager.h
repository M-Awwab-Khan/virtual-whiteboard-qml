#ifndef WHITEBOARDMANAGER_H
#define WHITEBOARDMANAGER_H
#include <QObject>
#include <QImage>
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
    void newWeightedImage(const QImage &image);

public slots:
    void processFrame(const QImage &frame);
    void clearWhiteboard();
    void saveSnapshot(const QString &filePath);
    void enableDrawing();
    void disableDrawing();
    void loadImage(const QString &filePath);

private:
    cv::Mat whiteboard;
    QImage qtWeightedImage;
    const cv::Scalar lowerColor;
    const cv::Scalar upperColor;
    cv::Point prevPoint;
    cv::Scalar currentColor;
    const cv::Rect redArea;
    const cv::Rect greenArea;
    const cv::Rect blueArea;
    const cv::Rect eraserArea;
    const cv::Rect clearArea;
    bool isDrawing;
    bool eraserSelected;
    bool drawingEnabled;
};

#endif // WHITEBOARDMANAGER_H
