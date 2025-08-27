
# 智慧医疗项目（Smart Medical System）

一个基于 **C++/Qt** 的智慧医疗系统，支持服务端逻辑处理、数据库管理、UI 界面（患者端 & 医生端）等模块，适合扩展和二次开发。

---

## 📂 仓库结构

```
smart\_medical/
├── build/             # 构建输出目录
├── cmake/             # CMake 自定义脚本
├── docs/              # 文档目录（需求、设计、项目计划）
├── schema/            # 数据库结构定义
├── src/               # 核心源码
│   ├── app/           # 程序入口
│   ├── core/          # 业务逻辑层
│   ├── api/           # API 接口层
│   ├── db/            # 数据层（ORM/数据库连接）
│   ├── ui/            # UI 界面（Qt Widgets / QML）
│   ├── common/        # 公共工具
│   └── tests/         # 单元测试
├── third\_party/       # 第三方依赖
├── scripts/           # 构建、运行、部署脚本
├── CMakeLists.txt     # 构建配置
├── .gitignore
└── README.md

```

---

## 🚀 环境准备

在 Ubuntu 上执行：

```bash
sudo apt update
sudo apt install -y build-essential gdb git vim cmake qtcreator qtbase5-dev
````
🗄️ 数据库支持 (Qt SQL)

本项目使用 Qt 自带的 SQL 模块（SQLite）。在 Ubuntu 上执行以下命令安装：

```bash
sudo apt update
sudo apt install -y libqt5sql5 libqt5sql5-sqlite   # Qt5
# 或 Qt6
sudo apt install -y libqt6sql6 libqt6sql6-sqlite
```
---

## 🛠 常用工具介绍

| 工具                | 作用                    | 常见用法                        |
| ----------------- | --------------------- | --------------------------- |
| **gcc/g++**       | 把代码编译成可执行文件           | `g++ main.cpp -o main`      |
| **gdb**           | 调试程序，找 bug            | `gdb ./build/your_program`  |
| **vim**           | 终端文本编辑器               | `vim src/core/foo.cpp`      |
| **make/Makefile** | 自动化构建项目               | `make`、`make clean`         |
| **Qt Creator**    | 集成开发环境，支持 CMake 和 GUI | 打开 `CMakeLists.txt`，点击运行或调试 |

---

## 🔧 构建 & 运行

### 方法 1：命令行 + CMake

```bash
# 克隆仓库
git clone git@github.com:your_name/smart_medical.git
cd smart_medical

# 创建构建目录
# mkdir -p build && cd build
mkdir -p build   # 创建一个叫 build 的文件夹（如果已经有，就不会报错）
cd build         # 进入 build 这个文件夹 


# 配置并构建
cmake ..
cmake --build .

# 运行
./smart_medical
```

### 方法 2：Qt Creator

1. 打开 `Qt Creator`
2. 选择“打开项目”，选中 `CMakeLists.txt`
3. 选择 Kit（自动检测 gcc/gdb）
4. 点击运行或调试

---

## 🐞 调试

### 命令行

```bash
gdb ./build/smart_medical
(gdb) break main
(gdb) run
(gdb) next
(gdb) print variable_name
```

### Qt Creator

点击左下角 🐞 图标，设置断点、单步调试更直观。

---

## 🌱 Git 分支工作流

| 分支              | 说明                                 |
| --------------- | ---------------------------------- |
| **main**        | 稳定正式版本，仅合并经过审核的代码                  |
| **develop**     | 日常开发分支                             |
| **feature/xxx** | 功能开发分支，完成后合并到 `develop`            |
| **hotfix/xxx**  | 紧急修复分支，修复后同时合并到 `main` 和 `develop` |

**常见流程：**

```bash
# 从 develop 拉新功能分支
git checkout develop
git pull
git checkout -b feature/your_feature

# 提交改动
git add .
git commit -m "[core] 完成用户注册接口"
git push -u origin feature/your_feature

# 发起 Pull Request 到 develop 分支
```

---

## 🔄 同步代码

**在另一台电脑拉取：**

```bash
git clone git@github.com:your_name/smart_medical.git
cd smart_medical
mkdir build && cd build
cmake ..
cmake --build .
```

**平时同步更新：**

```bash
git pull   # 拉取最新
git push   # 推送改动
```

---

## ✍️ 开发建议

* **写代码**

  * 用 `vim` 在终端快速编辑：`vim src/core/foo.cpp`
  * 或者直接用 **Qt Creator** 打开工程文件图形化编辑。

* **跑程序**

  * 命令行：`make` 或 `cmake --build .` 后 `./build/xxx`
  * Qt Creator：点运行按钮。

* **调试**

  * 简单问题：用 `printf` 打日志。
  * 复杂问题：命令行 gdb 或 Qt Creator 内置调试器。

---

## 📄 许可证

本项目遵循 [LICENSE](./LICENSE) 协议。

```

---

### 用法提示
- 将 `your_name` 替换为你 GitHub 用户名。  
- 如果未来有 Docker 或脚本启动方式，可以在 `构建 & 运行` 区块新增一节。  
- 这份 README **兼顾了简单易懂和完整信息**，适合团队新人快速上手。
