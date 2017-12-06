#include "IntegerParameter.h"
#include <qdebug.h>

IntegerParameter::IntegerParameter(int _value, int _minValue, int _maxValue, ValueType _valueType):
                                    AbstractParameter(), m_value(_value),
                                    m_minValue(_minValue), m_maxValue(_maxValue),
                                    m_valueType(_valueType) {}

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

inline int makeLessEven(int _val){
    return (_val / 2) * 2;
}

inline int makeLessOdd(int _val){
    return (_val-1) / 2 + 1;
}

void IntegerParameter::setValue(const int & _value)
{
    int new_value = _value;
    switch(m_valueType){
        case OnlyEven:
            new_value = makeLessEven(_value);
        break;
        case OnlyOdd:
            new_value = makeLessOdd(_value);
        break;

    }
    m_value = qBound(m_minValue, new_value, m_maxValue);
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
