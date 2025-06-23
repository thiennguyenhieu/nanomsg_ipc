cmake_minimum_required(VERSION 3.16)
project(service)

add_executable(service
    service_main.cpp
)

target_include_directories(service PRIVATE
    ${PROJECT_SOURCE_DIR}/ipc_adapter
)

find_library(NANOMSG_LIB nanomsg REQUIRED)
target_link_libraries(service PRIVATE ${NANOMSG_LIB})
