cmake_minimum_required(VERSION 3.16)
project(ui LANGUAGES CXX)

add_executable(ui
    main.cpp
)

target_include_directories(ui PRIVATE
    ${PROJECT_SOURCE_DIR}/interfaces
)

target_link_directories(ui PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
)

find_package(Threads REQUIRED)

target_link_libraries(ui PRIVATE
    ipc_adapter
    Threads::Threads
)
