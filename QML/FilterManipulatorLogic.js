var lastGenId = -1;
var repeaterModel;
var connections = [];
var repeaterToModelIndex= [];
var canvas;
var FilterManipulator;

var filterCreationTemplate = {
    'blend': {inConnectors: 2, outConnectors: 1},
    'add weighted': {inConnectors: 2, outConnectors: 1},
    'inversion': {inConnectors: 1, outConnectors: 1},
    'source image' : {inConnectors: 0, outConnectors: 1}
}

function genNewId(){
    lastGenId++;
    return lastGenId;
}

function createNewFilter(type, x, y){
    if(filterCreationTemplate.hasOwnProperty(type)){
        var newId = genNewId();
        var filterTemplate = filterCreationTemplate[type];

        if(repeaterModel != null){
            repeaterModel.append({number:newId,
                                     name: type,
                                     x:x, y:y,
                                     inputCount: filterTemplate.inConnectors,
                                     outputCount: filterTemplate.outConnectors});
            if(FilterManipulator != null){
                FilterManipulator.filterAdded(newId, type);
            }
        }      

        return newId;
    }
    return -1;
}

function removeFilter(num){ // TO DO: replace cycle for index in model
    for(var i = 0; i < repeaterModel.count; i++){
        if(repeaterModel.get(i).number == num){
            repeaterModel.remove(i,1);
        }
    }
    removeAllConnectionsWithFilter(num);
    if(FilterManipulator != null){
        FilterManipulator.filterRemove(num);
    }
}

function fillContexMenuModel(id){
    for(var k in filterCreationTemplate){
        id.append({text: k})
    }
}

function updateCanvas(){
    canvas.requestPaint();
}

function indexInModel(num){
    for(var i = 0; i < repeaterModel.count; i++){
        if(repeaterModel.get(i).number == num){
            return i;
        }
    }
    return null;
}

function removeAllInPutConnectionsWithFilter(number){
    connections = connections.filter(function(connection) {
        return connection.inputFilter != number
    });
}

function removeAllOutPutConnectionsWithFilter(number){
    connections = connections.filter(function(connection) {
        return connection.outputFilter != number
    });
}

function removeAllConnectionsWithFilter(number){
    connections = connections.filter(function(connection) {
        return (connection.outputFilter != number) && (connection.inputFilter != number)
    });
}

function removeInputPutConnectionForFilter(filterNumber, connectorNumber){
    connections = connections.filter(function(connection) {
        return (connection.inputFilter != filterNumber) || (connection.inputConnector != connectorNumber)
    });
}

function createNewConnection(outputFilter, outputConnector, inputFilter, inputConnector){
    removeInputPutConnectionForFilter(inputFilter, inputConnector);
    connections.push({outputFilter: outputFilter,
                        outputConnector: outputConnector,
                        inputFilter: inputFilter,
                        inputConnector: inputConnector});
    if(FilterManipulator != null){
        FilterManipulator.connectionAdded(outputFilter, outputConnector, inputFilter,inputConnector);
    }
}

