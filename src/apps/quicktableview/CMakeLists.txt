set(HHH_NAME quicktableview)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.ui
    *.qrc
)

qt_add_executable(${HHH_NAME} MANUAL_FINALIZATION ${${HHH_NAME}_SOURCES} ${CMAKE_SOURCE_DIR}/res/res.qrc)
add_common_includes(${HHH_NAME})
target_link_libraries(${HHH_NAME}
PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QuickLayouts
    Mydll
    utils
)

# add_deployable_executable(${HHH_NAME})

set_target_properties(${HHH_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(${HHH_NAME})
