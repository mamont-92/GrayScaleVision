import QtQuick 2.0

import "filters"

Item {
    id: root

    property string currentName: ""
    property int currentFilter: -1

    signal parameterModified(int filterNumber, var parameter)

    AddWeighted{
        id: addWeightedWidget
        visible: root.currentName == name
        anchors.fill: parent
        anchors.margins: 1
    }

    BoundByPercent{
        id: boundByPercentWidget
        visible: root.currentName == name
        anchors.fill: parent
        anchors.margins: 1
    }

    CLAHE{
        id: claheWidget
        visible: root.currentName == name
        anchors.fill: parent
        anchors.margins: 1
    }

    Inversion{
        id: inversionWidget
        visible: root.currentName == name
        anchors.fill: parent
        anchors.margins: 1
    }

    SourceImage{
        id: sourceImageWidget
        visible: root.currentName == name
        anchors.fill: parent
        anchors.margins: 1

        onParameterModified: {
            root.parameterModified(currentFilter, parameter)
        }
    }
}
