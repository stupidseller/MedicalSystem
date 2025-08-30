import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

ColumnLayout {
    spacing: 20

    CustomTextInput {
        id: userInput
        placeholderText: "用户名/邮箱"
        Layout.fillWidth: true
    }

    CustomTextInput {
        id: passInput
        placeholderText: "密码"
        echoMode: TextInput.Password
        Layout.fillWidth: true
    }

    ComboBox {
        id: roleComboBox
        model: ["患者", "医生"]
        Layout.fillWidth: true
        background: Rectangle {
            color: Constants.colorBackground
            border.color: Constants.colorBorder
            radius: 4
        }
    }

    Button {
        text: "登录"
        Layout.fillWidth: true
        Layout.preferredHeight: 45
        onClicked: console.log("Login clicked for role: " + roleComboBox.currentText)
    }

    Label {
        text: "忘记密码?"
        Layout.alignment: Qt.AlignRight
        color: Constants.colorBrand
    }
}