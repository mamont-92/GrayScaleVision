import QtQuick 2.10
import QtQuick.Controls 2.3
import "../utils"

FilterWidget {
    id: root
    name: "BilateralBlur"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty(sigmaIntensityParameter.paramName)){
                var sigmaIntensity = params[sigmaIntensityParameter.paramName];
                sigmaIntensityParameter.minValue = sigmaIntensity["min"];
                sigmaIntensityParameter.maxValue = sigmaIntensity["max"];
                sigmaIntensityParameter.value = sigmaIntensity["value"];
            }

            if(params.hasOwnProperty(sigmaSpaceParameter.paramName)){
                var sigmaSpace = params[sigmaSpaceParameter.paramName];
                sigmaSpaceParameter.minValue = sigmaSpace["min"];
                sigmaSpaceParameter.maxValue = sigmaSpace["max"];
                sigmaSpaceParameter.value = sigmaSpace["value"];
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

            text: qsTr("Bilateral blur filter")
            font.pointSize: 8
        }

        NumParameter{
            id: sigmaIntensityParameter
            property string paramName: "sigma intensity"
            viewDecimals: 0

            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name": paramName, "value":value})
            }
        }

        NumParameter{
            id: sigmaSpaceParameter
            property string paramName: "sigma space"
            viewDecimals: 0

            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":paramName, "value":value})
            }
        }
    }
}
