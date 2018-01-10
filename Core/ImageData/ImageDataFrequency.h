#ifndef ImageDataFrequency_H
#define ImageDataFrequency_H

#include <QRect>
#include <QSize>
#include <QSharedPointer>
#include <QWeakPointer>
#include <cmath>
#include <complex>

//TO DO: add unsafe methods: at, setPixel,

class ImageDataFrequency;

typedef QSharedPointer<ImageDataFrequency> ImageDataFrequencyPtr;
typedef QWeakPointer<ImageDataFrequency> ImageDataFrequencyWeakPtr;
typedef std::complex<float>  complexFloat;

class  ImageDataFrequency
{
public:


    ImageDataFrequency(quint16 _width = 0, quint16 _height = 0);
    ~ImageDataFrequency();

    QSize size() const;
    quint16 width() const;
    quint16 height() const;
    complexFloat* data();
    const complexFloat* data() const;
    QRect rect() const;
    bool isEmpty() const;
    quint64 pixelCount() const;

    void resize(QSize _size);
    void setWithCopyData(const complexFloat * _data, QSize _size);
    void setEmpty();

    complexFloat at(ushort column, ushort row) const;
    complexFloat at(QPoint _point) const;
    void setPixel(ushort column, ushort row, complexFloat value);
    void setPixel(QPoint _point, complexFloat value);

    void fill(complexFloat _value);
    void fillInRect(complexFloat _value, const QRect _rect);

//---------end--operators-------------------------------------------------------------------------
private:
    complexFloat * m_data;
    qint64 m_allocatedPixels;
    quint16  m_height;
    quint16 m_width;
};

#endif // ImageDataFrequency_H

