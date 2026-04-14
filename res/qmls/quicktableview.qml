import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 800
    height: 400
    title: "学生管理"
    font.pointSize: 16

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 表头
        Row {
            spacing: 10
            Rectangle {
                width: 100
                height: 30
                color: "#ddd"
                Text {
                    text: "学号"
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                width: 150
                height: 30
                color: "#ddd"
                Text {
                    text: "姓名"
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                width: 80
                height: 30
                color: "#ddd"
                Text {
                    text: "性别"
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                width: 150
                height: 30
                color: "#ddd"
                Text {
                    text: "院系"
                    anchors.centerIn: parent
                }
            }
            Rectangle {
                width: 150
                height: 30
                color: "#ddd"
                Text {
                    text: "专业"
                    anchors.centerIn: parent
                }
            }
        }

        TableView {
            id: table
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: studentModel

            columnSpacing: 5
            selectionModel: ItemSelectionModel {
                model: table.model
            }

            delegate: Row {
                spacing: 10

                 MouseArea {
                    anchors.fill: parent
                    onClicked: table.selection.select(styleData.row)
                }

                // color: styleData.row % 2 === 0 ? "#f7f7f7" : "#ffffff"
                Text {
                    text: studID
                    width: 100
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: name
                    width: 150
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: gender
                    width: 80
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: department
                    width: 150
                    verticalAlignment: Text.AlignVCenter
                }
                Text {
                    text: major
                    width: 150
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 15
            Button {
                text: "新增"
                onClicked: detailsDlg.openForNew()
            }
            Button {
                text: "编辑"
                onClicked: {
                    if (table.selection.currentIndex >= 0)
                        detailsDlg.openForEdit(table.selection.currentIndex);
                }
            }
            Button {
                text: "删除"
                onClicked: {
                    if (table.selection.currentIndex >= 0)
                        studentModel.deleteStudent(table.selection.currentIndex);
                }
            }
        }
    }

    DetailsDlg {
        id: detailsDlg
        onSaved: {
            if (editingRow >= 0)
                studentModel.editStudent(editingRow, name, gender, departID, majorID);
            else
                studentModel.addStudent(name, gender, departID, majorID);
        }
    }
}
