#ifndef COMMANDCALLBACKACCEPTOR_H
#define COMMANDCALLBACKACCEPTOR_H

#include "Commands.h"
#include <functional>

class FilterProcessor;

namespace FilterProcessorComands {

typedef std::function<void(const AddFilter & command)> AddFilterCallBack;
typedef std::function<void(const RemoveFilter & command)> RemoveFilterCallBack;
typedef std::function<void(const ConnectFilters & command)> ConnectFiltersCallBack;
typedef std::function<void(const SetParameterForFilter & command)> SetParameterForFilterCallBack;
typedef std::function<void(const SetRasterMode & command)> SetRasterModeCallBack;

class CommandCallBackAcceptor: public ICommandAcceptor
{
public:
    CommandCallBackAcceptor(AddFilterCallBack _addFilterCallBack,
                            RemoveFilterCallBack _removeFilterCallBack,
                            ConnectFiltersCallBack _connectFiltersCallBack,
                            SetParameterForFilterCallBack _setParameterForFilterCallBack,
                            SetRasterModeCallBack _setRasterModeCallBack);
    void accept(const AddFilter & command);
    void accept(const RemoveFilter & command);
    void accept(const ConnectFilters & command);
    void accept(const SetParameterForFilter & command);
    void accept(const SetRasterMode & command);
private:
    AddFilterCallBack m_addFilterCallBack;
    RemoveFilterCallBack m_removeFilterCallBack;
    ConnectFiltersCallBack m_connectFiltersCallBack;
    SetParameterForFilterCallBack m_setParameterForFilterCallBack;
    SetRasterModeCallBack m_setRasterModeCallBack;
};

}
#endif // COMMANDCALLBACKACCEPTOR_H
