import QtQuick 2.7
import QtQuick.Controls 2.2

import "../utils"

FilterWidget{
    id: root
    name: "CLAHE"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("clip count")){
                var clipCount = params["clip count"];
                clipCountParameter.minValue = clipCount["min"];
                clipCountParameter.maxValue = clipCount["max"];
                clipCountParameter.value = clipCount["value"];

            }

            if(params.hasOwnProperty("tile size")){
                var tileSize = params["tile size"];
                tileSizeParameter.minValue = tileSize["min"];
                tileSizeParameter.maxValue = tileSize["max"];
                tileSizeParameter.value = tileSize["value"];
            }
        }
    }

    onParamsChanged: {
        updateParams();
    }



    Column{
        anchors.fill: parent
        spacing: 5

        Text{
            id: text

            anchors.horizontalCenter: parent.horizontalCenter

            text: qsTr("apply CLAHE algorithm")
            font.family: "Poor Richard"
            font.italic: true
            font.pointSize: 10
            style: Text.Raised
        }

    RealParameter{
        id: clipCountParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"clip count", "value":value})
        }
    }

    RealParameter{
        id: tileSizeParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"tile size", "value":value})
        }
    }

    }


}
