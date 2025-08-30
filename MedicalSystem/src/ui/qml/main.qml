import QtQuick 2.15
import QtQuick.Controls 2.15
// 删除这行：import "AuthPage.qml"

ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 720
    minimumWidth: 1024
    minimumHeight: 600
    title: "智慧医疗系统"

    AuthPage {
        anchors.fill: parent
    }
}