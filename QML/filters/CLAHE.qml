import QtQuick 2.0

FilterWidget {
    id: root
    name: "CLAHE"

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("apply CLAHE algorithm")
        font.family: "Poor Richard"
        font.italic: true
        font.pointSize: 10
        style: Text.Raised
    }
}
