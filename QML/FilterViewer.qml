import QtQuick 2.0

Item {
    id: root
    property var availableRasterModes
    property var filterInfo

    ImageViewer{
        id: imageViewer

        height: 500
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

    }

    onFilterInfoChanged: {
        if(filterInfo.hasOwnProperty("number")){
            imageViewer.filterNumber = filterInfo.number;
        }
    }

    Component.onCompleted: {
        filterInfo = {}
    }
}
