import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true


Rectangle {
    width: 400
    height: 400
    color: "black"

    Grid {
        x: 5
        y: 5
        rows: 5
        columns: 5
        spacing: 10

        Repeater {
            model: 13
            Rectangle {
                id: delegate

                required property int index

                width: 70
                height: 30
                color: "lightgreen"

                Text {
                    text: delegate.index
                    font.pointSize: 30
                    anchors.centerIn: parent
                }
            }
        }
    }
}
}
