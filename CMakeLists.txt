cmake_minimum_required(VERSION 3.16)
project(smart_medical LANGUAGES CXX)

# 设置C++标准（与Qt兼容的版本）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt模块（根据项目用到的模块添加，缺一不可）
find_package(Qt5 COMPONENTS 
    Core 
    Widgets 
    Sql 
    Test  # 用于单元测试（tst_user_dao.cpp）
    REQUIRED
)

# 自动处理moc/uic/rcc（必须添加，否则Qt元对象系统失效）
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --------------------------
# 主程序源码（按GitHub目录结构组织）
# --------------------------
set(SOURCES
    src/server/app/main.cpp
    src/server/ui/widgets/common/mainwindow.cpp
    src/server/db/app_database.cpp
    src/server/core/dao/user_dao.cpp
    src/server/core/service/user_repository.cpp
    src/server/ui/widgets/common/hospital_view_model.cpp
    src/server/common/utils/crypto_utils.h  # 纯头文件工具类
    src/server/core/model/user_entity.h     # 数据模型
)

# UI文件（如果有.ui文件，需添加路径，如mainwindow.ui）
set(FORMS
    src/server/ui/widgets/common/mainwindow.ui
)

# --------------------------
# 主程序目标
# --------------------------
add_executable(smart_medical
    ${SOURCES}
    ${FORMS}
)

# 链接Qt模块和主程序
target_link_libraries(smart_medical PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Sql
)

# 头文件路径（告诉编译器去哪里找#include的文件）
target_include_directories(smart_medical PRIVATE
    src/server/core/model
    src/server/common/utils
    src/server/db
    src/server/core/dao
    src/server/core/service
    src/server/ui/widgets/common
)

# --------------------------
# 单元测试（tst_user_dao.cpp）
# --------------------------
set(TEST_SOURCES
    src/server/tests/core/tst_user_dao.cpp
)

add_executable(test_user_dao
    ${TEST_SOURCES}
    ${SOURCES}  # 测试需要依赖主程序源码
)

# 测试目标链接QtTest和其他模块
target_link_libraries(test_user_dao PRIVATE
    Qt5::Core
    Qt5::Sql
    Qt5::Test
)

# 测试头文件路径（与主程序一致）
target_include_directories(test_user_dao PRIVATE
    src/server/core/model
    src/server/common/utils
    src/server/db
    src/server/core/dao
    src/server/core/service
)

# 注册测试（可选，便于用ctest运行）
add_test(NAME UserDaoTest COMMAND test_user_dao)