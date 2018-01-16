import QtQuick 2.10
import QtQuick.Controls 2.3
import "utils"
import grayscalevision.core 1.0

import "FilterInfoStorage.js" as FilterParamsInfo

Item {
    id: root

    FilterProcessor {
        id: filterProcessor

        onParamsChanged: { // need it if no params have before, another - ignore because of already imported params
            var oldParams = FilterParamsInfo.filterParam(params.filterNumber);
            if((oldParams == null) || (oldParams == {}) )
                FilterParamsInfo.setFilterAllParams(params.filterNumber, params.params);
        }

        onImageRastered: {
            updateImage(number);
        }
    }

    function updateImage(filterNumber){
        filterManipulator.updateFilterImage(filterNumber);
        if(filterViewer.currentFilterNum == filterNumber)
            filterViewer.reloadImage();
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

    FilterViewer {
        id: filterViewer
        property int currentFilterNum: -1


        anchors.top: root.top
        anchors.bottom: root.bottom
        width: 300
        anchors.right: root.right

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


    //property real minRightPanelRatio: 0.25
    //property real maxRightPanelRatio: 0.95
    //property real rightPanelRatio: 0.75

    /*function filters(){
        return filterManipulator.allFilters();
    }

    function connections(){
        return filterManipulator.allConnections();
    }

    function filterParams(number){
        return filterWidgetManager.paramsForFilter(number);
    }

    function createFilter(name, x, y){
        return filterManipulator.createFilter(name, x, y);
    }

    function connectFilters(filterOut, slotOut, filterIn, slotIn){
        filterManipulator.connectFilters(filterOut, slotOut, filterIn, slotIn);
    }

    function setParamValueForFilter(filterNumber, paramName, paramValue){
        //filterWidgetManager.saveParameter(filterNumber, {name: paramName, value: paramValue});
        //filterProcessor.setParameterValueForFilter(filterNumber, paramName, paramValue);
    }*/

    /*function getState(){
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
    }*/



    /*Rectangle{
        id: leftBorderResizer

        property int minX : root.width * root.minRightPanelRatio;
        property int maxX : root.width * root.maxRightPanelRatio;

        color: "grey"
        y: 0
        width: 3
        height: parent.height

        Binding on x {
            when: !borderMouseArea.pressed
            value: rightPanelRatio*root.width
        }

        MouseArea{
            id: borderMouseArea
            drag.target: leftBorderResizer
            onReleased: leftBorderResizer.Drag.drop()
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

    FilterPanel{
        id: filterPanel
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: leftBorderResizer.right
        anchors.right: parent.right

        Text {
            id: filterPanelTextText

            anchors.left: parent.left
            anchors.leftMargin: 5

            text: "filter params"
        }

        FilterWidgetManager{
            id: filterWidgetManager
            anchors.left: parent.left
            anchors.right: parent.right
            height: 200
            anchors.bottom: parent.bottom
            anchors.margins: 5
            onParameterModified: {
                filterProcessor.setParameterValueForFilter(filterNumber, parameter["name"], parameter["value"])
            }
        }

        ImageViewer{
            id: imageViewer
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: filterPanelTextText.bottom
            anchors.bottom: filterWidgetManager.top
            anchors.margins: 10
        }

        Rectangle{
            id: rasterModeSelector
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: imageViewer.bottom
            height: comboBox.height+5
            border.width: 1
            border.color: "black"

            Text{
                id: rasterModeText
                text: "Raster mode: "
                font.pointSize: 10
                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox{
                id: comboBox
                anchors.left: rasterModeText.right
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                model: filterProcessor.availableRasterModes()
                height: 30
                currentIndex: model.indexOf("Grayscale")
                onCurrentTextChanged: {
                    filterProcessor.setRasterMode(currentText);
                }
            }

        }

    }

    Binding on rightPanelRatio {
        when: borderMouseArea.pressed
        value: leftBorderResizer.x / root.width
    }*/

    /*FilterProcessor {
        id: filterProcessor
        onImageRastered: {
            filterManipulator.updateFilterImage(number);
            imageViewer.reloadImage();
        }
        onParamsChanged: {

            console.log(filterParams.filterNumber, filterParams.filterName, filterParams.params);

            FilterParamsInfo.setFilterAllParams(params.filterNumber, params.params);
        }
    }*/



}
