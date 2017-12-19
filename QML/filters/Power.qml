import QtQuick 2.7
import QtQuick.Controls 2.2
import "../utils"

FilterWidget {
    id: root
    name: "Power"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("power")){
                var clipCount = params["power"];
                powerParameter.minValue = clipCount["min"];
                powerParameter.maxValue = clipCount["max"];
                powerParameter.value = clipCount["value"];

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

            text: qsTr("power image values")
            font.family: "Poor Richard"
            font.italic: true
            font.pointSize: 10
            style: Text.Raised
        }

    NumParameter{
        id: powerParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"power", "value":value})
        }
    }
    }
}
