import QtQuick 2.10
import "utils"
import grayscalevision.core 1.0

Item {
    id: root
    property real minRightPanelRatio: 0.25
    property real maxRightPanelRatio: 0.95
    property real rightPanelRatio: 0.75


    function getState(){
        var curState = {
            "filters" : [], "connections" : [],
            "selected filter" : imageViewer.filterNumber
        };
        var filters = filterManipulator.allFilters();

        for(var i = 0; i < filters.length; ++i){
            var f = filters[i];
            var params = filterProcessor.filterParamsInfo(f.number);
            filters[i]["params"] = {}
            for(var propertyName in params) {
                 filters[i]["params"][propertyName] = params[propertyName]["value"];
            }
        }
        curState["filters"] = filters;
        curState["connections"] = filterManipulator.allConnections();
        return curState;
    }

    FilterManipulator{
        id: filterManipulator
        anchors.fill: parent
        onConnectionAdded: {
            filterProcessor.connectFilters(outputFilterNumber, outputConnectorNumber, inputFilterNumber, inputConnectorNumber);
        }
        onFilterAdded: {
            filterProcessor.addFilter(number, type);
        }
        onFilterRemove: {
            filterProcessor.removeFilter(number);
        }
        onFilerSelected: {
            imageViewer.filterNumber = number;

            filterWidgetManager.filterInfo = {
                "number": number,
                "name" : filterManipulator.filterName(number),
                "params" : filterProcessor.filterParamsInfo(number)
            };
        }

        filterCreationTemplate: filterProcessor.availableFilters()
    }

    Rectangle{
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

    }

    Binding on rightPanelRatio {
        when: borderMouseArea.pressed
        value: leftBorderResizer.x / root.width
    }

    FilterProcessor {
        id: filterProcessor
        onImageRastered: {
            filterManipulator.updateFilterImage(number);
            imageViewer.reloadImage();
        }
    }
}
