import QtQuick 2.10

import "FilterWidgets"

Item {
    id: root

    property string currentFilterName: ""
    property var widgets: {}

    signal parameterModified(string paramName)

    function initFilterParams(filterParams){
        if(root.currentFilterName!="")
            root.widgets[root.currentFilterName].params =  filterParams;
    }

    AddWeighted{
        id: addWeightedWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = addWeightedWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

    BilateralBlur{
        id: bilateralBlurImageWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = bilateralBlurImageWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

    BoundByPercent{
        id: boundByPercentWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = boundByPercentWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

    CLAHE{
        id: claheWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = claheWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

    Inversion{
        id: inversionWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = inversionWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

    Laplacian{
        id: laplacianImageWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = laplacianImageWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }

    }

    Power{
        id: powerImageWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = powerImageWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

    SourceImage{
        id: sourceImageWidget
        visible: root.currentFilterName == name
        anchors.fill: parent
        anchors.margins: 1

        Component.onCompleted: {
            if(root.widgets == null)
               root.widgets = {}
            root.widgets[name] = sourceImageWidget
        }

        onParameterModified: {
            root.widgets[name].params[parameter.name].value = parameter.value;
            root.parameterModified(parameter.name);
        }
    }

}
