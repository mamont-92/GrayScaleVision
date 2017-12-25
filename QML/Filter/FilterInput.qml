import QtQuick 2.10

Item {
    id: root

    property int number: 0
    property int parentNumber: 0

    signal connected(int filterNumber, int connectorNumber)

    width : 16
    height : 16

    Rectangle{
        id: background
        x: 2
        y: 2
        width : 12
        height : 12
        border.color: isHighLight ? "#7F7F7F" : "#3F3F3F"
        border.width: isHighLight ? 2 : 2
        radius: width / 2
        color: isConnected ? "steelblue" : "orange"

        property bool isConnected : false
        property bool isHighLight: false

        MouseArea{
            propagateComposedEvents: true
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                background.isHighLight = true
            }
            onExited: {
                background.isHighLight = false
            }
        }
    }

    DropArea{
        anchors.fill: parent

        onEntered: {
            background.isHighLight = true
        }
        onDropped: {
            root.connected(drag.source.parentNumber, drag.source.number)
        }
        onExited: {
            background.isHighLight = false
        }
    }



}
