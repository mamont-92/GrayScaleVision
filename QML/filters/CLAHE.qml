import QtQuick 2.0
import QtQuick.Controls 2.2

FilterWidget {
    id: root
    name: "CLAHE"

    QtObject{
        id: paramsStorage
        property int clipCountValue
        property int clipCountMin
        property int clipCountMax

        property int tileSizeValue
        property int tileSizeMin
        property int tileSizeMax
    }

    /**/

    onParamsChanged: {
        if(params != null){
            if(params.hasOwnProperty("clip count")){
                var clipCount = params["clip count"];
                paramsStorage.clipCountValue = clipCount["value"];
                paramsStorage.clipCountMin = clipCount["min"];
                paramsStorage.clipCountMax = clipCount["max"];
            }

            if(params.hasOwnProperty("tile size")){
                var tileSize = params["tile size"];
                paramsStorage.tileSizeValue = tileSize["value"];
                paramsStorage.tileSizeMin = tileSize["min"];
                paramsStorage.tileSizeMax = tileSize["max"];
            }
        }
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

        from: paramsStorage.clipCountMin
        to: paramsStorage.clipCountMax
        value: paramsStorage.clipCountValue
        editable: true

        onValueModified: {
            root.parameterModified({"name":"clip count", "value":value})
        }
    }

}
