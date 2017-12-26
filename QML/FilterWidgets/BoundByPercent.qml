import QtQuick 2.10
import QtQuick.Controls 2.3
import "../utils"

FilterWidget {
    id: root
    name: "BoundByPercent"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty(startParameter.paramName)){
                var startParam = params[startParameter.paramName];
                startParameter.minValue = startParam["min"];
                startParameter.maxValue = startParam["max"];
                startParameter.value = startParam["value"];

            }

            if(params.hasOwnProperty(endParameter.paramName)){
                var endParam = params[endParameter.paramName];
                endParameter.minValue = endParam["min"];
                endParameter.maxValue = endParam["max"];
                endParameter.value = endParam["value"];
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
            font.pointSize: 8
        }

    NumParameter{
        id: startParameter
        property string paramName: "start"
        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":paramName, "value":value})
        }
    }

    NumParameter{
        id: endParameter
        property string paramName: "end"
        anchors.left: parent.left
        anchors.right: parent.right

        onValueModified: {
            root.parameterModified({"name":paramName, "value":value})
        }
    }

    }
}
