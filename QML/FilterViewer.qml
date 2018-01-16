import QtQuick 2.10
import QtQuick.Controls 2.3

Item {
    id: root

    property string currentRasterScheme
    readonly property  string defaultRasterShceme: "Grayscale"
    property var availableRasterModes
    property var filterInfo: {}

    signal parameterModified(string paramName)
    signal rasterSchemeModified(string rasterMode)

    function reloadImage(){
        imageViewer.reloadImage();
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

    ComboBox {
        id: comboBoxRasterMode

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: widgetManager.top
        anchors.margins: 3

        height: 30

        model :availableRasterModes
        currentIndex: model.indexOf(defaultRasterShceme)

        onCurrentTextChanged: {
            currentRasterScheme = currentText;
            root.rasterSchemeModified(currentText)
        }
    }

    ImageViewer{
        id: imageViewer

        anchors.top: parent.top
        anchors.bottom: comboBoxRasterMode.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    onFilterInfoChanged: {
        if(filterInfo != null){
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
    }
}
