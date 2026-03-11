set(HHH_NAME demo)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.ui
    *.qrc
)

add_executable(${HHH_NAME} ${${HHH_NAME}_SOURCES} ${CMAKE_SOURCE_DIR}/res/res.qrc)

target_link_libraries(${HHH_NAME}
PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QuickLayouts
    Mydll
)

add_deployable_executable(${HHH_NAME})