set(HHH_NAME Mydll)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.ui
    *.qrc
)

add_library(${HHH_NAME} SHARED ${${HHH_NAME}_SOURCES} ${CMAKE_SOURCE_DIR}/res/res.qrc)

target_link_libraries(${HHH_NAME} 
PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# 头文件搜索路径
target_include_directories(${HHH_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# DLL导出宏，编译库时生效
target_compile_definitions(${HHH_NAME} PRIVATE MYDLL_BUILD)

add_deployable_executable(${HHH_NAME})