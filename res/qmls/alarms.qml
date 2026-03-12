import QtQuick
import QtQuick.Controls


Window  {
    id: window
    width: 400
    height: 300
    visible: true
    title: "Quick Test"
    color: "#ff0000"

    Rectangle {
        anchors.centerIn: parent
        color: "#e4cd05"
        width: parent.width * 0.8
        height: parent.height * 0.5
        focus: true
        Text {
            id: keyview
            text: "Alarms"
            font.pointSize: 24
            anchors.centerIn: parent
        }
        Keys.enabled: true
        Keys.onPressed: {
            event.accepted = true
            keyview.text = "Key pressed: " + event.key
            if (event.key === Qt.Key_Escape) {
                console.log("Escape key pressed, closing application.")
                Qt.quit()
            }
        }
    }
    
    Button {
        text: "Click me!!!"
        checkable: true
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: console.log("Button clicked!")
    }
   
    onWidthChanged: console.log("Width changed to: " + width)
    onHeightChanged: console.log("Height changed to: " + height)
    Component.onCompleted:{
        console.log("Application started with width: " + width + " and height: " + height)
    }
}
