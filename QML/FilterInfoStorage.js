var filterInfo = [];

function addEmptyFilterIfNull(filterNumber){
    if(filterInfo[filterNumber] == null)
        filterInfo[filterNumber] = {}
}

function removeFilterInfo(filterNumber){
    filterInfo[filterNumber] = null;
}

function setFilterName(filterNumber, name){
    addEmptyFilterIfNull(filterNumber);
    filterInfo[filterNumber].name = name;
}

function setFilterAllParams(filterNumber, params){
    addEmptyFilterIfNull(filterNumber);
    filterInfo[filterNumber].params = params;
}

function setFilterParamValue(filterNumber, paramName, paramValue){
    addEmptyFilterIfNull(filterNumber);
    var filter = filterInfo[filterNumber];
    if(!filter.hasOwnProperty("params"))
        filter.params = {};
    filter.params.paramName = {value: paramValue};
}

function filterName(filterNumber){
    var filter = filterInfo[filterNumber];
    if(filter == null)
        return "";
    if(!filter.hasOwnProperty("name"))
        return "";
    return filter.name;
}

function filterAllParams(filterNumber){
    var filter = filterInfo[filterNumber];
    if(filter == null)
        return null;
    if(!filter.hasOwnProperty("params"))
        return null;
    return filter.params;
}

function filterParam(filterNumber, paramName){
    var filter = filterInfo[filterNumber];
    if(filter == null)
        return null;
    if(!filter.hasOwnProperty("params"))
        return null;
    if(filter.params.hasOwnProperty(paramName))
       return filter.params[paramName].value;
    return null;
}
