cmake_minimum_required(VERSION 3.16)
project(ipc_adapter)

add_library(ipc_adapter SHARED
    ipc_client.cpp
    ipc_adapter.cpp
)

target_include_directories(ipc_adapter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Windows: link to nanomsg (assuming installed or in vcpkg)
find_library(NANOMSG_LIB nanomsg REQUIRED)
target_link_libraries(ipc_adapter PRIVATE ${NANOMSG_LIB})

# Optional export flags
set_target_properties(ipc_adapter PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    OUTPUT_NAME "ipc_adapter"
)
