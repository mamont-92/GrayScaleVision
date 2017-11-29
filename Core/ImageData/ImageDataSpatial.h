#ifndef IMAGEDATASPATIAL_H
#define IMAGEDATASPATIAL_H

#include <QRect>
#include <QSize>

//TO DO: add unsafe methods: at, setPixel,

class  ImageDataSpatial
{
public:

    ImageDataSpatial(quint16 _width = 0, quint16 _height = 0);
    ~ImageDataSpatial();

    QSize size() const;
    quint16 width() const;
    quint16 height() const;
    float* data();
    const float* data() const;
    QRect rect() const;
    bool isEmpty() const;
    quint64 pixelCount() const;

    float at(ushort column, ushort row) const;
    float at(QPoint _point) const;
    void setPixel(ushort column, ushort row, float value);
    void setPixel(QPoint _point, float value);

    void fill(float _value);
    void fillInRect(float _value, const QRect _rect);

    void boundMinMax(float minValue, float maxValue);
    void boundMin(float minValue);
    void boundMax(float maxValue);

    void power(float _p); //power

//---------end--operators-------------------------------------------------------------------------
private:
    float * m_data;
    qint64 m_allocatedPixels;
    quint16  m_height;
    quint16 m_width;
};

#endif // ImageDataSpatial_H

