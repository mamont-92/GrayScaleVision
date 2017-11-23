import QtQuick 2.0
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
                    spinBox.value = value;
                    fromTrackBar = false;
                    console.log("trackbar mod", value)
                }
                else{
                    trackBar.value = value;
                    fromSpinBox = false;
                    console.log("spinbox mod", value)
                }
                root.valueModified();
            }
        }
    }



    SpinBox {
        id: spinBox

        width: 130

        from: minValue
        to: maxValue
        editable: true

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        onValueModified: {
            valueSync.fromSpinBox = true;
            valueSync.value = value;
        }

        Component.onCompleted: {
            value = root.value
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
        anchors.leftMargin: 10

        onValueModified: {
            valueSync.fromTrackBar = true;
            valueSync.value = value;
        }

        Component.onCompleted: {
            value = root.value
        }

    }

}
