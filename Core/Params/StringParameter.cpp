#include "StringParameter.h"

StringParameter::StringParameter(QString _value):
                            AbstractParameter(), m_value(_value) {}

QVariant StringParameter::value() const
{
    return QVariant::fromValue(m_value);
}

QVariant StringParameter::info() const
{
    QVariantMap parameter = {{"value", QVariant::fromValue(m_value)}};
    return QVariant::fromValue(parameter);
}

void StringParameter::setValue(const QVariant & _value)
{
    setValue(_value.toString());
}

void StringParameter::setValue(const QString & _value)
{
    m_value = _value;
}
