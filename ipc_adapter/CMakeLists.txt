cmake_minimum_required(VERSION 3.16)
project(ipc_adapter LANGUAGES CXX)

# Create shared library
add_library(ipc_adapter SHARED
    ipc_client.cpp
    ipc_adapter.cpp
    ipc_client.hpp
    ipc_common.hpp
    interfaces/ipc_interface.hpp
    interfaces/ipc_types.hpp
)

# Expose headers to both this target and dependents
target_include_directories(ipc_adapter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/nanomsg-1.2.1/src
)

# Link to nanomsg (assumes it's added as a subdirectory or globally installed)
target_link_libraries(ipc_adapter PRIVATE nanomsg)

# Optional: Export .so with clean name and position-independent code
set_target_properties(ipc_adapter PROPERTIES
    OUTPUT_NAME "ipc_adapter"
    POSITION_INDEPENDENT_CODE ON
)
