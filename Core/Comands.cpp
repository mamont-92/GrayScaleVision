#include "Comands.h"

using namespace FilterProcessorComands;

ICommand::ICommand()
{

}

AddFilter::AddFilter(const int & _id, const QString & _name): ICommand(),
    m_id(_id), m_name(_name)
{

}

void AddFilter::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

RemoveFilter::RemoveFilter(const int & _id): ICommand(),
    m_id(_id)
{

}

void RemoveFilter::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}

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

SetRasterMode::SetRasterMode(const QString & _mode): ICommand(),
    m_mode(_mode)
{

}

void SetRasterMode::accept(ICommandAcceptor * _visitor)
{
    if(_visitor)
        _visitor->accept(*this);
}
