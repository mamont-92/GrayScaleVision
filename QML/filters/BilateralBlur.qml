import QtQuick 2.10
import QtQuick.Controls 2.3
import "../utils"

FilterWidget {
    id: root
    name: "BilateralBlur"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("sigma intensity")){
                var sigmaIntensity = params["sigma intensity"];
                sigmaIntensityParameter.minValue = sigmaIntensity["min"];
                sigmaIntensityParameter.maxValue = sigmaIntensity["max"];
                sigmaIntensityParameter.value = sigmaIntensity["value"];
            }

            if(params.hasOwnProperty("sigma space")){
                var sigmaSpace = params["sigma space"];
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
            font.family: "Poor Richard"
            font.italic: true
            font.pointSize: 10
            style: Text.Raised
        }

        NumParameter{
            id: sigmaIntensityParameter
            viewDecimals: 0

            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":"sigma intensity", "value":value})
            }
        }

        NumParameter{
            id: sigmaSpaceParameter
            viewDecimals: 0

            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":"sigma space", "value":value})
            }
        }
    }
}
