import QtQuick 2.0
import QtQuick.Controls 2.2

FilterWidget {
    id: root
    name: "CLAHE"

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        text: qsTr("apply CLAHE algorithm")
        font.family: "Poor Richard"
        font.italic: true
        font.pointSize: 10
        style: Text.Raised
    }

    SpinBox {
        id: spinBox

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text.bottom

        from: 2
        to: 120
        editable: true

        onValueModified: {
            root.parameterModified({"name":"clip count", "value":value})
        }

        Component.onCompleted: {
            value = 8
        }
    }

}
