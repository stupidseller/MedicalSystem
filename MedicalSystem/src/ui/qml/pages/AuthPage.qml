import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    RowLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.35
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: Constants.colorBrand
                }
                GradientStop {
                    position: 1.0
                    color: Constants.colorBrandGradient
                }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Text {
                    text: "智能医疗系统"
                    color: "white"
                    font.pixelSize: Constants.fontTitle
                }

                Text {
                    text: "为您提供全面的医疗健康服务"
                    color: "white"
                    opacity: 0.8
                    font.pixelSize: Constants.fontSubTitle
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                anchors.fill: parent
                anchors.leftMargin: parent.width * 0.1
                anchors.rightMargin: parent.width * 0.1
                anchors.topMargin: 40
                anchors.bottomMargin: 40

                TabBar {
                    id: authTabBar
                    Layout.fillWidth: true
                    currentIndex: 0  // 确保默认选中第一个（登录）
                    background: Rectangle {
                        color: "transparent"
                    }

                    TabButton {
                        text: "登录"
                        background: Rectangle {
                            color: parent.checked ? Constants.colorBrand : "transparent"
                            radius: 4
                        }
                        contentItem: Text {
                            text: parent.text
                            color: parent.checked ? "white" : Constants.colorTextPrimary
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    TabButton {
                        text: "注册"
                        background: Rectangle {
                            color: parent.checked ? Constants.colorBrand : "transparent"
                            radius: 4
                        }
                        contentItem: Text {
                            text: parent.text
                            color: parent.checked ? "white" : Constants.colorTextPrimary
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                StackLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: 40
                    Layout.bottomMargin: 40
                    currentIndex: authTabBar.currentIndex

                    LoginForm {}
                    RegisterForm {}
                }

                Item {
                    Layout.fillHeight: true
                }

                Frame {
                    Layout.fillWidth: true
                    background: Rectangle {
                        color: Constants.colorLightGrey
                        radius: 8
                    }
                    padding: 20

                    Column {
                        width: parent.width

                        Label {
                            text: "系统功能"
                            font.bold: true
                        }

                        Label {
                            text: "· 预约就诊  · 电子病历  · 医生管理  · 药品管理"
                            color: Constants.colorTextSecondary
                            topPadding: 10
                        }
                    }
                }
            }
        }
    }
}