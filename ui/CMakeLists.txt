cmake_minimum_required(VERSION 3.16)
project(ui)

add_executable(ui
    main.cpp
)

target_include_directories(ui PRIVATE
    ${PROJECT_SOURCE_DIR}/ipc_adapter
)

target_link_libraries(ui PRIVATE
    ipc_adapter
)
