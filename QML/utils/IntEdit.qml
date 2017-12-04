import QtQuick 2.7

Item {
    id: root

    width: 40
    height: 30

    property alias minValue: intValidator.bottom
    property real maxValue: intValidator.top
    property alias value: valueSync.value

    signal valueModified()

    QtObject{
        id: valueSync
        property bool fromEdit: false
        property int value: 0

        onValueChanged: {
            if(valueSync.fromEdit){
                valueSync.fromEdit = false;
                valueModified()
            }
            else{
                textEdit.text = value
            }
        }
    }

    Rectangle{
        id: rect

        anchors.fill: parent

        border.width: 1
        border.color: "gainsboro"

        TextInput{
            id: textEdit

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            validator: IntValidator{
                        id: intValidator
                        bottom: 0
                        top: 100
                        }

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            onEditingFinished: {
                valueSync.fromEdit = true
                valueSync.value = text
            }

            Component.onCompleted: {
                text = root.value
            }
        }

    }
}
