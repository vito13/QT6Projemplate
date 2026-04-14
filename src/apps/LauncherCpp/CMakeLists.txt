set(HHH_NAME LauncherCpp)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.ui
    *.qrc
)


qt_add_executable(${HHH_NAME}
    WIN32
    ${${HHH_NAME}_SOURCES}
    ${CMAKE_SOURCE_DIR}/res/res.qrc
)


add_common_includes(${HHH_NAME})
target_link_libraries(${HHH_NAME}
PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickWidgets
    Qt6::QuickControls2
    Qt6::QuickLayouts
    Mydll
    utils
)
