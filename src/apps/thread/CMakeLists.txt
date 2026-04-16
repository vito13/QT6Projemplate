set(HHH_NAME thread)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.ui
    *.qrc
)

add_executable(${HHH_NAME} ${${HHH_NAME}_SOURCES} ${CMAKE_SOURCE_DIR}/res/res.qrc)
add_common_includes(${HHH_NAME})
target_link_libraries(${HHH_NAME}
PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# add_deployable_executable(${HHH_NAME})