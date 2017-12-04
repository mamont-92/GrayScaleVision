import QtQuick 2.7
import QtQuick.Controls 2.2

Item {
    id: root
    property real minValue: 0
    property real maxValue: 100
    property alias value: valueSync.value

    signal valueModified()

    height: 30
    width: 300

    QtObject{
        id: valueSync
        property real value: 0
        property bool fromTrackBar : false
        property bool fromSpinBox : false

        onValueChanged: {
            if(!fromTrackBar && !fromSpinBox){
                spinBox.value = value;
                trackBar.value = value;
            }
            else{
                if(fromTrackBar){
                    fromTrackBar = false;
                    spinBox.value = value;
                }
                else{
                    fromSpinBox = false;
                    trackBar.value = value;
                }
                root.valueModified();
            }
        }
    }


    IntEdit{
        id:  spinBox
        minValue: root.minValue
        maxValue: root.maxValue

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        onValueModified: {
            valueSync.fromSpinBox = true;
            valueSync.value = value;
        }

        Component.onCompleted: {
            value = valueSync.value
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

        onValueModified: {
            valueSync.fromTrackBar = true;
            valueSync.value = value;
        }

        Component.onCompleted: {
            value = valueSync.value
        }

    }
}
