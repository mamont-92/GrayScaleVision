import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Window 2.3
import grayscalevision.fileIO.json 1.0

import Qt.labs.platform 1.0



ApplicationWindow {
    id: root
    visible: true
    width: 1074
    height: 768

    MenuBar {
        Menu {
            title: "&File"

            MenuItem {
                text: "&Open"
            }
            MenuItem {
                text: "&Save As..."
                onTriggered: {
                    saveDialog.open();
                }
            }
            MenuItem {
                text: "&Quit"
            }
        }
        Menu {
            title: "&Help"

            MenuItem {
                text: "&About"
                onTriggered: {
                    aboutDialog.open()
                }
            }
            MenuItem {
                text: "&Show help"
            }
        }
    }

    AboutDialog{
        id: aboutDialog
        leftMargin: (parent.width - width)/2
        rightMargin: (parent.width - width)/2
        topMargin: (parent.height - height)/2
        bottomMargin: (parent.height - height)/2

    }


    FileDialog {
        id: openDialog
        fileMode: FileDialog.OpenFile
        nameFilters: ["Text files (*.txt)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {

        }
    }

    FileDialog {
        id: saveDialog
        fileMode: FileDialog.SaveFile
        nameFilters: ["Text files (*.txt)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted:  {
            var path = file.toString();
            path = path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            console.log(file)
            fileIO.writeJSONToFile(path, filterViewer.getState());
        }
    }

    FIlterViewer{
        id: filterViewer
        anchors.fill: parent
    }

    JsonFileIO{
        id: fileIO
    }

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }


}
