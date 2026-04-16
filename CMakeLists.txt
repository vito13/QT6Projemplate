cmake_minimum_required(VERSION 3.21)

project(MyQtProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C://Qt//6.10.2//msvc2022_64//lib//cmake//Qt6")

# 运行程序、动态库、静态库都放在 bin 目录下，区分 debug/release
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR}/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR}/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR}/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR}/release)



# Qt自动处理 moc / ui / rcc
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找 Qt
find_package(Qt6 COMPONENTS
    Core
    Widgets
    Sql
    Network
    StateMachine
    Svg
    Quick
    QuickWidgets
    QuickControls2
    QuickLayouts
    REQUIRED
)

if(WIN32)
    # 自动部署 Qt 可执行程序和 QML 插件
    function(add_deployable_executable target_name)
        # 确保是 exe 类型
        get_target_property(TGT_TYPE ${target_name} TYPE)
        if(TGT_TYPE STREQUAL "EXECUTABLE")

            # 推测 Qt bin 目录（windeployqt.exe 所在目录）
            get_filename_component(QtBinDir "${CMAKE_PREFIX_PATH}/../../../bin" ABSOLUTE)
            set(WINDEPLOYQT "${QtBinDir}/windeployqt.exe")

            # 检查是否存在 windeployqt.exe
            if(NOT EXISTS "${WINDEPLOYQT}")
                message(FATAL_ERROR "windeployqt.exe not found at ${WINDEPLOYQT}")
            endif()

            # QML 源目录（你自己的 QML 文件目录）
            set(QML_DIR "${CMAKE_SOURCE_DIR}/res/qmls")

            # 添加 POST_BUILD 命令，自动部署 DLL + QML 插件
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND "${WINDEPLOYQT}" "$<TARGET_FILE:${target_name}>"
                        --qmldir "${QML_DIR}"
                        --force
                        --no-compiler-runtime
                        --verbose 1
                COMMENT "Deploying Qt DLLs and QML plugins for ${target_name}"
            )
        endif()
    endfunction()
endif()

# 在 configure 阶段复制 compile_commands.json 到源代码目录，方便 clangd 等工具使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS ${CMAKE_BINARY_DIR}/compile_commands.json)
    file(COPY ${CMAKE_BINARY_DIR}/compile_commands.json
         DESTINATION ${CMAKE_SOURCE_DIR})
endif()

# 添加子工程
add_subdirectory(src)
