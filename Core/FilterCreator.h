#ifndef FILTERCREATOR_H
#define FILTERCREATOR_H

//#include "AbstractFilter.h"
#include <QString>
#include <functional>
#include <QHash>

class AbstractFilter;

#define DECLARE_READABLE_NAME(rname) static QString readableName(){ QString _readableName(rname); return _readableName; }

typedef std::function<AbstractFilter * ()> filterCreationFunc;

class FilterCreator
{
public:
    FilterCreator();

    static AbstractFilter * create(QString type){
        filterCreationFunc defFunc = [] () -> AbstractFilter * {return NULL;};
        return filterFuncs().value(type, defFunc)();
    }

    static void registerFIlter(QString type, filterCreationFunc func){
        filterFuncs().insert(type, func);
    }

public:
    static QHash<QString, filterCreationFunc> & filterFuncs(){
        static QHash<QString, filterCreationFunc> _filterFuncs;
        return _filterFuncs;
    }
};

class FilterRegistrator{
public:
    FilterRegistrator(QString type, filterCreationFunc func){
        FilterCreator::registerFIlter(type, func);
    }
};

#define REGISTER_FILTER(filter) static FilterRegistrator filter_reg_##filter(##filter::readableName(), [] () -> AbstractFilter * { return new  filter(); });


#endif // FILTERCREATOR_H
