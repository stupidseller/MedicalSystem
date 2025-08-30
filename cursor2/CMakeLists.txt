cmake_minimum_required(VERSION 3.10)

project(SmartHealthLogin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 关键：启用 Qt 的自动 MOC 以生成元对象代码，避免 vtable 链接错误
set(CMAKE_AUTOMOC ON)
# 可选：为将来使用 .ui/.qrc 做准备
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Quick Qml REQUIRED)

set(SOURCES
    src/main.cpp
)

set(HEADERS
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Quick Qt5::Qml
)

# Linux 特定配置
if(UNIX AND NOT APPLE)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    # Ubuntu 系统信息
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX_UBUNTU)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 资源文件
qt5_add_resources(QML_RESOURCES qml/qml.qrc)
target_sources(${PROJECT_NAME} PRIVATE ${QML_RESOURCES})


