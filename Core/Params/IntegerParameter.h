#ifndef INTEGERPARAMETER_H
#define INTEGERPARAMETER_H

#include "Core/AbstractParameter.h"

class IntegerParameter : public AbstractParameter
{
public:
    enum ValueType{
        ALLValues = 0,
        OnlyOdd = 1,
        OnlyEven = 2
    };
    IntegerParameter(int _value = 0, int _minValue = 0, int _maxValue = 100, ValueType _valueType = ALLValues);

    QVariant value() const;
    int valueInt() const;
    QVariant info() const;

    void setValue(const QVariant & _value);
    void setValue(const int & _value);
    void setMinValue(const int & _value);
    void setMaxValue(const int & _value);
    void setMinMaxValues(const int & _value1, const int & _value2);
private:
    int m_value, m_minValue, m_maxValue;
    ValueType m_valueType;
};

#endif // INTEGERPARAMETER_H
