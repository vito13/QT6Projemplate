import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

/*
Button.onClicked
    ↓
root.mySignal()
    ↓
Window.onMySignal
    ↓
subSignal()
    ↓
Button.onSubSignal
    ↓
Connections.onSubSignal


| 方法          | 示例                     | 使用场景  |
| ----------- | ---------------------- | ----- |
| 同对象 handler | `onMySignal`           | 最常见   |
| 子对象 handler | `Button { onClicked }` | 监听子组件 |
| Connections | `Connections {}`       | 跨对象监听 |

 */
Window {
    id: root
    visible: true
    width: 400
    height: 300

    signal mySignal(string msg)

    Button {
        id: btn
        signal subSignal(string msg)

        text: "send signal"
        anchors.centerIn: parent

        onClicked: {
            console.log("[Button] clicked")

            root.mySignal("hello from root signal")
            subSignal("hello from button signal")
        }

        onSubSignal: function(msg) {
            console.log("[Button handler] subSignal received ->", msg)
        }
    }

    onMySignal: function(msg) {
        console.log("[Window handler] mySignal received ->", msg)
    }

    Connections {
        target: btn // 监听 btn 这个对象发出的 signal

        function onSubSignal(msg) {
            console.log("[Connections handler] subSignal received ->", msg)
        }
        function onClicked() { // 监听 btn 的 clicked 信号
            console.log("clicked")
        }
    }
}