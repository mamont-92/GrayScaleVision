import QtQuick 2.7
import QtQuick.Controls 2.2
import "../utils"

FilterWidget {
    id: root
    name: "BoundByPercent"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("start")){
                var clipCount = params["start"];
                startParameter.minValue = clipCount["min"];
                startParameter.maxValue = clipCount["max"];
                startParameter.value = clipCount["value"];

            }

            if(params.hasOwnProperty("end")){
                var tileSize = params["end"];
                endParameter.minValue = tileSize["min"];
                endParameter.maxValue = tileSize["max"];
                endParameter.value = tileSize["value"];
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

            text: qsTr("bound image by new min and max values")
            font.family: "Poor Richard"
            font.italic: true
            font.pointSize: 10
            style: Text.Raised
        }

    NumParameter{
        id: startParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"start", "value":value})
        }
    }

    NumParameter{
        id: endParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"end", "value":value})
        }
    }

    }
}
