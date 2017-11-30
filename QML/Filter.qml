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
    property string name: ""

    signal positionChangedByDrag(real xpos, real ypos)
    signal connected(int outputFilterNumber, int outputConnectorNumber, int inputConnectorNumber)
    signal menuRequest(int xpos, int ypos)

    function reloadImage(){
        image.source = "image://rasterizer/" + root.number + "_" + Math.random();
        console.log(image.source, root.number);
    }

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
        id: background
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.fill: parent

        color: "black"
        border.width: 4
        border.color: type == FilterType.spatial ? "green" : "blue"
        radius: 3
        Image {
            anchors.fill: parent
            anchors.margins: background.border.width
            id: image
            fillMode: Image.PreserveAspectFit
            source: "image://rasterizer/" + root.number
        }

    }

    Text {
        text: name
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: background.border.width
        font.family: "Helvetica"
        font.pointSize: 8
        color: "red"
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
