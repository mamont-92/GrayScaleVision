import QtQuick 2.0
import "types"

Item {
    id: root
    width: 120
    height: 120

    Drag.active : rootMouseArea.drag.active
    Drag.hotSpot.x: 0
    Drag.hotSpot.y: 0

    property int inputNum: 0
    property int outputNum: 0
    property int number: 0
    property int type: FilterType.spatial;

    signal positionChangedByDrag(real xpos, real ypos)
    signal connected(int outputFilterNumber, int outputConnectorNumber, int inputConnectorNumber)
    signal menuRequest(int xpos, int ypos)

    function inputConnectorPos(number){
        var coords = {x:0, y:0}
        if((number >= 0) &(number < inputRepeater.count)){
            var obj = inputRepeater.itemAt(number);
            var tempObject =   mapFromItem(obj, obj.width/2, obj.height/2)
            coords.x = tempObject.x;
            coords.y = tempObject.y;
        }
        return coords;
    }

    function outputConnectorPos(number){
        var coords = {x:0, y:0}
        if((number >= 0) &(number < outputRepeater.count)){
            var obj = outputRepeater.itemAt(number);
            var tempObject =   mapFromItem(obj, obj.width/2, obj.height/2)
            coords.x = tempObject.x;
            coords.y = tempObject.y;
        }
        return coords;
    }

    MouseArea {
        id: rootMouseArea
        anchors.fill: parent
        drag.target: root
        onReleased: root.Drag.drop()
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPositionChanged: {
            root.positionChangedByDrag(root.x, root.y)
        }
        onClicked: {
            if(mouse.button & Qt.RightButton) {
                root.menuRequest(mouseX, mouseY)
            }
        }
    }

    Rectangle {
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.fill: parent

        color: "black"
        border.width: 4
        border.color: type == FilterType.spatial ? "green" : "blue"
        radius: 3
    }

    Column {
        id: inputColumn
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        Repeater{
            id: inputRepeater
            model: inputNum
            delegate: FilterInput{
                id: filterInput
                number: index
                parentNumber: root.number
                onConnected: root.connected(filterNumber, connectorNumber, number)
            }
        }
    }

    Column {
        id: outputColumn
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        Repeater{
            id: outputRepeater
            model: outputNum
            delegate: FilterOutput{
                id: filterOutput
                number: index
                parentNumber: root.number
            }
        }
    }

}
