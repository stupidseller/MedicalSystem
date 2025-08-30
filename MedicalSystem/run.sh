#!/bin/bash

# 项目根目录
PROJECT_DIR="/mnt/hgfs/SmartMedicalProject/MedicalSystem"
# QML文件实际路径（根据CMakeLists.txt，在src/ui/qml/下）
QML_FILE="$PROJECT_DIR/src/ui/qml/main.qml"
# Linux构建目录（全新目录，避免残留）
BUILD_DIR="$PROJECT_DIR/cmake-build-linux-qt512"
# 可执行文件路径（目标名为MedicalSystem，与CMakeLists.txt一致）
EXEC_FILE="$BUILD_DIR/MedicalSystem"

# 同步共享文件夹
echo "=== 正在同步共享文件夹 ==="
if [ -d "/mnt/hgfs" ]; then
  sudo umount /mnt/hgfs 2>/dev/null
  sudo vmhgfs-fuse .host:/ /mnt/hgfs -o allow_other,nonempty
else
  echo "共享文件夹路径不存在，跳过同步"
fi

# 检查QML文件是否存在
if [ ! -f "$QML_FILE" ]; then
  echo "错误：QML文件 $QML_FILE 不存在！"
  exit 1
fi

# 创建并进入构建目录
echo -e "\n=== 准备构建目录 ==="
mkdir -p "$BUILD_DIR" || { echo "创建构建目录失败！"; exit 1; }
cd "$BUILD_DIR" || { echo "进入构建目录失败！"; exit 1; }

# 用系统已有的Qt5.12配置CMake
echo -e "\n=== 生成构建配置（Qt5.12） ==="
QT512_PATH="/opt/qt512/lib/cmake/Qt5"  # 你的系统中已存在此路径
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_PREFIX_PATH="$QT512_PATH" \
      -G "Unix Makefiles" \
      "$PROJECT_DIR"

if [ $? -ne 0 ]; then
  echo "CMake配置失败！可能原因：项目使用了Qt5.15独有特性，必须安装5.15"
  exit 1
fi

# 编译项目
echo -e "\n=== 开始编译 ==="
make -j$(nproc)
if [ $? -ne 0 ]; then
  echo "编译失败！可能项目依赖Qt5.15特性，需安装5.15"
  exit 1
fi

# 运行程序
echo -e "\n=== 启动程序 ==="
if [ -f "$EXEC_FILE" ]; then
  "$EXEC_FILE"
else
  echo "错误：可执行文件不存在！"
  exit 1
fi