import QtQuick 2.7
import QtQuick.Controls 2.2
import "../utils"

FilterWidget {
    id: root
    name: "add weighted"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("alpha")){
                var clipCount = params["alpha"];
                alphaParameter.minValue = clipCount["min"];
                alphaParameter.maxValue = clipCount["max"];
                alphaParameter.value = clipCount["value"];

            }

            if(params.hasOwnProperty("beta")){
                var tileSize = params["beta"];
                betaParameter.minValue = tileSize["min"];
                betaParameter.maxValue = tileSize["max"];
                betaParameter.value = tileSize["value"];
            }

            if(params.hasOwnProperty("gamma")){
                var tileSize = params["gamma"];
                gammaParameter.minValue = tileSize["min"];
                gammaParameter.maxValue = tileSize["max"];
                gammaParameter.value = tileSize["value"];
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

            text: qsTr("Add two images with weight")
            font.family: "Poor Richard"
            font.italic: true
            font.pointSize: 10
            style: Text.Raised
        }

    NumParameter{
        id: alphaParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"alpha", "value":value})
        }
    }

    NumParameter{
        id: betaParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"beta", "value":value})
        }
    }

    NumParameter{
        id: gammaParameter

        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"gamma", "value":value})
        }
    }

    }
}
