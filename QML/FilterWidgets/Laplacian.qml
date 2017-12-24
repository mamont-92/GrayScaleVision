import QtQuick 2.10
import QtQuick.Controls 2.3
import "../utils"

FilterWidget {
    id: root
    name: "Laplacian"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty(kernelSizeParameter.paramName)){
                var kernelSize = params[kernelSizeParameter.paramName];
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
            font.pointSize: 8
        }

    NumParameter{
        id: kernelSizeParameter
        property string paramName: "kernel size"
        viewDecimals: 0
        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":paramName, "value":value})
        }
    }
    }
}
