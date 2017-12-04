import QtQuick 2.0
import QtQuick.Controls 2.2

FilterWidget{
    id: root
    name: "CLAHE"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("clip count")){
                var clipCount = params["clip count"];
                spinBox.from = clipCount["min"];
                spinBox.to = clipCount["max"];
                spinBox.value = clipCount["value"];

            }

            if(params.hasOwnProperty("tile size")){
                var tileSize = params["tile size"];
                /*paramsStorage.tileSizeMin = tileSize["min"];
                paramsStorage.tileSizeMax = tileSize["max"];
                paramsStorage.tileSizeValue = tileSize["value"];*/
            }
        }
    }

    onParamsChanged: {
        updateParams();
    }

    Text{
        id: text

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        text: qsTr("apply CLAHE algorithm")
        font.family: "Poor Richard"
        font.italic: true
        font.pointSize: 10
        style: Text.Raised
    }

    SpinBox {
        id: spinBox

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text.bottom

        editable: true

        onValueModified: {
            root.parameterModified({"name":"clip count", "value":value})
        }
    }

}
