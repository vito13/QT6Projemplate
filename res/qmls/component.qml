import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15


Window {
    title: qsTr("Tool V1.0.0")
    visible: true
    width: 400
    height: 300

    // 定义 Component
    Component {
        id: redRectComponent

        Rectangle {
            width: 100
            height: 100
            color: "red"
        }
    }

    // 按钮点击时动态创建 Rectangle
    MouseArea {
        anchors.fill: parent
        onClicked: {
            // 创建对象
            let rect = redRectComponent.createObject(parent, {
                x: Math.random() * (parent.width - 100),
                y: Math.random() * (parent.height - 100)
            })
        }
    }
}