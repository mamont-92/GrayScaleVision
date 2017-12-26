import QtQuick 2.10

Item {
    id: root

    property int number: 0
    property int parentNumber: 0

    width : 16
    height : 16

    Rectangle{
        id: background
        property bool isConnected : false
        property bool isHighLight: false
        x: 2
        y: 2
        width : 12
        height : 12

        border.color: isHighLight ? "#7F7F7F" : "#3F3F3F"
        border.width: isHighLight ? 2 : 2
        radius: width / 2
        color: isConnected ? "orange" : "darkorange"

        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: mouseArea.mouseX
        Drag.hotSpot.y: mouseArea.mouseY



        MouseArea{
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            drag.target: dragTarget

            Rectangle {
                id: dragTarget

                property int number: root.number
                property int parentNumber: root.parentNumber

                color: "darkorange"
                width: 6
                height: 6

                x: mouseArea.mouseX - width / 2
                y: mouseArea.mouseY - width / 2

                radius: width / 2
                visible: mouseArea.drag.active
                Drag.active: mouseArea.drag.active
                Drag.hotSpot.x: 3
                Drag.hotSpot.y: 3
            }

            onReleased: dragTarget.Drag.drop()

            onEntered: {
                background.isHighLight = true
            }
            onExited: {
                background.isHighLight = false
            }
        }
    }



}
