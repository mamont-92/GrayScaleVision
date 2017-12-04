#include "Matrix3x3Parameter.h"
#include <QMatrix4x4>
#include <qdebug.h>

Matrix3x3Parameter::Matrix3x3Parameter(QMatrix3x3 _value):
                            AbstractParameter(), m_value(_value) {}

QVariant Matrix3x3Parameter::value() const
{
    return QVariant::fromValue(QMatrix4x4(m_value));
}

QVariant Matrix3x3Parameter::info() const
{
    QVariantMap parameter = {{"value", value()}};
    return QVariant::fromValue(parameter);
}

void Matrix3x3Parameter::setValue(const QVariant & _value)
{
    setValue(_value.toString());
    QMatrix4x4 mat4x4 = _value.value<QMatrix4x4>();
    QMatrix3x3 mat3x3 = mat4x4.toGenericMatrix<3,3>();
    setValue(mat3x3);
}

void Matrix3x3Parameter::setValue(const QMatrix3x3 & _value)

{
    m_value = _value;
}


QMatrix3x3 Matrix3x3Parameter::matValue() const
{
    return m_value;
}
