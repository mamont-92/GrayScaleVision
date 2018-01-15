import QtQuick 2.10

import "FilterWidgets"

Item {
    id: root

    property var filterInfo: {}
    property var filterInfoArray: []
    property var widgets: {}
    property string filterName: ""
    property int  filterNumber: -1

    signal parameterModified(int filterNumber, var parameter)

    function updateWidgets(){
        if(filterInfo != null){
            var filterName = filterInfo["name"];
            //root.filterNumber = filterInfo["number"];
            root.filterName = filterName;
            root.widgets[filterName].params = filterInfo["params"];

        }
    }

    function paramsForFilter(filterNumber){
        if(filterInfoArray[filterNumber] = null)
            return null;
        else
            return filterInfoArray[filterNumber].params;
    }

    function setParamsForFilter(filterParams){
        //if(filterParams.hasOwnProperty("filterNumber") && filterParams.hasOwnProperty("params") && filterParams.hasOwnProperty("filterName"))
            filterInfoArray[filterParams.filterNumber] = {"name":filterParams.filterName, "params": filterParams.params};
    }

    function saveParameter(filterNumber, parameter){
        //if(filterInfoArray[filterNumber] == null);
            //filterInfoArray[filterNumber]  = {;

        if(filter["params"]){
            filter.params[parameter.name].value = parameter.value;
        }
    }

    onFilterNumberChanged: {
        /*filterName = filterInfoArray[filterNumber].name;*/
        filterInfo = filterInfoArray[filterNumber];
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
            saveParameter(filterNumber, parameter);
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
            saveParameter(filterNumber, parameter);
            root.parameterModified(filterNumber, parameter)
        }
    }

    CLAHE{
        id: claheWidget
        visible: root.filterName == name
        anchors.fill: parent
        anchors.margins: 1

        onParameterModified: {
            saveParameter(filterNumber, parameter);
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
            saveParameter(filterNumber, parameter);
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
            saveParameter(filterNumber, parameter);
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
            saveParameter(filterNumber, parameter);
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
            saveParameter(filterNumber, parameter);
            root.parameterModified(filterNumber, parameter)
        }
    }
}
