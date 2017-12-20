import QtQuick 2.0

import "filters"

Item {
    id: root

    property var filterInfo: {}
    property var widgets: {}
    property string filterName: ""
    property int  filterNumber: -1

    signal parameterModified(int filterNumber, var parameter)

    function updateWidgets(){
        if(filterInfo != null){
            var filterName = filterInfo["name"];
            root.filterNumber = filterInfo["number"];
            root.filterName = filterName;
            root.widgets[filterName].params = filterInfo["params"];

        }
    }

    onFilterInfoChanged: {
        updateWidgets();
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

        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
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
        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
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

    Power{
        id: powerImageWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = powerImageWidget
        }

        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
        }
    }

    Laplacian{
        id: laplacianImageWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = laplacianImageWidget
        }

        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
        }
    }

    BilateralBlur{
        id: bilateralBlurImageWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = bilateralBlurImageWidget
        }

        onParameterModified: {
            root.parameterModified(filterNumber, parameter)
        }
    }
}
