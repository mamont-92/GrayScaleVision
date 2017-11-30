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

    FilterManagerBackend {
        id: filterManagerBackend
        onImageRastered: {
            filterManagerVisual.updateFilterImage(number);
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

        filterCreationTemplate: filterManagerBackend.filterCreationTemplate()
    }



    FilterPanel{
        id: filterPanel
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        width: 200
        anchors.right: parent.right

        Text {
            id: filterPanelTextText

            anchors.left: parent.left
            anchors.leftMargin: 10

            text: "filter params"
        }

        RealParameter{
            id: param1

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: filterPanelTextText.bottom
            transform: Scale{ xScale: 0.5; yScale: 0.5}
        }

    }



}
