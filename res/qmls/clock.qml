import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "Clock"
    property string currTime: "00:00:00"
    property QtObject backend

    FileDialog {
        id: fileDialog
        title: "选择文件"
        currentFolder: StandardPaths.documents
        nameFilters: ["Text files (*.txt)", "All files (*)"]

        onAccepted: {
            console.log("选择文件:", fileDialog.fileUrl)  // 单个文件
        }
        onRejected: {
            console.log("取消选择")
        }
    }

    Rectangle {
        anchors.fill: parent

        Image {
            anchors.fill: parent
            source: "/images/background.png"
            fillMode: Image.PreserveAspectCrop
            Button {
                background: Rectangle {
                    radius: 8
                    color: "green"
                }
                contentItem: Text {
                    text: "Click Me"
                    color: "yellow"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                anchors {
                    bottom: parent.bottom
                    bottomMargin: 12
                    right: parent.right
                    leftMargin: 12
                }
                onClicked: {
                    fileDialog.open()
                }
            }        
                    

            Text {
                text: currTime
                font.pixelSize: 48
                color: "pink"
                style: Text.Outline
                styleColor: "green"
                anchors {
                    bottom: parent.bottom
                    bottomMargin: 12
                    left: parent.left
                    leftMargin: 12
                }

                Component.onCompleted: {
                    console.log(color.r, color.g, color.b, color.a);
                }
            }

            Item {
                id: item
                width: 400
                height: 400
                Rectangle {
                    id: itemrect
                    anchors.fill: parent
                    color: "lightgray"
                }
                Item {
                    id: itemitem
                    anchors.centerIn: parent
                    width: 100
                    height: 100
                    Rectangle {
                        anchors.fill: parent
                        color: "gray"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            Qt.quit(); // 点击窗口时退出应用
                        }
                    }
                    focus: true   // 关键，允许接收键盘事件

                    Keys.onPressed: {
                        if (event.key === Qt.Key_Left) {
                            console.log("左键按下")
                        } else if (event.key === Qt.Key_Right) {
                            console.log("右键按下")
                        }
                    }

                    Keys.onReleased: {
                        console.log("按键释放:", event.key)
                    }
                }
            }
        }
    }

    Connections {
        // Connections 用于监听 QML 以外对象的信号
        target: backend // 监听 backend 对象发出的信号

        function onUpdated(msg) { // 当 backend 发出 updated 信号时，更新 currTime 属性
            currTime = msg; // 更新 QML UI显示的时间字符串
        }
    }
}
