import QtQuick 2.0

FilterWidget {
    id: root
    name: "BoundByPercent"

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        text: qsTr("bound image by new min and max values")
        font.family: "Poor Richard"
        font.italic: true
        font.pointSize: 10
        style: Text.Raised
    }
}
