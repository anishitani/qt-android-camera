#include "FilterTest.h"

QVideoFilterRunnable* FilterTest::createFilterRunnable()
{
    return new FilterTestRunnable(this);
}

QVideoFrame FilterTestRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surface, RunFlags flags){
    Q_UNUSED(surface);
    Q_UNUSED(flags);

    cv::Mat m(input->height(),input->width(),CV_8UC3);
    cv::Mat out(input->height(),input->width(),CV_8UC3);

    input->map(QAbstractVideoBuffer::ReadOnly);

    if(input->isMapped() && input->isReadable()){
        m = cv::Mat(input->height(),input->width(),CV_8UC3,input->bits());
        out = cv::Mat(input->height(),input->width(),CV_8UC3);
        cv::cvtColor(m,out,CV_YUV2BGR);
    }

    QImage image(m.data,m.cols,m.rows,QImage::Format_RGB444);
    QVideoFrame frame(image);

    return frame;
}
