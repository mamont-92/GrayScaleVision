import QtQuick 2.10
import QtQuick.Controls 2.3

import "../utils"

FilterWidget{
    id: root
    name: "CLAHE"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty(clipCountParameter.paramName)){
                var clipCount = params[clipCountParameter.paramName];
                clipCountParameter.minValue = clipCount["min"];
                clipCountParameter.maxValue = clipCount["max"];
                clipCountParameter.value = clipCount["value"];
            }

            if(params.hasOwnProperty(tileSizeParameter.paramName)){
                var tileSize = params[tileSizeParameter.paramName];
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
            font.pointSize: 8
        }

        NumParameter{
            id: clipCountParameter
            property string paramName: "clip count"
            viewDecimals: 0
            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":paramName, "value":value.toFixed(viewDecimals)})
            }
        }

        NumParameter{
            id: tileSizeParameter
            property string paramName: "tile size"
            viewDecimals: 0
            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":paramName, "value":value.toFixed(viewDecimals)})
            }
        }

    }


}
