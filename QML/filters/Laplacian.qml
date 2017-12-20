import QtQuick 2.7
import QtQuick.Controls 2.2
import "../utils"

FilterWidget {
    id: root
    name: "Laplacian"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty("kernel size")){
                var kernelSize = params["kernel size"];
                kernelSizeParameter.minValue = kernelSize["min"];
                kernelSizeParameter.maxValue = kernelSize["max"];
                kernelSizeParameter.value = kernelSize["value"];

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

            text: qsTr("Laplacian filter")
            font.family: "Poor Richard"
            font.italic: true
            font.pointSize: 10
            style: Text.Raised
        }

    NumParameter{
        id: kernelSizeParameter
        viewDecimals: 0
        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":"kernel size", "value":value})
        }
    }
    }
}
