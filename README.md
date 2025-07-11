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
│ ├── ipc_common.hpp # Shared constants/config/macros used in IPC
│ ├── ipc_interface.hpp # Abstract interfaces for callback
│ ├── ipc_types.hpp # Shared data structures and enums
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
     [ UI Process ]
           │
           │  calls functions in
           ▼
  ┌──────────────────────────────┐
  │      libipc_adapter.dll      │  ◄── Shared library used by UI
  │  (wraps nanomsg socket APIs) │
  └──────────────────────────────┘
           │
           │  dynamically links to
           ▼
       [ nanomsg.dll ]
           │
           │  handles socket transport (REQ/SUB)
           ▼
  ┌────────────────────────────────────┐
  │         IPC Transport Layer        │
  │     NN_REQ  ─────────▶  NN_REP     │  ► Request/Reply (UI → Service)
  │     NN_SUB  ◀────────  NN_PUB      │  ◄ Publish/Subscribe (Service → UI)
  └────────────────────────────────────┘
           │
           │  communicates over IPC sockets
           ▼
     [ Service Process ]
  ┌──────────────────────────────┐
  │   Listens via nanomsg REQ &  │
  │     publishes via PUB socket │
  └──────────────────────────────┘

```
- libipc_adapter.dll wraps nanomsg API calls for the UI to consume easily.
- nanomsg.dll is the runtime dependency that actually implements socket transport.
- The "IPC Transport Layer" is where actual nanomsg sockets (REQ/REP, PUB/SUB) communicate via shared IPC endpoints.
- Service Process uses NN_REP to respond and NN_PUB to notify.
