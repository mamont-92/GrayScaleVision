import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQml 2.2

Window {
    id: root
    visible: true
    width: 640
    height: 480

    FilterManager{
        id: filterManager
        anchors.fill: parent
    }

    TrackBar{

    }

}
