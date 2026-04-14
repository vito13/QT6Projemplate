set(HHH_NAME utils)

file(GLOB_RECURSE ${HHH_NAME}_SOURCES CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(${HHH_NAME} STATIC ${${HHH_NAME}_SOURCES})

target_link_libraries(${HHH_NAME} 
PRIVATE
    Qt6::Core
    Qt6::Widgets
)

# include path
target_include_directories(${HHH_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)