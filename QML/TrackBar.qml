import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: root
    property real minValue: 0
    property real maxValue: 100
    property real value: 0
    property int buttonWidth: 40

    signal valueModified()

    width: 200
    height: 50

    Binding on value {
        when: mouseArea.pressed
        value: slider.x / (track.width - slider.width) * (maxValue - minValue) + minValue
    }

    Rectangle {
        id: sliderBackground
        border.color: "gainsboro"
        border.width: 1

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    Rectangle {
        id: minValueButton
        width: buttonWidth

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 5

        color: "gainsboro"

        Text {
            id: minValueButtonText
            text: minValue
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.value = minValue;
                root.valueModified();
            }
        }
    }


    Rectangle {
        id: maxValueButton
        width: buttonWidth

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        color: "gainsboro"


        Text {
            id: maxValueButtonText
            text: maxValue
            //anchors.centerIn: parent.Center
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.value = maxValue;
                root.valueModified();
            }
        }
    }

    Rectangle {
        id: track

        anchors.right: maxValueButton.left
        anchors.left: minValueButton.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        height: buttonWidth / 3

        color: "darkgray"

        Rectangle {
            id: slider

            height: sliderBackground.height - 10
            width: buttonWidth /2
            anchors.verticalCenter: parent.verticalCenter
            color: "gainsboro"

            Binding on x {
                when: !mouseArea.pressed
                value: (root.value - minValue) / (maxValue - minValue) * (track.width - slider.width)
            }

            MouseArea{
                id: mouseArea
                anchors.fill: parent
                drag.target: parent
                drag.minimumX : 0
                drag.maximumX : track.width - width

                drag.axis: Drag.XAxis

                onMouseXChanged: {
                    root.valueModified();
                }
            }

        }
    }

}
