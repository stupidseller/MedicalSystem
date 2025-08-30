import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ApplicationWindow {
    id: win
    width: 980
    height: 640
    visible: true
    title: "智能医疗系统 - Ubuntu"
    
    // Ubuntu 风格字体
    FontLoader {
        id: ubuntuFont
        source: "qrc:/fonts/Ubuntu-Regular.ttf"
    }

    Rectangle {
        anchors.fill: parent
        // Ubuntu 风格渐变背景
        gradient: Gradient {
            GradientStop { position: 0; color: "#f7f7f7" }
            GradientStop { position: 1; color: "#e0e0e0" }
        }
    }

    Rectangle {
        id: card
        anchors.centerIn: parent
        width: Math.min(parent.width - 40, 900)
        height: Math.min(parent.height - 40, 560)
        radius: 8
        color: "white"
        layer.enabled: true
        layer.effect: DropShadow { 
            radius: 12; 
            samples: 16; 
            color: "#20000000"; 
            horizontalOffset: 0; 
            verticalOffset: 4 
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 0

            // 左侧头部区域 - Ubuntu 风格
            Rectangle {
                Layout.preferredWidth: parent.width * 0.4
                Layout.fillHeight: true
                gradient: Gradient {
                    GradientStop { position: 0; color: "#772953" }  // Ubuntu 紫色
                    GradientStop { position: 1; color: "#5d2751" }
                }
                radius: 8
                Column {
                    anchors.centerIn: parent
                    spacing: 12
                    Text { 
                        text: "智能医疗系统"; 
                        color: "white"; 
                        font.bold: true; 
                        font.pixelSize: 28;
                        font.family: ubuntuFont.name
                    }
                    Text { 
                        text: "为您提供全面的医疗健康服务"; 
                        color: "#EEFFFFFF"; 
                        font.pixelSize: 16;
                        font.family: ubuntuFont.name
                    }
                }
            }

            // 右侧内容
            Item {
                Layout.preferredWidth: parent.width * 0.6
                Layout.fillHeight: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 24
                    spacing: 20

                    TabBar {
                        id: tabs
                        Layout.fillWidth: true
                        background: Rectangle {
                            color: "transparent"
                            border.bottom: Rectangle { color: "#e0e0e0"; width: 1 }
                        }
                        TabButton { 
                            text: "登录"
                            background: Rectangle {
                                color: tabs.currentIndex === 0 ? "#772953" : "transparent"
                                radius: 4
                            }
                        }
                        TabButton { 
                            text: "注册"
                            background: Rectangle {
                                color: tabs.currentIndex === 1 ? "#772953" : "transparent"
                                radius: 4
                            }
                        }
                    }

                    StackLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        currentIndex: tabs.currentIndex

                        // 登录页
                        ColumnLayout {
                            spacing: 16
                            TextField { 
                                id: loginUser; 
                                placeholderText: "请输入用户名或邮箱"; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    border.color: loginUser.activeFocus ? "#772953" : "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            TextField { 
                                id: loginPwd; 
                                placeholderText: "请输入密码"; 
                                echoMode: TextInput.Password; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    border.color: loginPwd.activeFocus ? "#772953" : "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            ComboBox { 
                                id: loginRole; 
                                Layout.fillWidth: true; 
                                model: ["患者","医生"];
                                background: Rectangle {
                                    radius: 6
                                    border.color: "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            Button {
                                text: "登录"; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    color: parent.pressed ? "#5d2751" : "#772953"
                                }
                                contentItem: Text {
                                    text: parent.text
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                                onClicked: {
                                    if (!loginUser.text || !loginPwd.text) { 
                                        popup.text = "请输入用户名和密码"; 
                                        popup.open(); 
                                        return 
                                    }
                                    if (loginPwd.text.length < 6) { 
                                        popup.text = "密码至少6位"; 
                                        popup.open(); 
                                        return 
                                    }
                                    popup.text = "欢迎以" + loginRole.currentText + "身份登录"; 
                                    popup.open();
                                }
                            }
                        }

                        // 注册页
                        ColumnLayout {
                            spacing: 16
                            property bool isDoctor: userType.currentIndex === 1

                            ComboBox { 
                                id: userType; 
                                Layout.fillWidth: true; 
                                model: ["患者","医生"];
                                background: Rectangle {
                                    radius: 6
                                    border.color: "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            TextField { 
                                id: regUser; 
                                placeholderText: "请设置用户名"; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    border.color: regUser.activeFocus ? "#772953" : "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            TextField { 
                                id: regEmail; 
                                placeholderText: "请输入邮箱"; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    border.color: regEmail.activeFocus ? "#772953" : "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            TextField { 
                                id: regPwd; 
                                placeholderText: "请设置密码（至少6位）"; 
                                echoMode: TextInput.Password; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    border.color: regPwd.activeFocus ? "#772953" : "#e0e0e0"
                                    border.width: 2
                                }
                            }
                            TextField { 
                                id: regPwd2; 
                                placeholderText: "请再次输入密码"; 
                                echoMode: TextInput.Password; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    border.color: regPwd2.activeFocus ? "#772953" : "#e0e0e0"
                                    border.width: 2
                                }
                            }

                            // 医生专属
                            ColumnLayout {
                                visible: parent.isDoctor
                                spacing: 16
                                TextField { 
                                    id: staffId; 
                                    placeholderText: "请输入工号"; 
                                    Layout.fillWidth: true;
                                    background: Rectangle {
                                        radius: 6
                                        border.color: staffId.activeFocus ? "#772953" : "#e0e0e0"
                                        border.width: 2
                                    }
                                }
                                ComboBox { 
                                    id: dept; 
                                    Layout.fillWidth: true; 
                                    model: ["内科","外科","儿科","妇科","骨科","眼科","耳鼻喉科","皮肤科"];
                                    background: Rectangle {
                                        radius: 6
                                        border.color: "#e0e0e0"
                                        border.width: 2
                                    }
                                }
                            }

                            Button {
                                text: "注册"; 
                                Layout.fillWidth: true;
                                background: Rectangle {
                                    radius: 6
                                    color: parent.pressed ? "#5d2751" : "#772953"
                                }
                                contentItem: Text {
                                    text: parent.text
                                    color: "white"
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                                onClicked: {
                                    if (!regUser.text || !regEmail.text || !regPwd.text || !regPwd2.text) { 
                                        popup.text = "请完整填写信息"; 
                                        popup.open(); 
                                        return 
                                    }
                                    if (regPwd.text.length < 6) { 
                                        popup.text = "密码至少6位"; 
                                        popup.open(); 
                                        return 
                                    }
                                    if (regPwd.text !== regPwd2.text) { 
                                        popup.text = "两次输入的密码不一致"; 
                                        popup.open(); 
                                        return 
                                    }
                                    if (userType.currentIndex === 1 && !staffId.text) { 
                                        popup.text = "请输入工号"; 
                                        popup.open(); 
                                        return 
                                    }
                                    popup.text = (userType.currentIndex===1?"医生":"患者") + "注册成功"; 
                                    popup.open();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Popup {
        id: popup
        x: (win.width - width) / 2
        y: win.height - height - 40
        width: 280
        height: implicitHeight
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background: Rectangle { 
            radius: 8; 
            color: "#772953";
            border.color: "#5d2751";
            border.width: 1;
        }
        contentItem: Text { 
            color: "white"; 
            text: popup.text; 
            wrapMode: Text.Wrap; 
            padding: 16; 
            horizontalAlignment: Text.AlignHCenter;
            font.family: ubuntuFont.name
        }
        property string text: ""
    }
}
