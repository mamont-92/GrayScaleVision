import QtQuick 2.10

Item {
    id: root
    property string name: ""
    property var params: {}
    signal parameterModified(var parameter)

}
