# 设置CMake所需的最低版本
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和语言
project(MedicalSystem VERSION 1.0 LANGUAGES CXX)

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用CMake对Qt的自动化支持
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找Qt5的安装路径。现在我们核心需要的是Qml和Quick
find_package(Qt5 5.15 REQUIRED COMPONENTS Core Gui Qml Quick)

# 添加可执行文件目标
# 我们需要将qrc文件也加入编译目标，这样CMake才能处理它
add_executable(MedicalSystem
        src/app/main.cpp
        src/ui/qml/qml.qrc
        src/core/service/LoginHandler.h
        src/core/service/LoginHandler.cpp
)

# 将Qt5的库链接到我们的应用程序中
# 注意：我们已经移除了Widgets，替换为Gui
target_link_libraries(MedicalSystem PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)