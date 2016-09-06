import QtQuick 2.0
import QtMultimedia 5.4
import camera.filter.test 1.0

Rectangle {
    visible: true
    color: "black"

    Camera {
        id: camera
        viewfinder.resolution: "1280x720"
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
