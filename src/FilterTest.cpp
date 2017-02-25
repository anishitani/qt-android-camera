#include "FilterTest.h"

QVideoFilterRunnable* FilterTest::createFilterRunnable()
{
    return new FilterTestRunnable(this);
}

QVideoFrame FilterTestRunnable::run(QVideoFrame *input,
                                    const QVideoSurfaceFormat &surfaceFormat,
                                    QVideoFilterRunnable::RunFlags flags)
{
    if (!input->isValid())
        return *input;

    QAbstractVideoBuffer::MapMode mode = input->mapMode();

    input->map(QAbstractVideoBuffer::ReadWrite);
        if(input->isReadable()){
            qWarning() << "Is readable!";
            if(input->isWritable()){
                qWarning() << "Is writable!";
                this->deleteColorComponentFromYUV(input);
                cv::Mat mat(input->height(),input->width(), CV_8UC1, input->bits()); // create grayscale mat with input's Ys only and avoid additional color conversion and copying

                cv::GaussianBlur(mat, mat, cv::Size(7,7), 1.5, 1.5);
                cv::Canny(mat, mat, 0, 30, 3);
            }
        }
        input->unmap();


    return *input;
}

void FilterTestRunnable::deleteColorComponentFromYUV(QVideoFrame *input)
{
    // Assign 0 to Us and Vs
    int firstU = input->width()*input->height(); // if i correctly understand YUV420
    int lastV = input->width()*input->height() + input->width()*input->height()/4*2;
    uchar* inputBits = input->bits();

    for (int i=firstU; i<lastV; i++)
        inputBits[i] = 0;
}
