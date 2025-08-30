pragma Singleton // 关键：将此QML对象设置为全局单例
import QtQuick 2.15

QtObject {
    // --- Colors ---
    readonly property color colorBrand: "#2E74B5" // 主题品牌蓝
    readonly property color colorBrandGradient: "#1F4E79" // 左侧面板渐变色
    readonly property color colorBackground: "#FFFFFF" // 右侧背景白
    readonly property color colorLightGrey: "#F5F7FA" // 浅灰背景（用于系统功能区域）
    readonly property color colorTextPrimary: "#303133" // 主要文字颜色
    readonly property color colorTextSecondary: "#909399" // 次要/提示文字颜色
    readonly property color colorBorder: "#DCDFE6" // 边框颜色

    // --- Fonts ---
    readonly property int fontTitle: 28
    readonly property int fontSubTitle: 16
    readonly property int fontBody: 14
    readonly property int fontSmall: 12
}