add_library(
    broxflow STATIC
    broxflow.cpp
)

set(Broxflow_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(Broxflow_LIBRARIES broxflow PARENT_SCOPE)

install(TARGETS broxflow DESTINATION lib)

file(GLOB_RECURSE cheader *.h)
file(GLOB_RECURSE cppheader *.hpp)
set(headerfiles ${cheader} ${cppheader})

foreach(headerfile ${headerfiles})
    # CMAKE_CURRENT_SOURCE_DIRの部分を書き換え
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" headerfile ${headerfile})
    # ディレクトリパス取り出し
    get_filename_component(dir ${headerfile} DIRECTORY)
    # インストールパスに追加
    install(FILES ${headerfile} DESTINATION include/${dir})
endforeach()
