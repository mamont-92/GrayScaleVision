#include "ImageDataFrequency.h"

#include <cmath>
#include "opencv2/opencv.hpp"

static const float epsilone = 0.000001f;

ImageDataFrequency::ImageDataFrequency(quint16 _width, quint16 _height):
    m_width(_width),
    m_height(_height)
{
    m_allocatedPixels = m_width * m_height;
    if(m_allocatedPixels)
        m_data = new complexFloat[m_allocatedPixels];
    else
        m_data = NULL;
    if(!m_data)
        m_allocatedPixels = 0;
}

ImageDataFrequency::~ImageDataFrequency()
{
    m_width = 0;
    m_height = 0;
    if(m_data)
        delete [] m_data;
    m_data = NULL;
}

QSize ImageDataFrequency::size() const
{
    return QSize(m_width, m_height);
}

void ImageDataFrequency::resize(QSize _size)
{
    m_width = _size.width();
    m_height = _size.height();
    qint64 newAllocPixels = _size.width() * _size.height();
    if((newAllocPixels > m_allocatedPixels) || ((1.5 * newAllocPixels) < m_allocatedPixels)){
        if(m_data) delete [] m_data;
        m_allocatedPixels = newAllocPixels;
        if(m_allocatedPixels)
            m_data = new complexFloat[m_allocatedPixels];
        else
            m_data = NULL;
        if(!m_data)
            m_allocatedPixels = 0;
    }
    else
        m_allocatedPixels = newAllocPixels;
}

void ImageDataFrequency::setWithCopyData(const complexFloat * _data, QSize _size)
{
    resize(_size);
    memcpy(m_data, _data, sizeof(complexFloat)* qMin((qint64)_size.width() * _size.height(), (qint64)m_allocatedPixels));
}

void ImageDataFrequency::setEmpty()
{
    resize(QSize(0,0));
}

quint16 ImageDataFrequency::width() const
{
    return m_width;
}
quint16 ImageDataFrequency::height() const
{
    return m_height;
}

complexFloat* ImageDataFrequency::data()
{
    return m_data;
}

const complexFloat* ImageDataFrequency::data() const
{
    return m_data;
}

QRect ImageDataFrequency::rect() const
{
    return (m_allocatedPixels > 0) ? QRect(0,0, m_width-1, m_height-1) : QRect(0,0,0,0);
}

quint64 ImageDataFrequency::pixelCount() const
{
    return m_allocatedPixels;
}

void ImageDataFrequency::fill(complexFloat _value){
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = _value;
    }
}

void ImageDataFrequency::fillInRect(complexFloat _value, const QRect _rect){
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

void ImageDataFrequency::setPixel(ushort column, ushort row, complexFloat value)
{
    setPixel(QPoint(column, row), value);
}

void ImageDataFrequency::setPixel(QPoint _point, complexFloat value)
{
    if(rect().contains(_point)){
        m_data[_point.y()*m_width+_point.x()] = value;
    }
}

complexFloat ImageDataFrequency::at(ushort column, ushort row) const
{
    return at(QPoint(column, row));
}

complexFloat ImageDataFrequency::at(QPoint _point) const
{
    return rect().contains(_point) ? m_data[_point.y()*m_width+_point.x()] : 0;
}


bool ImageDataFrequency::isEmpty() const
{
    return !(m_allocatedPixels > 0);
}

