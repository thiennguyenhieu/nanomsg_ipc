cmake_minimum_required(VERSION 3.16)
project(NanoIpcExample)

add_subdirectory(nanomsg-1.2.1)
add_subdirectory(ipc_adapter)
add_subdirectory(service)
add_subdirectory(ui)
