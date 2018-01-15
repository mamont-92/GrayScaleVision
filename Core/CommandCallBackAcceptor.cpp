#include "CommandCallBackAcceptor.h"
#include "FilterProcessor.h"

using namespace FilterProcessorComands;

CommandCallBackAcceptor::CommandCallBackAcceptor(AddFilterCallBack _addFilterCallBack,
                                                 RemoveFilterCallBack _removeFilterCallBack,
                                                 ConnectFiltersCallBack _connectFiltersCallBack,
                                                 SetParameterForFilterCallBack _setParameterForFilterCallBack,
                                                 SetRasterModeCallBack _setRasterModeCallBack):
                                                    m_addFilterCallBack(_addFilterCallBack),
                                                    m_removeFilterCallBack(_removeFilterCallBack),
                                                    m_connectFiltersCallBack(_connectFiltersCallBack),
                                                    m_setParameterForFilterCallBack(_setParameterForFilterCallBack),
                                                    m_setRasterModeCallBack(_setRasterModeCallBack)
{

}

/*CommandCallBackAcceptor::CommandCallBackAcceptor(FilterProcessor _filterProcessorPtr):m_filterProcessorPtr(_filterProcessorPtr)
{

}*/

void CommandCallBackAcceptor::accept(const AddFilter & command)
{
    m_addFilterCallBack(command);
}
void CommandCallBackAcceptor::accept(const RemoveFilter & command)
{
    m_removeFilterCallBack(command);
}
void CommandCallBackAcceptor::accept(const ConnectFilters & command)
{
    m_connectFiltersCallBack(command);
}
void CommandCallBackAcceptor::accept(const SetParameterForFilter & command)
{
    m_setParameterForFilterCallBack(command);
}
void CommandCallBackAcceptor::accept(const SetRasterMode & command)
{
    m_setRasterModeCallBack(command);
}
