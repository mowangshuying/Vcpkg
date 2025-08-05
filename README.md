# Vcpkg
## Vscode 中使用vcpkg
### 设置vcpkg
ref:https://learn.microsoft.com/zh-cn/vcpkg/get_started/get-started-vscode?pivots=shell-powershell
1.克隆存储库

第一步是从 GitHub 克隆 vcpkg 存储库。 存储库包含用于获取 vcpkg 可执行文件的脚本，以及由 vcpkg 社区维护的特选开放源代码库的注册表。 要执行此操作，请运行：

```
git clone https://github.com/microsoft/vcpkg.git
```

vcpkg 特选注册表是一组数量超过 2000 个的开源库。 这些库已通过 vcpkg 的持续集成管道进行验证，可以协同工作。 虽然 vcpkg 存储库不包含这些库的源代码，但它保存方案和元数据，以便在系统中生成和安装它们。

2.运行启动脚本

现在，你已经克隆了 vcpkg 存储库，请导航到 vcpkg 目录并执行启动脚本：

```
cd vcpkg; .\bootstrap-vcpkg.bat
```
启动脚本执行先决条件检查并下载 vcpkg 可执行文件。

就这么简单！ vcpkg 已安装并可供使用。

### 创建项目文件夹
创建一个文件夹以将项目文件保存在所选位置。 在本教程中，我们将创建一个名为“helloworld”的文件夹。 然后使用 Visual Studio Code 打开该文件夹。
```
mkdir helloworld
code helloworld
```

### 安装Visual Studio Code 扩展
导航到“扩展”视图并安装 C++ 扩展。 此操作将启用 C++ IntelliSense 和代码导航。

![安装 C++ Visual Studio Code 扩展](.\imgs\vscode-c-extension.png)
安装 CMake 工具扩展。 这将在 Visual Studio Code 中启用 CMake 支持。

![安装 CMake Tools Visual Studio Code 扩展](.\imgs\vscode-cmake-extension.png)

### 设置环境变量

1.配置 `VCPKG_ROOT` 环境变量。

在 Visual Studio Code 中打开新的终端：**终端 > 新建终端**）。

运行以下命令：

 备注

以这种方式设置环境变量只会影响当前终端会话。 若要使这些更改在所有会话中永久存在，请通过“Windows 系统环境变量”面板进行设置。

PowerShell复制

```PowerShell
$env:VCPKG_ROOT="C:\path\to\vcpkg"
$env:PATH="$env:VCPKG_ROOT;$env:PATH"
```

![设置 vcpkg 环境变量](.\imgs\vscode-terminal-vcpkg.png)

在 Visual Studio Code 终端中设置 VCPKG_ROOT 并将其添加到 PATH 中的屏幕截图。



 备注

以这种方式设置环境变量只会影响当前终端会话。 若要使这些更改在所有会话中永久存在，请通过“Windows 系统环境变量”面板进行设置。

设置 `VCPKG_ROOT` 可帮助 Visual Studio Code 查找 vcpkg 实例。 将它添加到 `PATH` 确保可以直接从 shell 运行 vcpkg 命令。

1. 生成清单文件并添加依赖项。

运行以下命令，在 `vcpkg.json` 文件夹的根目录中创建 vcpkg 清单文件 (`helloworld`)：

控制台复制

```console
vcpkg new --application
```

[`vcpkg new`](https://learn.microsoft.com/zh-cn/vcpkg/commands/new) 命令在项目的目录中添加一个 `vcpkg.json` 文件和一个 `vcpkg-configuration.json` 文件。

添加 `fmt` 包作为依赖项：

控制台复制

```console
vcpkg add port fmt
```

`vcpkg.json` 现在应包含：

JSON复制

```json
{
  "dependencies": [
    "fmt"
  ]
}
```

这是清单文件。 vcpkg 读取清单文件，了解要安装和与 CMake 集成的依赖项，以提供项目所需的依赖项。

生成的 `vcpkg-configuration.json` 文件引入了一个[基线](https://learn.microsoft.com/zh-cn/vcpkg/reference/vcpkg-configuration-json#registry-baseline)，用于对项目的依赖项设置[最低版本约束](https://learn.microsoft.com/zh-cn/vcpkg/users/versioning)。 修改此文件超出了本教程的范围。 虽然在本教程中不适用，但建议将 `vcpkg-configuration.json` 文件保留在源代码管理之下，以确保不同开发环境中的版本一致性。

### 设置项目文件

1. 创建 `CMakeLists.txt` 文件

在项目文件夹的根目录中使用以下内容创建名为 `CMakeLists.txt` 的新文件：

cmake复制

```cmake
cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(fmt CONFIG REQUIRED)

add_executable(HelloWorld helloworld.cpp)

target_link_libraries(HelloWorld PRIVATE fmt::fmt)
```

我们来逐一了解 `CMakeLists.txt` 文件中的每一行：

- `cmake_minimum_required(VERSION 3.10)`：指定生成项目所需的 CMake 最低版本为 3.10。 如果系统上安装的 CMake 版本低于此版本，则将生成错误。
- `project(HelloWorld)`：将项目的名称设置为 "HelloWorld."。
- `find_package(fmt CONFIG REQUIRED)`：使用 `fmt` 库的 CMake 配置文件查找该库。 `REQUIRED` 关键字确保在找不到包时生成错误。
- `add_executable(HelloWorld helloworld.cpp)`：添加从源文件 `helloworld.cpp` 生成的名为 "HelloWorld," 的可执行目标。
- `target_link_libraries(HelloWorld PRIVATE fmt::fmt)`：指定 `HelloWorld` 可执行文件应链接到 `fmt` 库。 `PRIVATE` 关键字表明 `fmt` 仅在生成 `HelloWorld` 时需要，不应传播到其他依赖项目。

1. 创建包含以下内容的 `helloworld.cpp` 文件：

C++复制

```cpp
#include <fmt/core.h>

int main()
{
    fmt::print("Hello World!\n");
    return 0;
}
```

在此 `helloworld.cpp` 文件中，包含用于使用 `<fmt/core.h>` 库的 `fmt` 标头。 然后，`main()` 函数调用 `fmt::print()` 将 "Hello World!" 消息输出到控制台。

要允许 CMake 项目系统识别 vcpkg 提供的 C++ 库，需要提供 `vcpkg.cmake` 工具链文件。 要自动执行此操作，请在包含以下内容的 "helloworld" 目录中创建一个 `CMakePresets.json` 文件：

JSON复制

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "vcpkg",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      }
    }
  ]
}
```

1. 使用以下内容在“helloworld”目录中创建 `CMakeUserPresets.json` 文件：

JSON复制

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "<path to vcpkg>"
      }
    }
  ]
}
```

此 `CMakePresets.json` 文件包含适用于 CMake 的单个“vcpkg”预设并设置 `CMAKE_TOOLCHAIN_FILE` 变量。 `CMAKE_TOOLCHAIN_FILE` 使 CMake 项目系统能够识别 vcpkg 提供的 C++ 库。 在本地使用 `CMakePresets.json` 时，只应将 `CMakeUserPresets.json` 签入源代码管理。



### 生成并运行该项目

1. 通过导航到>中的命令面板来运行 项目命令

![Visual Studio Code 中的 CMake 生成命令](.\imgs\vscode-command-build.png)

在 Visual Studio Code 中选择 CMake 生成命令的屏幕截图。



选择 `default` CMake 预设。 此操作将启用 vcpkg 工具链。

![在 Visual Studio Code 的 CMake 生成命令中选择预设](.\imgs\vscode-command-build-preset.png)

在 Visual Studio Code 的 CMake 生成命令中选择预设的屏幕截图。



1. 启动项目

运行该程序：

Bash复制

```bash
./build/HelloWorld.exe
```

你应会看到输出：

Console复制

```Console
Hello World!
```