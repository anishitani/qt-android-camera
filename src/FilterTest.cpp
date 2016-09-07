#include "FilterTest.h"

QVideoFilterRunnable* FilterTest::createFilterRunnable()
{
    return new FilterTestRunnable(this);
}

QVideoFrame FilterTestRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surface, RunFlags flags){
    Q_UNUSED(surface);
    Q_UNUSED(flags);

    cv::Mat m,out;

    input->map(QAbstractVideoBuffer::ReadOnly);

    if(input->isMapped() && input->isReadable()){

        int y,u,v;
        int r,g,b;

        int w = input->width();
        int h = input->height();
        int total = input->width()*input->height();
        uchar* yuv = input->bits();

        m = cv::Mat(input->height(),input->width(),CV_8UC3);
        out = cv::Mat(input->height(),input->width(),CV_8UC3);

        for(int row=0 ; row < input->height() ; row++){
            for(int col=0 ; col< input->width() ; col++){
                y = yuv[row * input->width() + col];
                u = yuv[(row / 2) * (input->width() / 2) + (col / 2) + total];
                v = yuv[(row / 2) * (input->width() / 2) + (col / 2) + 5*total/4];

                b = 1.164 * (y - 16) + 2.018 * (u - 128);
                g = 1.164 * (y - 16) - 0.813 * (v - 128) - 0.391 * (u - 128);
                r = 1.164 * (y - 16) + 1.596 * (v - 128);

                m.data[ 3*(row*w + col) + 0 ] = r;
                m.data[ 3*(row*w + col) + 1 ] = g;
                m.data[ 3*(row*w + col) + 2 ] = b;
            }
        }
    }

#ifndef Q_OS_ANDROID
    cv::cvtColor(m,out,CV_RGB2BGR);

    cv::namedWindow("Image",cv::WINDOW_NORMAL);
    cv::imshow("Image",out);
#endif

    QImage image(m.data,m.cols,m.rows,QImage::Format_RGB444);
    QVideoFrame frame(image);

    return frame;
}
