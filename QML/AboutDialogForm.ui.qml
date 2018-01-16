import QtQuick 2.10
import QtQuick.Controls 2.3

Item {
    id: root
    width: 400
    height: 256

    signal clicked

    Rectangle {
        id: rectangle
        color: "#ffffff"
        border.width: 2
        anchors.fill: parent
        transformOrigin: Item.Center

        Button {
            id: button
            x: 270
            y: 230
            height: 40
            text: qsTr("Close")
            spacing: 0
            leftPadding: 8
            topPadding: 6
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            anchors.right: parent.right
            anchors.rightMargin: 20
        }

        TextArea {
            id: textArea
            height: 99
            text: qsTr("is a simple programm  for 16-bit monochrome image  filtering and viewing. The programm allows to combine filters with each other for serching best way for contrast increasing and nose reducing.")
            anchors.top: titleText.bottom
            anchors.topMargin: 6
            font.pointSize: 8
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 30
            textFormat: Text.AutoText
            wrapMode: Text.WordWrap
        }

        Image {
            id: image
            y: 189
            width: 72
            height: 72
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 30
            fillMode: Image.TileHorizontally
            source: "media/aboutIco.png"
        }

        Text {
            id: titleText
            x: 30
            y: 26
            text: qsTr("GrayScaleVision 1.0")
            anchors.top: parent.top
            anchors.topMargin: 26
            anchors.left: parent.left
            anchors.leftMargin: 30
            font.pixelSize: 18
        }

        SpinBox {
            id: spinBox
            x: 120
            y: 186
            width: 125
            height: 34
            font.weight: Font.Bold
            bottomPadding: 11
            topPadding: 23
            padding: 17
            leftPadding: 43
            font.pointSize: 8
            wheelEnabled: true
            stepSize: 0
            editable: true
        }
    }

    Connections {
        target: button
        onClicked: root.clicked()
    }
}
