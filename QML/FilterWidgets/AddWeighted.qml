import QtQuick 2.10
import QtQuick.Controls 2.3
import "../utils"

FilterWidget {
    id: root
    name: "add weighted"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty(alphaParameter.paramName)){
                var alphaParam = params[alphaParameter.paramName];
                alphaParameter.minValue = alphaParam["min"];
                alphaParameter.maxValue = alphaParam["max"];
                alphaParameter.value = alphaParam["value"];

            }

            if(params.hasOwnProperty(betaParameter.paramName)){
                var betaParam = params[betaParameter.paramName];
                betaParameter.minValue = betaParam["min"];
                betaParameter.maxValue = betaParam["max"];
                betaParameter.value = betaParam["value"];
            }

            if(params.hasOwnProperty(gammaParameter.paramName)){
                var gammaParam = params[gammaParameter.paramName];
                gammaParameter.minValue = gammaParam["min"];
                gammaParameter.maxValue = gammaParam["max"];
                gammaParameter.value = gammaParam["value"];
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
            font.pointSize: 8
            style: Text.Raised
        }

        NumParameter{
            id: alphaParameter
            property string paramName: "alpha"
            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":"alpha", "value":value})
            }
        }

        NumParameter{
            id: betaParameter
            property string paramName: "beta"
            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":paramName, "value":value})
            }
        }

        NumParameter{
            id: gammaParameter
            property string paramName: "gamma"
            anchors.left: parent.left
            anchors.right: parent.right
            onValueModified: {
                root.parameterModified({"name":paramName, "value":value})
            }
        }

    }
}
