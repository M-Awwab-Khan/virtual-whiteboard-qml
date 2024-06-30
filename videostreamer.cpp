#include "videostreamer.h"

VideoStreamer::VideoStreamer()
{
    connect(&tUpdate,&QTimer::timeout,this,&VideoStreamer::streamVideo);
    cap.open(0);
    // cap.set(cv::CAP_PROP_FPS, 50);
    double fps = cap.get(cv::CAP_PROP_FPS);

    tUpdate.start(1000/fps);
}


VideoStreamer::~VideoStreamer()
{
    cap.release();
    tUpdate.stop();
}

void VideoStreamer::streamVideo()
{
    cap>>frame;

    QImage img = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
    emit newImage(img);
}
