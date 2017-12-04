#ifndef Matrix3x3Parameter_H
#define Matrix3x3Parameter_H

#include "Core/AbstractParameter.h"

#include <QMatrix3x3>

class Matrix3x3Parameter : public AbstractParameter
{
public:
    Matrix3x3Parameter(QMatrix3x3 _value = QMatrix3x3());

    QVariant value() const;
    QVariant info() const;
    QMatrix3x3 matValue() const;

    void setValue(const QVariant & _value);
    void setValue(const QMatrix3x3 & _value);
private:
    QMatrix3x3 m_value;
};

#endif // Matrix3x3Parameter_H
