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
 UI Process (Subscriber)
         ▲
         │
  libipc_adapter.dll (nanomsg SUB socket)
         ▲
         │
 nanomsg IPC socket (PUB/SUB)
         │
         ▼
Service Process (Publisher)

```
- Service uses NN_PUB to broadcast status updates.
- UI uses NN_SUB to subscribe and react to those updates.
- The IPC adapter encapsulates all SUB socket logic and exposes a clean C++ interface.
