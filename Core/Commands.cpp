#include "Commands.h"

using namespace FilterProcessorComands;

ICommand::ICommand()
{

}
//------------------------------------------------------------------------
AddFilter::AddFilter(const int & _filterNumber, const QString & _name): ICommand(),
    m_filterNumber(_filterNumber), m_name(_name)
{

}

void AddFilter::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

int AddFilter::filterNumber() const
{
    return m_filterNumber;
}

QString AddFilter::name() const
{
    return m_name;
}
//------------------------------------------------------------------------
RemoveFilter::RemoveFilter(const int & _filterNumber): ICommand(),
    m_filterNumber(_filterNumber)
{

}
void RemoveFilter::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

int RemoveFilter::filterNumber() const
{
    return m_filterNumber;
}
//------------------------------------------------------------------------
ConnectFilters::ConnectFilters(const int & _filterOut, const int & _connectorOut,
                               const int & _filterIn, const int & _connectorIn): ICommand(),
    m_filterOut(_filterOut), m_connectorOut(_connectorOut), m_filterIn(_filterIn), m_connectorIn(_connectorIn)
{

}

void ConnectFilters::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

int ConnectFilters::filterOut() const
{
    return m_filterOut;
}

int ConnectFilters::connectorOut() const
{
    return m_connectorOut;
}

int ConnectFilters::filterIn() const
{
    return m_filterIn;
}

int ConnectFilters::connectorIn() const
{
    return m_connectorIn;
}
//------------------------------------------------------------------------
SetParameterForFilter::SetParameterForFilter(const int & _filterNumber, const QString & _paramName,
                                 const QVariant & _value): ICommand(),
    m_filterNumber(_filterNumber), m_paramName(_paramName), m_value(_value)
{

}

void SetParameterForFilter::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

int SetParameterForFilter::filterNumber() const
{
    return m_filterNumber;
}

QString SetParameterForFilter::paramName() const
{
    return m_paramName;
}

QVariant SetParameterForFilter::value() const
{
    return m_value;
}
//------------------------------------------------------------------------
SetRasterMode::SetRasterMode(const QString & _mode): ICommand(),
    m_mode(_mode)
{

}

void SetRasterMode::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

QString SetRasterMode::mode() const
{
    return m_mode;
}
