cmake_minimum_required(VERSION 3.16)
project(ui LANGUAGES CXX)

add_executable(ui
    main.cpp
)

target_include_directories(ui PRIVATE
    ${CMAKE_SOURCE_DIR}/ipc_adapter
)

find_package(Threads REQUIRED)

target_link_libraries(ui PRIVATE
    ${CMAKE_SOURCE_DIR}/ui/lib
    ipc_adapter
    Threads::Threads
)
