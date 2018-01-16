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
        id:  spinbox

        property int decimals: viewDecimals
        property real factor: Math.pow(10, decimals)

        from: root.minValue * factor
        to: root.maxValue * factor
        stepSize: factor

        validator: DoubleValidator{
            bottom: Math.min(spinbox.from, spinbox.to) / spinbox.factor
            top:  Math.max(spinbox.from, spinbox.to) / spinbox.factor
        }

        textFromValue: function(value, locale) {
            return parseFloat(value*1.0/factor).toFixed(decimals);
        }

        valueFromText: function(text, locale) {
            return parseFloat(text) * factor;
        }

        inputMethodHints: Qt.ImhFormattedNumbersOnly

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 2
        width: 120
        editable: true

        property alias rvalue: root.value

        onRvalueChanged: {
            value = rvalue * factor;
        }

        onValueModified: {
            focus = false;
            rvalue = value / factor;
            root.valueModified();
        }

    }

    TrackBar {
        id: trackBar
        minValue: root.minValue
        maxValue: root.maxValue

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.left: spinbox.right
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
