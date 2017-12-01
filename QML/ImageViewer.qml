import QtQuick 2.0

Item { // TO DO: replace in filter qml image by this object
    id: root
    clip: true
    property int filterNumber: -1

    onFilterNumberChanged: {
        reloadImage();
    }

    function reloadImage(){
        image.source = "image://rasterizer/" + root.filterNumber + "_" + Math.random();
        console.log(image.source, root.filterNumber);
        resetImageTransform();
    }

    function resetImageTransform(){
        image.x = 0;
        image.y = 0;
        image.width = root.width
        image.height = root.height
        scaleTransform.xScale = 1.0;
        scaleTransform.yScale = 1.0;
    }

    Image{
        id: image
        x:0
        y:0
        fillMode: Image.PreserveAspectFit

        transform: Scale {
            id: scaleTransform
        }

        MouseArea{
            id: mouseArea
            property real zoomFactor: 1.2
            anchors.fill: parent
            drag.target: image
            onReleased: image.Drag.drop()

            onWheel: {

                if(wheel.angleDelta.y > 0)
                    var zoomRatio = zoomFactor
                else
                    zoomRatio = 1.0 / zoomFactor
                var realX = wheel.x * scaleTransform.xScale
                var realY = wheel.y * scaleTransform.yScale
                image.x += (1-zoomRatio)*realX
                image.y += (1-zoomRatio)*realY
                scaleTransform.xScale *=zoomRatio
                scaleTransform.yScale *=zoomRatio
            }
        }

    }





}
