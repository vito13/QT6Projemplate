# QT6Projemplate
QT6Projemplate

# 非msvc启动方式

- 开启 x64 Native Tools Command Prompt for VS 2022
- 执行 code，开启vscode即可编译

# 注意事项
 - 可以使用vs2022（带有qt扩展）开启cmakelist方式作为ide
 - 可以使用vscode（带有cmake与qt扩展，见下面）开启目录方式作为ide，使用vs的终端启动code避免找不到vs的编译器（启用vs的环境变量）
 - 需要将"C:\Qt\6.10.2\msvc2022_64\bin"加入PATH（管理员：setx PATH "C:\Qt\6.10.2\msvc2022_64\bin;%PATH%" /M）

# 非msvc开发工具链

vscode+clang+mingw+cmake+qt
https://blog.csdn.net/qq_73648789/article/details/154692278?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogOpenSearchComplete%7ERate-3-154692278-blog-158670939.235%5Ev43%5Epc_blog_bottom_relevance_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogOpenSearchComplete%7ERate-3-154692278-blog-158670939.235%5Ev43%5Epc_blog_bottom_relevance_base1&utm_relevant_index=3

## 安装
 - 添加vscode插件
   - C/C++ Extension Pack
   - clangd
   - CMake Tools
   - CodeLLDB
   - QML
   - QML Format
 - 安装包
   - LLVM https://github.com/llvm/llvm-project/releases/download/llvmorg-22.1.1/LLVM-22.1.1-win64.exe 
   - mingw64 https://github.com/niXman/mingw-builds-binaries/releases/download/15.2.0-rt_v13-rev0/x86_64-15.2.0-release-mcf-seh-ucrt-rt_v13-rev0.7z
   - cmake

## 配置

- 添加"%LocalAppData%\clangd\config.yaml"
```
# 参考：https://clangd.llvm.org/config
# 补全配置：参数列表显示分隔符
Completion:
  ArgumentLists: Delimiters
 
# 嵌入式提示：显示代码块结束、默认参数等
InlayHints:
  BlockEnd: true        # 显示代码块结束标记（如 `}` 旁标注函数名）
  DefaultArguments: true # 显示函数默认参数提示
  TypeNameLimit: 0      # 类型名提示无长度限制
 
# 悬停提示：显示别名（AKA）信息
Hover:
  ShowAKA: true
 
# 全局编译选项（所有项目生效）
CompileFlags:
  Add: [-Wall]  # 添加 `-Wall` 开启所有警告
```
- 在项目根目录添加".clangd"

```
CompileFlags: {
    
}
```
- 在VSCode中配置Clangd:Path到 "C:\\Program Files\\LLVM\\bin"
- 添加.vscode\settings.json
```
{
    "clangd.arguments": [
        // 后台索引（提升大型项目的响应速度）
        "--background-index",
        "--background-index-priority=low",  // 后台索引优先级设为低，不影响编辑
        
        // 启用代码检查（基于clang-tidy，支持代码规范检查）
        "--clang-tidy",
        
        // 补全样式：detailed显示更详细的补全信息（如参数类型）
        "--completion-style=detailed",
        
        // 代码风格 fallback：当项目无明确风格时，默认使用Google风格
        "--fallback-style=Google",
        
        // 关闭函数参数占位符（避免补全时自动插入`${1}`等占位符）
        "--function-arg-placeholders=false",
        
        // 禁止自动插入#include（如需手动控制头文件引入）
        "--header-insertion=never",
        
        // 重命名文件时无数量限制（默认可能限制大项目重命名）
        "--rename-file-limit=0",
        
        // 启用Clangd的配置文件（即前面提到的user/project级config.yaml）
        "--enable-config",
        
        // 并行任务数量（根据CPU核心数调整，如8核设为8，加速索引）
        "-j=18",
        
        // PCH（预编译头）存储在内存中，提升解析速度
        "--pch-storage=memory",
        
        // 格式化输出日志（方便调试）
        "--pretty",
        
        // 【核心】指定compile_commands.json的路径（必须修改！）
        // 该文件由CMake、Make等构建工具生成，包含项目编译信息（如头文件路径、宏定义）
        // 解释：基于cmake构建管理项目时，使用该命令（--compile-commands-dir=）产生的compile_commands.json会放到指定文件夹下同时该文件帮助你找到头文件信息索引
        // 格式：--compile-commands-dir=项目中compile_commands.json所在的文件夹路径
        // "--compile-commands-dir=${workspaceFolder}/out",  // 示例：项目根目录下的build文件夹，在根目录无需指定路径
        
        // 【核心】指定编译器路径（解决标准库头文件找不到的问题）
        // 通配符匹配编译器路径（如ARM交叉编译器、x86编译器）
        // 格式：--query-driver=编译器可执行文件的路径（支持*通配符）
        "--query-driver=C:/x86_64-15.2.0-release-mcf-seh-ucrt-rt_v13-rev0/mingw64/bin/*"
    ],
    "clangd.path": "C:\\Program Files\\LLVM\\bin\\clangd.exe"
}
```

- 添加到cmakelist
```
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS ${CMAKE_BINARY_DIR}/compile_commands.json)
    file(COPY ${CMAKE_BINARY_DIR}/compile_commands.json
         DESTINATION ${CMAKE_SOURCE_DIR})
endif()
```

- 添加.vscode\launch.json用于调试

```
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug demo",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bin/debug/demo.exe",
            "args": [],
            "cwd": "${workspaceFolder}",
            "stopAtEntry": false,
            "environment": [],
            "console": "externalTerminal",
            "MIMode": "gdb",
            "miDebuggerPath": "C:/x86_64-15.2.0-release-mcf-seh-ucrt-rt_v13-rev0/mingw64/bin/gdb.exe"
        }

    ]
}
```