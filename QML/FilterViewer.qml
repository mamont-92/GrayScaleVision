import QtQuick 2.0

Item {
    id: root
    property var availableRasterModes
    property var filterInfo

    signal parameterModified(string paramName)

    function reloadImage(){
        imageViewer.reloadImage();
    }

    ImageViewer{
        id: imageViewer

        height: 500
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

    }

    FilterWidgetManager{
        id: widgetManager
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 200

        onParameterModified: {
            root.parameterModified(paramName)
        }

    }

    onFilterInfoChanged: {
        if(filterInfo.hasOwnProperty("number")){
            imageViewer.filterNumber = filterInfo.number;
        }
        if(filterInfo.hasOwnProperty("name")){
            widgetManager.currentFilterName = filterInfo.name;
            if(filterInfo.hasOwnProperty("params")){
                widgetManager.initFilterParams(filterInfo.params)
            }
        }
    }

    Component.onCompleted: {
        filterInfo = {}
    }
}
