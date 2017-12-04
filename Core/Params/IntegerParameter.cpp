#include "IntegerParameter.h"
#include <qdebug.h>

IntegerParameter::IntegerParameter(int _value, int _minValue, int _maxValue):
                                    AbstractParameter(), m_value(_value),
                                    m_minValue(_minValue), m_maxValue(_maxValue) {}

QVariant IntegerParameter::value() const
{
    return QVariant::fromValue(m_value);
}

int IntegerParameter::valueInt() const
{
    return m_value;
}

QVariant IntegerParameter::info() const
{
    QVariantMap parameter = {{"value", QVariant::fromValue(m_value)},
                             {"min", QVariant::fromValue(m_minValue)},
                             {"max", QVariant::fromValue(m_maxValue)}};
    return QVariant::fromValue(parameter);
}

void IntegerParameter::setValue(const QVariant & _value)
{
    bool isCorrect = true;
    int newValue = _value.toInt(&isCorrect);
    if(isCorrect)
        setValue(newValue);
}


void IntegerParameter::setValue(const int & _value)
{
    m_value = qBound(m_minValue, _value, m_maxValue);
}

void IntegerParameter::setMinValue(const int & _value)
{
    m_minValue = qMin(_value, m_maxValue);
    setValue(m_value);
}

void IntegerParameter::setMaxValue(const int & _value)
{
    m_minValue = qMax(_value, m_minValue);
    setValue(m_value);
}

void IntegerParameter::setMinMaxValues(const int & _value1, const int & _value2)
{
    if(_value1 < _value2)
        m_minValue = _value1, m_maxValue = _value2;
    else
        m_minValue = _value2, m_maxValue = _value1;
    setValue(m_value);
}
