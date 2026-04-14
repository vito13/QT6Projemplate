import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "script tut"

    // 👉 强类型
    property int count: 0
    property real price: 9.9
    property string message: "点击开始"

    // 👉 var：数组（list）
    property var cart: [1, 2, 3]

    // 👉 var：JSON对象
    property var user: ({
        name: "Tom",
        age: 20
    })

    // 👉 null / undefined
    property var optionalData: null
    property var notInit   // = undefined

    Rectangle {
        anchors.fill: parent

        Image {
            anchors.fill: parent
            source: "/images/background.png"
            fillMode: Image.PreserveAspectCrop
        }

        Rectangle {
            anchors.fill: parent
            color: "#80000000"
        }

        Column {
            anchors.centerIn: parent
            spacing: 12

            // ===== 基础数值 =====
            Text {
                text: "count: " + count
                color: "white"
            }

            Text {
                text: "总价: " + (count * price).toFixed(2)
                color: "yellow"
            }

            // ===== JSON 使用 =====
            Text {
                text: "用户: " + user.name + " (" + user.age + ")"
                color: "lightgreen"
            }

            // ===== list 使用 =====
            Text {
                text: "cart长度: " + cart.length
                color: "orange"
            }

            // ===== null / undefined =====
            Text {
                text: "optionalData: " + (optionalData === null ? "null" : "有值")
                color: "pink"
            }

            Text {
                text: "notInit: " + (notInit === undefined ? "undefined" : "有值")
                color: "lightblue"
            }

            // ===== 按钮操作 =====

            Button {
                text: "+1"
                onClicked: {
                    count++
                    message = "点击了 " + count
                }
            }

            Button {
                text: "加入购物车(list)"
                onClicked: {
                    // cart.push(count)
                    // console.log("cart:", cart)
                    var newCart = cart.slice()  // 同“修改JSON”的思路，创建新数组替换原数组，才能触发监听
                    newCart.push(count)
                    cart = newCart
                }
            }

            Button {
                text: "修改JSON"
                onClicked: {
                    // user.age += 1 单独这句没效果，因为只监听 property 本身的变化，不监听 property 内部结构变化
                    user = {
                        name: user.name,
                        age: user.age + 1
                    }
                }
            }

            Button {
                text: "设置非null"
                onClicked: {
                    optionalData = 123
                }
            }

            Button {
                text: "赋值非undefined"
                onClicked: {
                    notInit = 'aaa'
                }
            }

            Button {
                text: "类型转换"
                onClicked: {
                    var s = "123"
                    var n = parseInt(s)
                    var f = parseFloat("3.14")

                    console.log("string -> int:", n)
                    console.log("string -> float:", f)

                    var str = (100 * 3.14).toString()
                    console.log("number -> string:", str)
                }
            }

            // ===== 显示消息 =====
            Text {
                text: message
                color: "white"
            }
        }
    }
}