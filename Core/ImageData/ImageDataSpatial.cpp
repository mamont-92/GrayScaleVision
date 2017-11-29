#include "ImageDataSpatial.h"

#include <cmath>
#include "opencv2/opencv.hpp"

static const float epsilone = 0.000001f;

ImageDataSpatial::ImageDataSpatial(quint16 _width, quint16 _height):
    m_width(_width),
    m_height(_height)
{
    m_allocatedPixels = m_width * m_height;
    m_data = new float[m_allocatedPixels];
    if(!m_data)
        m_allocatedPixels = 0;
}

ImageDataSpatial::~ImageDataSpatial()
{
    m_width = 0;
    m_height = 0;
    if(m_data)
        delete [] m_data;
    m_data = NULL;
}

QSize ImageDataSpatial::size() const
{
    return QSize(m_width, m_height);
}
quint16 ImageDataSpatial::width() const
{
    return m_width;
}
quint16 ImageDataSpatial::height() const
{
    return m_height;
}

float* ImageDataSpatial::data()
{
    return m_data;
}

const float* ImageDataSpatial::data() const
{
    return m_data;
}

QRect ImageDataSpatial::rect() const
{
    return (m_allocatedPixels > 0) ? QRect(0,0, m_width-1, m_height-1) : QRect(0,0,0,0);
}

quint64 ImageDataSpatial::pixelCount() const
{
    return m_allocatedPixels;
}

void ImageDataSpatial::fill(float _value){
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = _value;
    }
}

void ImageDataSpatial::fillInRect(float _value, const QRect _rect){
    QRect  resultRect = rect().intersected(_rect);
    qint32 startCol = resultRect.left();
    qint32 endCol = resultRect.right();
    qint32 startRow = resultRect.top();
    qint32 endRow = resultRect.bottom();

    qint64 pixCount = (endCol-startCol)*(endRow-startRow);
    if(!pixCount)
        return;

#pragma omp parallel
    {
        #pragma omp for
        for(qint32  i = startRow; i <= endRow; ++i){
            qint32 start_ind = i*m_width; //TO DO: need add startCol and increment it in "while" cyle below
            for(qint32 j = startCol; j < endCol; ++j)
                m_data[start_ind+j] = _value;
        }
    }

}

void ImageDataSpatial::setPixel(ushort column, ushort row, float value)
{
    setPixel(QPoint(column, row), value);
}

void ImageDataSpatial::setPixel(QPoint _point, float value)
{
    if(rect().contains(_point)){
        m_data[_point.y()*m_width+_point.x()] = value;
    }
}

float ImageDataSpatial::at(ushort column, ushort row) const
{
    return at(QPoint(column, row));
}

float ImageDataSpatial::at(QPoint _point) const
{
    return rect().contains(_point) ? m_data[_point.y()*m_width+_point.x()] : 0;
}


bool ImageDataSpatial::isEmpty() const
{
    return !(m_allocatedPixels > 0);
}

void ImageDataSpatial::boundMinMax(float minValue, float maxValue){
    #pragma omp parallel for
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = qBound(minValue, m_data[i], maxValue);
    }
}

void ImageDataSpatial::boundMin(float minValue){
    #pragma omp parallel for
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = qMax(minValue, m_data[i]);
    }
}

void ImageDataSpatial::boundMax(float maxValue){
    #pragma omp parallel for
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = qMin(maxValue, m_data[i]);

    }
}

void ImageDataSpatial::power(float _p) {
    #pragma omp parallel for
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = pow(m_data[i], _p);
    }
}

void ImageDataSpatial::calcMinMax(float & minVal, float & maxVal) const
{
    const float* d = data();
    cv::Mat src(height(), width(), CV_32FC1, (void*)d);
    double min, max;
    cv::minMaxIdx(src, &min, &max);
    minVal = min;
    maxVal = max;
}
