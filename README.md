# 🧩 IPC Adapter Project (C++ / nanomsg / Windows)

This project demonstrates an inter-process communication (IPC) system in C++ using [nanomsg](https://nanomsg.org) with a shared library (`libipc_adapter.dll`) to mediate communication between a **UI process** and a **Service process**.

---

## 📦 Project Structure
```text
NANOMSG_IPC/
├── ipc_adapter/ # IPC shared library (.dll)
│ ├── ipc_adapter.cpp # Adapter implementation
│ ├── ipc_client.cpp # nanomsg client logic
│ ├── ipc_client.hpp
│ ├── ipc_common.hpp # Shared types, enums
│ ├── ipc_interface.hpp # Abstract interfaces for callback
│ └── CMakeLists.txt
├── service/ # Backend process
│ ├── service_main.cpp # Contains logic and nanomsg server
│ └── CMakeLists.txt
├── ui/ # Frontend process
│ ├── main.cpp # Calls into libipc_adapter.dll
│ └── CMakeLists.txt
├── CMakeLists.txt # Top-level build configuration
└── README.md
```
---

## 🔧 Requirements

- **Windows 10/11**
- [MinGW-w64](https://www.mingw-w64.org/)
- [CMake ≥ 3.10](https://cmake.org/)
- `nanomsg` 1.2.1 (built as a shared `.dll`)

---

## 🔌 IPC Flow (Overview)
```text
UI Process ──[calls adapter]──► libipc_adapter.dll ──► nanomsg client
                                              │
                                              ▼
                                    nanomsg socket (PAIR)
                                              │
                                              ▼
                                  Service process (nanomsg server)
```
- ipc_interface.hpp declares the abstract callback interface
- ipc_client handles socket communication
- ipc_adapter links the UI and the IPC backend
