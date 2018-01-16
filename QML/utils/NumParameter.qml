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

    SpinBox {
        id:  spinBox
        from: root.minValue
        to: root.maxValue

        validator: DoubleValidator{
            bottom: spinBox.from
            top: spinBox.to
            decimals: root.viewDecimals
        }

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 2
        width: 120
        editable: true

        property alias rvalue: root.value

        onRvalueChanged: {
            value = rvalue;
        }

        onValueModified: {
            rvalue = value;
            focus = false;
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
