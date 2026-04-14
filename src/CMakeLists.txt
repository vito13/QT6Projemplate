function(add_common_includes target_name)
    target_include_directories(${target_name}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src/utils
    )
endfunction()

add_subdirectory(utils)
add_subdirectory(modules/mydll)
add_subdirectory(apps/demo)
add_subdirectory(apps/quicktableview)
add_subdirectory(apps/listview)
add_subdirectory(apps/modelview)
add_subdirectory(apps/launchercpp)
add_subdirectory(apps/ui)
