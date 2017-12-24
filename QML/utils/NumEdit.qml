import QtQuick 2.10

Item {
    id: root

    width: 40
    height: 30

    property alias minValue: doubleValidator.bottom
    property alias maxValue: doubleValidator.top
    property double value: 0
    property alias decimals: doubleValidator.decimals

    signal valueModified()

    Rectangle{
        id: rect

        anchors.fill: parent

        border.width: 1
        border.color: "gainsboro"

        TextInput{
            id: textEdit

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            validator: DoubleValidator{
                            id: doubleValidator
                            bottom: 0.0
                            top: 1.0
                            notation: DoubleValidator.StandardNotation
                        }

            inputMethodHints: Qt.ImhFormattedNumbersOnly

            property alias rvalue: root.value

            onEditingFinished: {
                focus = false
                rvalue = text;
                root.valueModified()
            }

            onRvalueChanged: {
                text = rvalue.toFixed(decimals);
            }
        }

    }
}
