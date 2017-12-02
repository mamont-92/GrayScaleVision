#ifndef FILTERCREATOR_H
#define FILTERCREATOR_H

//#include "AbstractFilter.h"
#include <QString>
#include <functional>
#include <QHash>

class AbstractFilter;

#define DECLARE_READABLE_NAME(rname) static QString readableName(){ QString _readableName(rname); return _readableName; }

typedef std::function<AbstractFilter * ()> filterCreationFunc;

struct FilterInfo
{
    QString type;
    int inputs;
    int outputs;
    filterCreationFunc creationFunc;

    FilterInfo(QString _type = "", int _inputs = 0, int _outputs = 0,
               filterCreationFunc _func = [] () -> AbstractFilter * {return NULL;}):
                type(_type), inputs(_inputs), outputs(_outputs), creationFunc(_func) {}
};

typedef QHashIterator<QString, FilterInfo> FilterInfoIterator;

class FilterCreator
{
public:
    static AbstractFilter * create(QString type){
        return filtersInfo().value(type).creationFunc();
    }

    static void registerFIlter(QString type, int inputs, int outputs, filterCreationFunc func){
        filtersInfo().insert(type, FilterInfo(type, inputs, outputs, func));
    }

    static QHash<QString, FilterInfo> & filtersInfo(){
        static QHash<QString, FilterInfo> _filtersInfo;
        return _filtersInfo;
    }
};

class FilterRegistrator{
public:
    FilterRegistrator(QString type, int inputs, int outputs, filterCreationFunc func){
        FilterCreator::registerFIlter(type, inputs, outputs, func);
    }
};

#define REGISTER_FILTER(filter, inputs, outputs) static FilterRegistrator filter_reg_##filter(##filter::readableName(), inputs, outputs, [] () -> AbstractFilter * { return new  filter(); });


#endif // FILTERCREATOR_H
