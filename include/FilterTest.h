#ifndef FILTERTEST_H
#define FILTERTEST_H

#include <iostream>

#include <QObject>
#include <QAbstractVideoFilter>
#include <QDebug>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/**
 * @brief The FilterTest class
 */
class FilterTest : public QAbstractVideoFilter
{
    Q_OBJECT

private:
    friend class FilterTestRunnable;

public:
    QVideoFilterRunnable *createFilterRunnable();
};

/**
 * @brief The FilterTestRunnable class
 */
class FilterTestRunnable : public QVideoFilterRunnable
{
private:
    FilterTest *m_filter;

    void deleteColorComponentFromYUV(QVideoFrame *input);
public:
    FilterTestRunnable(FilterTest *filter) : m_filter(filter) { }
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
};

#endif // FILTERTEST_H
