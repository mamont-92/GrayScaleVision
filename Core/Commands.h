#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>
#include <QVariant>

namespace FilterProcessorComands {

class ICommandAcceptor; //interface for "visitor pattern"

class ICommand // interface for "command pattern"
{
protected:
    ICommand();
public:
    virtual ~ICommand() {}
    virtual void accept(ICommandAcceptor * _visitor) = 0;
};

class AddFilter : public ICommand
{
public:
    AddFilter(const int & _filterNumber, const QString & _name);
    void accept(ICommandAcceptor * _visitor);

    int filterNumber() const;
    QString name() const;
private:
    int m_filterNumber;
    QString m_name;
};

class RemoveFilter : public ICommand
{
public:
    RemoveFilter(const int & _filterNumber);
    void accept(ICommandAcceptor * _visitor);

    int filterNumber() const;
private:
    int m_filterNumber;
};


class ConnectFilters : public ICommand
{
public:
    ConnectFilters(const int & _filterOut, const int & _connectorOut,
                   const int & _filterIn, const int & _connectorIn);
    void accept(ICommandAcceptor * _visitor);

    int filterOut() const;
    int connectorOut() const;
    int filterIn() const;
    int connectorIn() const;
private:
    int m_filterOut, m_connectorOut, m_filterIn, m_connectorIn;
};

class SetParameterForFilter : public ICommand
{
public:
    SetParameterForFilter(const int & _filterNumber, const QString & _paramName, const QVariant & _value);
    void accept(ICommandAcceptor * _visitor);

    int filterNumber() const;
    QString paramName() const;
    QVariant value() const;
private:
    int m_filterNumber;
    QString m_paramName;
    QVariant m_value;
};


class SetRasterMode : public ICommand
{
public:
    SetRasterMode(const QString & _mode);
    void accept(ICommandAcceptor * _visitor);

    QString mode() const;
private:
    QString m_mode;
};

class ICommandAcceptor
{
public:
    virtual ~ICommandAcceptor() {}
    virtual void accept(const AddFilter & command) = 0;
    virtual void accept(const RemoveFilter & command) = 0;
    virtual void accept(const ConnectFilters & command) = 0;
    virtual void accept(const SetParameterForFilter & command) = 0;
    virtual void accept(const SetRasterMode & command) = 0;
};

}

#endif // COMMANDS_H
