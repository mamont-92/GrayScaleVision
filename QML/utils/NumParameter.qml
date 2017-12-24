import QtQuick 2.10
import QtQuick.Controls 2.3

Item {
    id: root
    property double minValue: 0
    property double maxValue: 100
    property double value: 0
    property int viewDecimals: 3

    signal valueModified()

    height: 30
    width: 300

    NumEdit{
        id:  spinBox
        minValue: root.minValue
        maxValue: root.maxValue

        decimals: root.viewDecimals

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        property alias rvalue: root.value

        onRvalueChanged: {
            value = rvalue;
        }

        onValueModified: {
            rvalue = value;
            root.valueModified();
        }
    }

    TrackBar {
        id: trackBar
        minValue: root.minValue
        maxValue: root.maxValue

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.left: spinBox.right
        anchors.right: parent.right
        anchors.leftMargin: 2

        property alias rvalue: root.value

        onRvalueChanged: {
            value = rvalue;
        }

        onValueModified: {
            rvalue = value;
            root.valueModified();
        }
    }
}
