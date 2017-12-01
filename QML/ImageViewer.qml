import QtQuick 2.0

Item { // TO DO: replace in filter qml image by this object
    id: root
    property int filterNumber: -1

    onFilterNumberChanged: {
        reloadImage();
    }

    function reloadImage(){
        image.source = "image://rasterizer/" + root.filterNumber + "_" + Math.random();
        console.log(image.source, root.filterNumber);
    }

    Image{
        id: image
        anchors.fill: parent
        anchors.margins: 1
        fillMode: Image.PreserveAspectFit
        //source: "image://rasterizer/" + root.number
    }

}
