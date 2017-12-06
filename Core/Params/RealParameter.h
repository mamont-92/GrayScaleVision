#ifndef RealParameter_H
#define RealParameter_H

#include "Core/AbstractParameter.h"

class RealParameter : public AbstractParameter
{
public:
    RealParameter(float _value = 0.0f, float _minValue = 0.0f, float _maxValue = 1.0f);

    QVariant value() const;
    float valueReal() const;
    QVariant info() const;

    void setValue(const QVariant & _value);
    void setValue(const float & _value);
    void setMinValue(const float & _value);
    void setMaxValue(const float & _value);
    void setMinMaxValues(const float & _value1, const float & _value2);
private:
    float m_value, m_minValue, m_maxValue;
};

#endif // RealParameter_H
