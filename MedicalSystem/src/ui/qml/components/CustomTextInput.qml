import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property alias placeholderText: textField.placeholderText
    property alias text: textField.text
    property alias echoMode: textField.echoMode

    height: 40
    color: Constants.colorBackground
    border.color: Constants.colorBorder
    radius: 4

    TextField {
        id: textField
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        font.pixelSize: Constants.fontBody
        background: Rectangle {
            color: "transparent"
        }
    }
}