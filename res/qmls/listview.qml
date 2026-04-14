import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// ApplicationWindow {
//     id: root
//     width: 300
//     height: 300
//     visible: true

   
   Rectangle {
    id: button
    signal clicked

    width: 150; height: 50; radius: 3
    color: tapHandler.pressed ? "goldenrod" : hoverHandler.hovered ? "wheat" : "beige"
    border.color: activeFocus ? "brown" : "transparent"
    focus: true

    HoverHandler {
        id: hoverHandler
    }

    TapHandler {
        id: tapHandler
        onTapped: button.clicked()
    }

    Keys.onEnterPressed: button.clicked()
}
// }