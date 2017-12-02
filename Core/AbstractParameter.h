#ifndef ABSTRACTPARAMETER_H
#define ABSTRACTPARAMETER_H

#include <QVariant>
#include <QString>

class AbstractParameter
{
public:
    AbstractParameter();
    virtual ~AbstractParameter();

    virtual QVariant value() const = 0;
    virtual void setValue(const QVariant & _value) = 0;
};

#endif // ABSTRACTPARAMETER_H
