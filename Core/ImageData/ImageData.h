#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <QRect>
#include <QSize>
#include "opencv2/opencv.hpp"
#include <complex>


template <typename>
struct CVType{
    enum {type = 0};
};

template <>
struct CVType<float>{
    enum {type = CV_32FC1};
};

template <>
struct CVType<double>{
    enum {type = CV_64FC1};
};

template <>
struct CVType<unsigned short>{
    enum {type = CV_16UC1};
};

template<class T>
const T& min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

template <typename DataType>
class ImageData;

using ImageDataSpatial = ImageData<float>;
using ImageDataFrequency = ImageData<std::complex<float> >;
using complexFloat = std::complex<float>;

template<typename DataType, typename Func>
void parallel_process(ImageData<DataType> && imgData, Func func)
{
    qint64 maxInd = imgData.pixelCount();
    DataType * data = imgData.data();
#pragma omp parallel for
    for(qint64 i = 0; i <maxInd; ++i)
        func(*(data+i));
}

template<typename DataType>
void min_max(const ImageData<DataType> & imgData, DataType & min, DataType & max)
{
    const DataType * data = imgData.data();
    if(CVType<DataType>::type){
        cv::Mat src(imgData.height(), imgData.width(), CVType<DataType>::type, (void*)data);
        double dmin, dmax;
        cv::minMaxIdx(src, &dmin, &dmax);
        min = dmin;
        max = dmax;
    }
    else{
        qint64 maxInd = imgData.pixelCount();
        DataType globalMin = *data;
        DataType globalMax = globalMin;

#pragma omp parallel
        {
            DataType localMin = globalMin;
            DataType localMax = globalMax;

#pragma omp for
            for(qint64 i = 0; i <maxInd; ++i){
                DataType val = data[i];
                if(val < localMin)
                    localMin = val;
                else if (val > localMax)
                    localMax = val;
            }

#pragma omp critical
            {
                if(localMin < globalMin)
                    globalMin = localMin;
                if(localMax > globalMax)
                    globalMax = localMax;
            }
        }
        min = globalMin;
        max = globalMax;
    }

}


template <typename DataType>
class ImageData
{
public:
    ImageData(quint16 _width = 0, quint16 _height = 0);
    ImageData(const ImageData<DataType> & obj);
    ImageData(ImageData<DataType> &&other);

    ImageData<DataType>& operator=(ImageData<DataType>&& other);

    ~ImageData();

    QSize size() const;
    quint16 width() const;
    quint16 height() const;
    DataType * data();
    const DataType * data() const; //watafaq is thiiis?
    QRect rect() const;
    bool isEmpty() const;
    quint32 pixelCount() const;

    void resize(QSize _size);
    void setDataWithCopy(const DataType * _data, QSize _size);
    void setEmpty();

    void fill(DataType _value);
    void fillInRect(DataType _value, const QRect & _rect);

    DataType at(ushort column, ushort row) const;
    DataType at(QPoint _point) const;
    void setPixel(ushort column, ushort row, DataType value);
    void setPixel(QPoint _point, DataType value);
private:
    void tryAllocData(QSize _size);
    void freeData();
    void clearData();

    DataType * m_data;
    quint32 m_allocatedPixels;
    quint16  m_height;
    quint16 m_width;
};

template <typename DataType>
ImageData<DataType>::ImageData(quint16 _width, quint16 _height)
{
    tryAllocData(QSize(_width, _height));
}

template <typename DataType>
ImageData<DataType>::ImageData(const ImageData<DataType> & obj)
{
    setWithCopyData(obj.data(), obj.size());
}

template <typename DataType>
ImageData<DataType>::ImageData(ImageData<DataType> && other):
    m_width(other.m_width),
    m_height(other.m_height),
    m_data(other.m_data),
    m_allocatedPixels(other.m_allocatedPixels)
{
    other.clearData();
}

template <typename DataType>
ImageData<DataType>& ImageData<DataType>::operator=(ImageData<DataType>&& other)
{
    if(this != &other){
        m_width = other.m_width;
        m_height = other.m_height;
        if(m_data)
            delete [] m_data;
        m_data = other.m_data;
        m_allocatedPixels = other.m_allocatedPixels;

        other.clearData();
    }
    return *this;
}

template <typename DataType>
ImageData<DataType>::~ImageData()
{
    freeData();
}

template <typename DataType>
void ImageData<DataType>::tryAllocData(QSize _size)
{
    m_width = _size.width();
    m_height = _size.height();
    m_allocatedPixels = m_width * m_height;
    if(m_allocatedPixels)
        m_data = new DataType[m_allocatedPixels];
    else
        m_data = nullptr;
    if(!m_data)
        m_allocatedPixels = 0;
}

template <typename DataType>
void ImageData<DataType>::freeData()
{
    m_width = 0;
    m_height = 0;
    m_allocatedPixels = 0;
    if(m_data){
        delete [] m_data;
        m_data = nullptr;
    }
}

template <typename DataType>
void ImageData<DataType>::clearData()
{
    m_width = 0;
    m_height = 0;
    m_allocatedPixels = 0;
    m_data = nullptr;
}

template <typename DataType>
void ImageData<DataType>::resize(QSize _size)
{
    const float lessRatio = 1.25;
    quint32 newAllocPixels = _size.width() * _size.height();
    if( (newAllocPixels > m_allocatedPixels) || (newAllocPixels*lessRatio < m_allocatedPixels)){
        freeData();
        tryAllocData(_size);
    }
}

template <typename DataType>
void ImageData<DataType>::setEmpty()
{
    resize(QSize(0,0));
}

template <typename DataType>
QSize ImageData<DataType>::size() const
{
    return QSize(m_width, m_height);
}


template <typename DataType>
quint16 ImageData<DataType>::width() const
{
    return m_width;
}

template <typename DataType>
quint16 ImageData<DataType>::height() const
{
    return m_height;
}

template <typename DataType>
DataType* ImageData<DataType>::data()
{
    return m_data;
}

template <typename DataType>
const DataType* ImageData<DataType>::data() const
{
    return m_data;
}

template <typename DataType>
QRect ImageData<DataType>::rect() const
{
    return (m_allocatedPixels > 0) ? QRect(0,0, m_width-1, m_height-1) : QRect(0,0,0,0);
}

template <typename DataType>
quint32 ImageData<DataType>::pixelCount() const
{
    return m_allocatedPixels;
}

template <typename DataType>
void ImageData<DataType>::fill(DataType _value){
#pragma omp parallel for
    for(qint64 i = 0; i < m_allocatedPixels; ++i){
        m_data[i] = _value;
    }
}

template <typename DataType>
void ImageData<DataType>::fillInRect(DataType _value, const QRect & _rect){
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

template <typename DataType>
bool ImageData<DataType>::isEmpty() const
{
    return m_allocatedPixels;
}

template <typename DataType>
void ImageData<DataType>::setPixel(ushort column, ushort row, DataType value)
{
    setPixel(QPoint(column, row), value);
}

template <typename DataType>
void ImageData<DataType>::setPixel(QPoint _point, DataType value)
{
    if(rect().contains(_point)){
        m_data[_point.y()*m_width+_point.x()] = value;
    }
}

template <typename DataType>
DataType ImageData<DataType>::at(ushort column, ushort row) const
{
    return at(QPoint(column, row));
}

template <typename DataType>
DataType ImageData<DataType>::at(QPoint _point) const
{
    return rect().contains(_point) ? m_data[_point.y()*m_width+_point.x()] : 0;
    }

    template <typename DataType>
    void ImageData<DataType>::setDataWithCopy(const DataType * _data, QSize _size)
    {
    resize(_size);
    memcpy(m_data, _data, sizeof(DataType)* min((qint64)_size.width() * _size.height(), (qint64)m_allocatedPixels));
}

#endif // IMAGEDATA_H
