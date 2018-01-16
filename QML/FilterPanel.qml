import QtQuick 2.10

Item {
    id: root

    Rectangle{
        id: leftBorderResizer
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        color: "grey"
        width: 5

        MouseArea {
            id: borderMouseArea
            drag.target: leftBorderResizer
            onReleased: leftBorderResizer.Drag.drop()
            drag.axis: Drag.XAxis

            cursorShape: Qt.SizeHorCursor;

            anchors.fill: parent
        }
    }

    Rectangle{
        anchors.left: parent
        border.width: 1
        border.color: "grey"
    }
}
