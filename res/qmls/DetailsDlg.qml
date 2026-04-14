import QtQuick
import QtQuick.Controls

Dialog {
    id: dlg
    property int editingRow: -1
    property string name: ""
    property string gender: "男"
    property int departID: -1
    property int majorID: -1

    signal saved()

    Column {
        spacing: 10
        padding: 10

        TextField { placeholderText: "姓名"; text: dlg.name; onTextChanged: dlg.name = text }
        ComboBox {
            id: genderCombo
            model: ["男","女"]
            currentIndex: dlg.gender=="女"?1:0
            onCurrentIndexChanged: dlg.gender = currentText
        }

        ComboBox {
            id: departCombo
            model: ["计算机系","数学系","物理系"] // 可从 C++ 查询 departments
            onCurrentIndexChanged: dlg.departID = currentIndex+1
        }

        ComboBox {
            id: majorCombo
            model: ["软件工程","数学与应用","理论物理"] // 可根据 departID 联动查询 majors
            onCurrentIndexChanged: dlg.majorID = currentIndex+1
        }

        Row {
            spacing: 10
            Button { text: "保存"; onClicked: { dlg.saved(); dlg.close() } }
            Button { text: "取消"; onClicked: dlg.close() }
        }
    }

    function openForNew() {
        editingRow = -1
        name = ""
        gender = "男"
        departID = -1
        majorID = -1
        dlg.open()
    }

    function openForEdit(row) {
        editingRow = row
        var s = studentModel.getStudent(row)
        name = s.name
        gender = s.gender
        departID = s.departID
        majorID = s.majorID
        dlg.open()
    }
}