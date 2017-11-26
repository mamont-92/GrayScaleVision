#ifndef FILTERCREATOR_H
#define FILTERCREATOR_H

#include "AbstractFilter.h"
#include <QString>
#include <functional>
#include <QHash>

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


//#define REGISTER_FILTER(filter) temp_##filter; static FilterRegistrator filter_reg_##filter(#filter, [] () -> AbstractFilter * {return new  filter() }); class filter

class FilterRegistrator{
public:
    FilterRegistrator(QString type, filterCreationFunc func){
        FilterCreator::registerFIlter(type, func);
    }
};

#endif // FILTERCREATOR_H
