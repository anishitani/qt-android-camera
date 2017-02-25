import QtQuick 2.5
import QtMultimedia 5.5
import FilterTest 1.0

Rectangle {
    visible: true
    color: "black"

    Camera {
        id: camera
    }

    VideoOutput {
        id: videoOutput
        source: camera
        anchors.fill: parent
        autoOrientation: true

        filters: [ filterTest ]
    }

    FilterTest {
        id: filterTest
    }
}
