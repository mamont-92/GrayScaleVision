import QtQuick 2.0

Item {
    id: root
    property string name: "add weighted"

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Add two images with weight")
        font.family: "Poor Richard"
        font.italic: true
        font.pointSize: 10
        style: Text.Raised
    }
}
