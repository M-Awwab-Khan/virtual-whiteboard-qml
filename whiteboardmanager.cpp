#include "whiteboardmanager.h"
#include <QDebug>

WhiteboardManager::WhiteboardManager(QObject *parent)
    : QObject(parent),
    lowerColor(cv::Scalar(0, 129, 148)),
    upperColor(cv::Scalar(22, 255, 255)),
    isDrawing(false)
{
    whiteboard = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
}

WhiteboardManager::~WhiteboardManager()
{
}

QImage WhiteboardManager::getWhiteboardImage() const
{
    return qtWhiteboardImage;
}

void WhiteboardManager::processFrame(const QImage &frame)
{
    cv::Mat matFrame(frame.height(), frame.width(), CV_8UC3, const_cast<uchar*>(frame.bits()), frame.bytesPerLine());
    cv::cvtColor(matFrame, matFrame, cv::COLOR_RGB2BGR);

    cv::Mat hsvFrame, mask;
    cv::cvtColor(matFrame, hsvFrame, cv::COLOR_BGR2HSV);
    cv::inRange(hsvFrame, lowerColor, upperColor, mask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {
        std::sort(contours.begin(), contours.end(), [](const std::vector<cv::Point>& c1, const std::vector<cv::Point>& c2) {
            return cv::contourArea(c1, false) > cv::contourArea(c2, false);
        });

        cv::Rect boundingRect = cv::boundingRect(contours[0]);
        cv::Point center(boundingRect.x + boundingRect.width / 2, boundingRect.y + boundingRect.height / 2);

        if (isDrawing) {
            cv::line(whiteboard, prevPoint, center, cv::Scalar(0, 0, 255), 1);
        }

        prevPoint = center;
        isDrawing = true;
    } else {
        isDrawing = false;
    }

    // cv::cvtColor(whiteboard, whiteboard, cv::COLOR_BGR2RGB);
    qtWhiteboardImage = QImage(whiteboard.data, whiteboard.cols, whiteboard.rows, QImage::Format_RGB888).rgbSwapped();

    emit newWhiteboardImage(qtWhiteboardImage);
}

void WhiteboardManager::clearWhiteboard()
{
    whiteboard = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);
    emit newWhiteboardImage(QImage(whiteboard.data, whiteboard.cols, whiteboard.rows, QImage::Format_RGB888).rgbSwapped());
}

void WhiteboardManager::saveSnapshot(const QString &filePath)
{
    if (!qtWhiteboardImage.isNull()) {
        qtWhiteboardImage.save(filePath);
    }
}
