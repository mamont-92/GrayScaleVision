#include "RealParameter.h"
#include <qdebug.h>

RealParameter::RealParameter(float _value, float _minValue, float _maxValue):
                                    AbstractParameter(), m_value(_value),
                                    m_minValue(_minValue), m_maxValue(_maxValue) {}

QVariant RealParameter::value() const
{
    return QVariant::fromValue(m_value);
}

float RealParameter::valueReal() const
{
    return m_value;
}

QVariant RealParameter::info() const
{
    QVariantMap parameter = {{"value", QVariant::fromValue(m_value)},
                             {"min", QVariant::fromValue(m_minValue)},
                             {"max", QVariant::fromValue(m_maxValue)}};
    return QVariant::fromValue(parameter);
}

void RealParameter::setValue(const QVariant & _value)
{
    bool isCorrect = true;
    float newValue = _value.toFloat(&isCorrect);
    if(isCorrect)
        setValue(newValue);
}


void RealParameter::setValue(const float & _value)
{
    m_value = qBound(m_minValue, _value, m_maxValue);
}

void RealParameter::setMinValue(const float & _value)
{
    m_minValue = qMin(_value, m_maxValue);
    setValue(m_value);
}

void RealParameter::setMaxValue(const float & _value)
{
    m_minValue = qMax(_value, m_minValue);
    setValue(m_value);
}

void RealParameter::setMinMaxValues(const float & _value1, const float & _value2)
{
    if(_value1 < _value2)
        m_minValue = _value1, m_maxValue = _value2;
    else
        m_minValue = _value2, m_maxValue = _value1;
    setValue(m_value);
}
