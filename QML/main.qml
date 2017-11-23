import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQml 2.2
import "utils"

Window {
    id: root
    visible: true
    width: 640
    height: 480

    FilterManager{
        id: filterManager
        anchors.fill: parent
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
