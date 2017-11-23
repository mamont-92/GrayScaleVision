import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQml 2.2

import "FilterManagerVisualLogic.js" as FilterManagerLogic

Item {
    id: root

    Component.onCompleted: {
        FilterManagerLogic.fillContexMenuModel(filterCreationContexMenuModel);
        FilterManagerLogic.repeaterModel = filtersModel;
        FilterManagerLogic.canvas = mainCanvas;
    }

    /*DropArea {  //useless now
        anchors.fill: parent
        onDropped: { console.log("red-dropped") } //useless now
    }*/

    function filterByNumber(num){
        for(var i = 0; i < filters.count; i++){
            var f = filters.itemAt(i);
            if(f.number == num)
                return f;
        }
        return null;
    }

    Canvas {
        id: mainCanvas
        anchors.fill: parent
        Path {
            id: pathTemplate
            property real endX: startX
            property real endY: startY
            PathCubic  {
                x: pathTemplate.endX; y: pathTemplate.endY;
                control1X: pathTemplate.startX + (pathTemplate.endX-pathTemplate.startX)/3;
                control1Y: pathTemplate.startY - (pathTemplate.endY - pathTemplate.startY) * 0.25
                control2X: pathTemplate.startX + (pathTemplate.endX-pathTemplate.startX)*2/3;
                control2Y: pathTemplate.startY + (pathTemplate.endY - pathTemplate.startY) * 1.25
            }
        }
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.strokeStyle = Qt.rgba(.4,.6,.8);

            for(var i=0; i < FilterManagerLogic.connections.length; i++){
                var connection = FilterManagerLogic.connections[i];

                var inputFilter = filterByNumber(connection.inputFilter);
                var outputFilter = filterByNumber(connection.outputFilter);
                if( (inputFilter != null) && (outputFilter != null)){
                    var localInputCoords = inputFilter.inputConnectorPos(connection.inputConnector);
                    var localOutputCoords = outputFilter.outputConnectorPos(connection.outputConnector);

                    pathTemplate.startX = localOutputCoords.x+outputFilter.x;
                    pathTemplate.startY = localOutputCoords.y + outputFilter.y;
                    pathTemplate.endX = localInputCoords.x+inputFilter.x;
                    pathTemplate.endY = localInputCoords.y + inputFilter.y;

                    ctx.path = pathTemplate;
                    ctx.stroke();
                }
            }
        }
    }

    MouseArea {
        id: mainMouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if(mouse.button & Qt.RightButton) {
                contextMenu.x = mouseX
                contextMenu.y = mouseY
                contextMenu.open()
            }
        }
    }

    Menu {
        id: contextMenu
        visible: false
        background: Rectangle {
                  implicitWidth: 100
                  implicitHeight: 100
                  color: "#f0f0ff"
                  border.color: "#353637"
              }
        Instantiator {
            model: ListModel {
                id: filterCreationContexMenuModel
            }
            MenuItem {
                text: model.text
                onTriggered: {
                    FilterManagerLogic.createNewFilter(model.text, contextMenu.x, contextMenu.y);
                    FilterManagerLogic.updateCanvas();
                }
            }
            onObjectAdded: contextMenu.insertItem(index, object)
            onObjectRemoved: contextMenu.removeItem(object)
        }
    }

    Repeater {
        id: filters
        anchors.fill: parent
        model: ListModel {
            id: filtersModel
        }

        delegate : Filter {
            id: filter
            x: model.x
            y: model.y
            number: model.number
            name: model.name
            inputNum: model.inputCount
            outputNum: model.outputCount

            Menu {
                property var canvasRef: mainCanvas
                id: filteContexMenu
                visible: false
                background: Rectangle {
                          implicitWidth: 80
                          implicitHeight: 30
                          color: "#f0f0ff"
                          border.color: "#353637"
                      }
                MenuItem {
                    text: "Remove"
                    onTriggered: {
                        FilterManagerLogic.removeFilter(filter.number);
                        FilterManagerLogic.updateCanvas();
                    }
                }
            }

            onPositionChangedByDrag: {
                var ind = FilterManagerLogic.indexInModel(number);
                if(ind != null){
                    filtersModel.setProperty(ind, "x", filter.x);
                    filtersModel.setProperty(ind, "y", filter.y);
                    mainCanvas.requestPaint();
                }
            }
            onConnected: {
                FilterManagerLogic.createNewConnection(outputFilterNumber, outputConnectorNumber, number,inputConnectorNumber);
                FilterManagerLogic.updateCanvas();
            }
            onMenuRequest: {
                filteContexMenu.x = xpos;
                filteContexMenu.y = ypos;
                filteContexMenu.open();
            }
        }
    }
}
