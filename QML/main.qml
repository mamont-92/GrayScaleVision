import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQml 2.2
import "utils"
import grayscalevision.core 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    property real minRightPanelRatio: 0.25
    property real maxRightPanelRatio: 0.95
    property real rightPanelRatio: 0.75

    Binding on rightPanelRatio {
        when: borderMouseArea.pressed
        value: borderRect.x / root.width
    }

    FilterManagerBackend {
        id: filterManagerBackend
        onImageRastered: {
            filterManagerVisual.updateFilterImage(number);
            imageViewer.reloadImage();
        }
    }


    FilterManagerVisual{
        id: filterManagerVisual
        anchors.fill: parent
        onConnectionAdded: {
            filterManagerBackend.connectFilters(outputFilterNumber, outputConnectorNumber, inputFilterNumber, inputConnectorNumber);
        }
        onFilterAdded: {
            filterManagerBackend.addFilter(number, type);
        }
        onFilterRemove: {
            filterManagerBackend.removeFilter(number);
        }
        onFilerSelected: {
            imageViewer.filterNumber = number;
            filterWidgetManager.currentFilter = number;
            filterWidgetManager.currentName = filterManagerVisual.filterName(number);

        }

        filterCreationTemplate: filterManagerBackend.filterCreationTemplate()
    }


    Rectangle{
        id: borderRect

        property int minX : root.width * root.minRightPanelRatio;
        property int maxX : root.width * root.maxRightPanelRatio;

        color: "grey"
        y: 0
        width: 5
        height: parent.height

        Binding on x {
            when: !borderMouseArea.pressed
            value: rightPanelRatio*root.width
        }

        MouseArea{
            id: borderMouseArea
            drag.target: borderRect
            onReleased: borderRect.Drag.drop()
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
        anchors.left: borderRect.right
        anchors.right: parent.right

        Text {
            id: filterPanelTextText

            anchors.left: parent.left
            anchors.leftMargin: 10

            text: "filter params"
        }



        FilterWidgetManager{
            id: filterWidgetManager
            anchors.left: parent.left
            anchors.right: parent.right
            height: 70
            anchors.bottom: parent.bottom
            anchors.margins: 10
            onParameterModified: {
                //console.log(filterNumber, parameter)
                //root.filterParameterModified({"filterNumber": filterNumber, "parameter":parameter})
                filterManagerBackend.setParameterValueForFilter(filterNumber, parameter["name"], parameter["value"])
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



}
