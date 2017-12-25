import QtQuick 2.4
import QtQuick.Controls 2.3

Popup {
    id: root
    width: aboutForm.width
    height: aboutForm.height
    modal: true
    focus: true
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    AboutDialogForm {
        id: aboutForm
        onClicked: root.close()
    }
}


