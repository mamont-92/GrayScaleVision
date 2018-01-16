import QtQuick 2.10
import QtQuick.Controls 2.3
import "utils"
import grayscalevision.core 1.0

import "FilterInfoStorage.js" as FilterParamsInfo

Item {
    id: root

    property real minRightPanelRatio: 0.25
    property real maxRightPanelRatio: 0.95
    property real rightPanelRatio: 0.75

    Binding on rightPanelRatio {
        when: resizerMouseArea.pressed
        value: leftSideResizer.x / root.width
    }


    FilterManipulator{
        id: filterManipulator

        anchors.fill: parent

        onConnectionAdded: {
            filterProcessor.connectFilters(outputFilterNumber, outputConnectorNumber, inputFilterNumber, inputConnectorNumber);
        }
        onFilterAdded: {
            FilterParamsInfo.setFilterName(number, type);
            filterProcessor.addFilter(number, type);
        }
        onFilterRemove: {
            FilterParamsInfo.removeFilterInfo(number)
            filterProcessor.removeFilter(number);
        }
        onFilerSelected: {
            filterViewer.currentFilterNum =  number;
        }

        filterCreationTemplate: filterProcessor.availableFilters()
    }

    FilterProcessor {
        id: filterProcessor

        onParamsChanged: { // need it if no params have before, another - ignore because of already imported params
            var oldParams = FilterParamsInfo.filterAllParams(params.filterNumber);
            for(var propertyName in oldParams) {
                params.params[propertyName].value = oldParams[propertyName].value;
            }
            FilterParamsInfo.setFilterAllParams(params.filterNumber, params.params);
        }

        onImageRastered: {
            updateImage(number);
        }
    }

    Rectangle{
        id: leftSideResizer

        property int minX : root.width * root.minRightPanelRatio;
        property int maxX : root.width * root.maxRightPanelRatio;

        color: "grey"
        y: 0
        width: 3
        height: parent.height

        Binding on x {
            when: !resizerMouseArea.pressed
            value: rightPanelRatio*root.width
        }

        MouseArea{
            id: resizerMouseArea
            drag.target: leftSideResizer
            onReleased: leftSideResizer.Drag.drop()
            drag.axis: Drag.XAxis

            cursorShape: Qt.SizeHorCursor;

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top : parent.top
            anchors.bottom: parent.bottom
        }

        onXChanged: {
            if(x < minX)
                x = minX;
            if(x > maxX)
                x = maxX;
        }
    }

    Rectangle{
        id: rightPanel

        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: leftSideResizer.right
        anchors.right: parent.right

        border.color: "grey"
        border.width: 2

        Text {
            id: filterPanelTextText
            anchors.top : parent.top
            anchors.topMargin: 2
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Filter: " + FilterParamsInfo.filterName(filterViewer.currentFilterNum)
        }

        FilterViewer {
            id: filterViewer
            property int currentFilterNum: -1

            anchors.top: filterPanelTextText.bottom
            anchors.bottom: parent.bottom
            anchors.left:  parent.left
            anchors.right: parent.right

            availableRasterModes: filterProcessor.availableRasterModes()

            onCurrentFilterNumChanged: {
                if(currentFilterNum >= 0)
                    filterInfo = { number: currentFilterNum, name: FilterParamsInfo.filterName(currentFilterNum), params: FilterParamsInfo.filterAllParams(currentFilterNum)};
            }

            onCurrentRasterSchemeChanged: {
                if((currentRasterScheme != null) && (currentRasterScheme != ""))
                    filterProcessor.setRasterMode(currentRasterScheme);
            }

            onParameterModified: {
                var val = FilterParamsInfo.filterParam(currentFilterNum, paramName);
                filterProcessor.setParameterValueForFilter(currentFilterNum, paramName, val);
            }
        }

    }


    function updateImage(filterNumber){
        filterManipulator.updateFilterImage(filterNumber);
        if(filterViewer.currentFilterNum == filterNumber)
            filterViewer.reloadImage();
    }

    function filters(){
        return filterManipulator.allFilters();
    }

    function connections(){
        return filterManipulator.allConnections();
    }

    function filterParams(number){
        return FilterParamsInfo.filterAllParams(number);
    }

    function createFilter(name, x, y){
        return filterManipulator.createFilter(name, x, y);
    }

    function connectFilters(filterOut, slotOut, filterIn, slotIn){
        filterManipulator.connectFilters(filterOut, slotOut, filterIn, slotIn);
    }

    function setParamValueForFilter(filterNumber, paramName, paramValue){
        FilterParamsInfo.setFilterParamValue(filterNumber, paramName, paramValue);
        filterProcessor.setParameterValueForFilter(filterNumber, paramName, paramValue);
    }

    function getState(){
        var curState = {
            "filters" : [], "connections" : [],
        };
        var filtersArr = filters();

        for(var i = 0; i < filtersArr.length; ++i){
            var f = filtersArr[i];
            var params = filterParams(f.number);
            filtersArr[i]["params"] = {}
            for(var propertyName in params) {
                filtersArr[i]["params"][propertyName] = params[propertyName]["value"];
            }
        }
        curState["filters"] = filtersArr;
        curState["connections"] = connections();
        return curState;
    }

    function setState(state){
        var indMap = [];
        if(state.hasOwnProperty("filters") && state.hasOwnProperty("connections")){
            var filters = state["filters"];
            for(var i = 0; i < filters.length; ++i){
                var f = filters[i];
                var newInd = createFilter(f.name, f.x, f.y);
                indMap[f.number] = newInd;
                if(f.hasOwnProperty("params")){
                    var params = f.params;
                    for(var propertyName in params) {
                        if(params[propertyName] != null)
                            setParamValueForFilter(newInd, propertyName, params[propertyName])
                    }
                }
            }
            var connections = state["connections"];
            for(i = 0; i < connections.length; ++i){
                var c = connections[i];
                connectFilters(indMap[c.outputFilter], c.outputConnector, indMap[c.inputFilter], c.inputConnector);
            }

        }
    }
}
