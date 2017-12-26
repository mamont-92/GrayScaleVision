import QtQuick 2.10
import QtQuick.Dialogs 1.2

FilterWidget {
    id: root
    name: "SourceImage"

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        text: qsTr("set image from source")
        font.pointSize: 8
    }

    Rectangle{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text.bottom
        anchors.margins: 5
        height: 30
        border.width: 1
        border.color: "grey"

        Text{
            id: buttonText

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            text: qsTr("Open file...")
            font.pointSize: 8
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                openDialog.open();
            }
        }
    }

    FileDialog {
        id: openDialog
        title: "Please choose a 16-bit TIFF file"
        folder: shortcuts.home
        nameFilters: ["TIFF image files (*.tiff *.tif)"]
        onAccepted: {
            var path = openDialog.fileUrl.toString();
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            root.parameterModified({name: "path" , value: path});
        }
        onRejected: {
            console.log("Canceled");
        }
    }
}
