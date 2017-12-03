import QtQuick 2.0

import "filters"

Item {
    id: root

    property var filterInfo: {}
    property var widgets: {}
    property string filterName: ""
    property int  filterNumber: -1

    signal parameterModified(int filterNumber, var parameter)


    onFilterInfoChanged: {
        if(filterInfo != null){
            var filterName = filterInfo["name"];
            root.widgets[filterName].params = filterInfo["params"];
            root.filterNumber = filterInfo["number"];
            root.filterName = filterName;

        }
    }


    AddWeighted{
        id: addWeightedWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = addWeightedWidget
        }
    }

    BoundByPercent{
        id: boundByPercentWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = boundByPercentWidget
        }
    }

    CLAHE{
        id: claheWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
        }


        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = claheWidget
        }
    }

    Inversion{
        id: inversionWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = inversionWidget
        }
    }

    SourceImage{
        id: sourceImageWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = sourceImageWidget
        }

        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
        }
    }
}
