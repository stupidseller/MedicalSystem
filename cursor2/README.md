# 智能医疗系统 - Ubuntu Linux 版本

基于 Qt5 Quick/QML 的智能医疗系统登录注册界面，专为 Ubuntu Linux 设计。

## 系统要求

- Ubuntu 18.04 LTS 或更高版本
- Qt 5.12 或更高版本
- CMake 3.10 或更高版本
- GCC 7.0 或更高版本

## 安装依赖

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake
sudo apt install qt5-default qtbase5-dev qtdeclarative5-dev
sudo apt install qtquickcontrols2-5-dev qml-module-qtquick2
sudo apt install qml-module-qtquick-controls2 qml-module-qtgraphicaleffects
```

### 从源码编译 Qt5（可选）
```bash
# 如果系统包管理器中的 Qt5 版本过低
git clone https://code.qt.io/qt/qt5.git
cd qt5
./init-repository --module-subset=qtbase,qtdeclarative,qtquickcontrols2,qtgraphicaleffects
mkdir build && cd build
../configure -prefix /opt/qt5 -opensource -confirm-license
make -j$(nproc)
sudo make install
```

## 构建与运行

### 方法1：使用 Qt Creator（推荐）
1. 安装 Qt Creator：`sudo apt install qtcreator`
2. 打开 Qt Creator → 文件 → 打开文件或项目
3. 选择项目根目录的 `CMakeLists.txt`
4. 配置项目，选择 Desktop Qt 5.x GCC 64-bit Kit
5. 构建 → 构建项目（Ctrl+B）
6. 运行 → 运行（Ctrl+R）

### 方法2：命令行构建
```bash
cd /path/to/project
mkdir build && cd build
cmake ..
make -j$(nproc)
./bin/SmartHealthLogin
```

### 方法3：使用 Ninja（更快）
```bash
sudo apt install ninja-build
cd /path/to/project
mkdir build && cd build
cmake -G Ninja ..
ninja
./bin/SmartHealthLogin
```

## 项目特性

- **Ubuntu 设计语言**：使用 Ubuntu 官方紫色 (#772953) 作为主色调
- **响应式布局**：支持不同屏幕尺寸
- **表单验证**：完整的登录/注册表单验证
- **用户类型切换**：支持患者/医生两种用户类型
- **医生专属字段**：医生注册时显示工号和科室选择

## 文件结构

```
├── CMakeLists.txt          # CMake 构建配置
├── src/
│   └── main.cpp           # 程序入口点
├── qml/
│   ├── main.qml           # 主界面 QML 文件
│   └── qml.qrc            # Qt 资源文件
└── README.md              # 项目说明文档
```

## 故障排除

### 常见问题

1. **找不到 Qt5 模块**
   ```bash
   sudo apt install qt5-default qtbase5-dev
   ```

2. **QML 模块缺失**
   ```bash
   sudo apt install qml-module-qtquick2 qml-module-qtquick-controls2
   ```

3. **图形效果不可用**
   ```bash
   sudo apt install qml-module-qtgraphicaleffects
   ```

4. **字体加载失败**
   - 确保系统安装了 Ubuntu 字体：`sudo apt install fonts-ubuntu`
   - 或下载字体文件到 `qml/fonts/` 目录

### 调试模式
```bash
# 启用 QML 调试
export QML_IMPORT_TRACE=1
export QML_IMPORT_PATH=/usr/lib/x86_64-linux-gnu/qt5/qml
./bin/SmartHealthLogin
```

## 开发说明

- 使用 Qt Quick Controls 2 实现现代化 UI
- 支持高 DPI 显示
- 遵循 Ubuntu 设计规范
- 使用 CMake 进行跨平台构建

## 许可证

本项目采用开源许可证，具体请查看 LICENSE 文件。
