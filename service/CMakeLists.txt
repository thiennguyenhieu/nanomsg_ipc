cmake_minimum_required(VERSION 3.16)
project(service LANGUAGES CXX)

add_executable(service
    service_main.cpp
)

# Include headers from ipc_adapter and nanomsg
target_include_directories(service PRIVATE
    ${CMAKE_SOURCE_DIR}/ipc_adapter
    ${CMAKE_SOURCE_DIR}/nanomsg-1.2.1/src
)

# Link with nanomsg static/shared library
target_link_libraries(service PRIVATE nanomsg)

# Optional: Set C++ standard if needed
target_compile_features(service PRIVATE cxx_std_17)
