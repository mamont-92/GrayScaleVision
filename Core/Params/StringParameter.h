#ifndef StringParameter_H
#define StringParameter_H

#include "Core/AbstractParameter.h"

class StringParameter : public AbstractParameter
{
public:
    StringParameter(QString _value= "");

    QVariant value() const;
    QVariant info() const;

    void setValue(const QVariant & _value);
    void setValue(const QString & _value);
private:
    QString m_value;
};

#endif // StringParameter_H
