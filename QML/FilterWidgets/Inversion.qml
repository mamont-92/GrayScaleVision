import QtQuick 2.10

FilterWidget {
    id: root
    name: "inversion"

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("Image inversion")
        font.pointSize: 8
    }
}
