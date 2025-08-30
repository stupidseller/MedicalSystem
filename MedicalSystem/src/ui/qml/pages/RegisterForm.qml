import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

ColumnLayout {
    spacing: 20

    ComboBox {
        id: userTypeComboBox
        model: ["患者", "医生"]
        Layout.fillWidth: true
        displayText: "选择用户类型: " + currentText
        background: Rectangle {
            color: Constants.colorBackground
            border.color: Constants.colorBorder
            radius: 4
        }
    }

    CustomTextInput {
        placeholderText: "请设置用户名"
        Layout.fillWidth: true
    }

    CustomTextInput {
        placeholderText: "请输入邮箱"
        Layout.fillWidth: true
    }

    CustomTextInput {
        placeholderText: "请设置密码 (至少6位)"
        echoMode: TextInput.Password
        Layout.fillWidth: true
    }

    CustomTextInput {
        placeholderText: "请再次输入密码"
        echoMode: TextInput.Password
        Layout.fillWidth: true
    }

    Button {
        text: "注册"
        Layout.fillWidth: true
        Layout.preferredHeight: 45
        onClicked: console.log("Register clicked as: " + userTypeComboBox.currentText)
    }

    Label {
        text: "已有账号? 返回登录"
        Layout.alignment: Qt.AlignHCenter
        color: Constants.colorBrand
    }
}