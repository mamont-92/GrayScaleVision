import QtQuick 2.10
import QtQuick.Controls 2.3
import "../utils"

FilterWidget {
    id: root
    name: "Power"

    function updateParams(){
        if(params != null){
            if(params.hasOwnProperty(powerParameter.paramName)){
                var parameter = params[powerParameter.paramName];
                powerParameter.minValue = parameter["min"];
                powerParameter.maxValue = parameter["max"];
                powerParameter.value = parameter["value"];
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
            font.pointSize: 8
        }

        NumParameter{
            id: powerParameter
            property string paramName: "power"

            anchors.left: parent.left
            anchors.right: parent.right

            onValueModified: {
                root.parameterModified({"name":paramName, "value":value})
            }
        }
    }
}
