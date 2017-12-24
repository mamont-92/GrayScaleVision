import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Window 2.3
import "utils"
import grayscalevision.core 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1074
    height: 768
    property real minRightPanelRatio: 0.25
    property real maxRightPanelRatio: 0.95
    property real rightPanelRatio: 0.75

    menuBar:  MenuBar {
           Menu {
               title: "&File"

               MenuItem {
                   text: "&Open"
               }
               MenuItem {
                   text: "&Save As..."
               }
               MenuItem {
                   text: "&Quit"
               }
           }
           Menu {
               title: "&Help"

               MenuItem {
                   text: "&About"
               }
               MenuItem {
                   text: "&Show help"
               }
           }
    }


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

            filterWidgetManager.filterInfo = {
                            "number": number,
                            "name" : filterManagerVisual.filterName(number),
                            "params" : filterManagerBackend.filterParamsInfo(number)
            };
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
            height: 150
            anchors.bottom: parent.bottom
            anchors.margins: 10
            onParameterModified: {
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

    Component.onCompleted: {
            x = Screen.width / 2 - width / 2
            y = Screen.height / 2 - height / 2
    }


}
