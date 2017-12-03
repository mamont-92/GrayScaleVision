#ifndef INTEGERPARAMETER_H
#define INTEGERPARAMETER_H

#include "Core/AbstractParameter.h"

class IntegerParameter : public AbstractParameter
{
public:
    IntegerParameter(int _value = 0, int _minValue = 0, int _maxValue = 100);

    QVariant value() const;
    QVariant info() const;

    void setValue(const QVariant & _value);
    void setValue(const int & _value);
    void setMinValue(const int & _value);
    void setMaxValue(const int & _value);
    void setMinMaxValues(const int & _value1, const int & _value2);
private:
    int m_value, m_minValue, m_maxValue;
};

#endif // INTEGERPARAMETER_H
