# 总流程

- C:\Qt\Examples\Qt-6.10.2\quick\shared

```
        ┌──────────────┐
        │ CMakeLists   │
        └──────┬───────┘
               ↓
        qt_add_qml_module
               ↓
        ┌──────────────┐
        │ shared.qrc   │ ← 真正打包资源
        └──────┬───────┘
               ↓
        ┌──────────────┐
        │ qmldir       │ ← 模块入口
        └──────┬───────┘
               ↓
        import shared

.qmlls.ini  ← 只给 IDE 用
quick_shared.qrc ← 旧方式备用
--------------------------------


1️⃣ CMakeLists.txt
    ↓
2️⃣ qt_add_qml_module
    ↓
3️⃣ 生成 QML module（含 qmldir）
    ↓
4️⃣ 打包 QML + 图片进资源
    ↓
5️⃣ 程序运行
    ↓
6️⃣ QML import shared
    ↓
7️⃣ Qt 加载模块
```



# qmldir

- 运行时使用
- QML模块的“类型注册表”，定义叫什么，依赖、有哪些组件。导入模块必须有此文件
- 可由cmakelist里的“qt_add_qml_module(...)”自动生成，也可手动编写
- 可以指定具体导入版本，如import shared 2.1

```
module shared  // 模块定义，此处没有URI，是本地模块
Button 2.0 Button.qml  // 注册组件（QML类型名随便写、版本、文件）
CheckBox 2.1 CheckBox.qml // 
Label 2.0 Label.qml
LauncherList 2.0 LauncherList.qml
SimpleLauncherDelegate 2.0 SimpleLauncherDelegate.qml
Slider 2.0 Slider.qml
TabSet 2.1 TabSet.qml
TextField 2.1 TextField.qml
singleton Images 2.2 Images.qml // 全局单例对象
```

# CMakeLists.txt

- 编译时使用
- qt_add_qml_module的编译目标是QML的模块、（动态库 or 静态库）
- 注册为 QML 类型、自动生成 qmldir
- 版本号不会自动推断
- RESOURCES部分用 CMake 直接替代 QRC（实验失败，还是使用qrc安全）

```
# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

set_source_files_properties(Images.qml // 等价于生成 singleton Images 2.2 Images.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE true
)

qt_add_qml_module(${PROJECT_NAME}_shared // 依赖于“PROJECT_NAME”的定义，会连在一起成为最终的名字
    URI shared // 相当于import shared，类似qmldir的module shared的作用
    PLUGIN_TARGET ${PROJECT_NAME}_shared // 指定 QML 插件名字
    SOURCES // C++ 文件
        "shared.h"
    QML_FILES   // qml的文件注册
        "Button.qml"
        "CheckBox.qml"
        "Label.qml"
        "LauncherList.qml"
        "SimpleLauncherDelegate.qml"
        "Slider.qml"
        "TabSet.qml"
        "TextField.qml"
        "Images.qml"
    RESOURCES // 资源系统，编译进 Qt Resource System（QRC）
        "images/back.png"
        "images/checkmark.png"
        "images/next.png"
        "images/qt-logo.png"
        "images/slider_handle.png"
        "images/tab.png"
)
```

# shared.qrc

现代方式的QML模块资源打包，包括

- QML文件
- 图片
- qmldir

```
<RCC>
    <qresource prefix="/qt/qml/shared"> 
    // 上面这句是QML模块标准路径QML模块必须在 /qt/qml/<URI> 下，
    // CMake里定义的那句“URI shared”，指的是同一个地方。
    // 代码里"import shared"时候，会自动寻找“:/qt/qml/shared/qmldir”
        <file>Button.qml</file>
        <file>CheckBox.qml</file>
        <file>Images.qml</file>
        <file>Label.qml</file>
        <file>LauncherList.qml</file>
        <file>SimpleLauncherDelegate.qml</file>
        <file>Slider.qml</file>
        <file>TabSet.qml</file>
        <file>TextField.qml</file>
        <file>images/back.png</file>
        <file>images/checkmark.png</file>
        <file>images/next.png</file>
        <file>images/qt-logo.png</file>
        <file>images/slider_handle.png</file>
        <file>images/tab.png</file>
        <file>qmldir</file>
    </qresource>
</RCC>


```

# quick_shared.qrc

兼容目的的历史遗留方式，现代 Qt6 建议shared.qrc方式

# .qmlls.ini

给 QML Language Server（qmlls） 用的，只影响自动补全、报错提示、跳转定义，不影响程序运行

```
[General]
buildDir="C:/Qt/Examples/Qt-6.10.2/quick/multieffect/testbed/build" // 找到编译后的 QML模块
no-cmake-calls=false // 不允许 qmlls 调用 CMake
docDir=C:/Qt/Docs/Qt-6.10.2 // Qt 文档路径，鼠标悬停显示文档，自动补全说明
importPaths="C:/Qt/6.10.2/msvc2022_64/qml" // QML模块搜索路径
```

# Launcher

系统的“运行逻辑”，应用内页面导航系统（mini 框架）

## LauncherList.qml

## SimpleLauncherDelegate.qml

- 列表项

```

```


# 组件库


# 资源系统
