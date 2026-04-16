set(HHH_NAME ui)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
    *.ui
    *.qrc
)

add_executable(${HHH_NAME} ${${HHH_NAME}_SOURCES} res.qrc)
add_common_includes(${HHH_NAME})
target_link_libraries(${HHH_NAME}
PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::StateMachine
    Qt6::Svg
)

# add_deployable_executable(${HHH_NAME})