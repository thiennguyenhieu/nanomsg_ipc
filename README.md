# 🧩 IPC Adapter Project (C++ / nanomsg / Linux)

This project demonstrates an inter-process communication (IPC) system in **C++** using [nanomsg](https://nanomsg.org). A shared library (`libipc_adapter.so`) mediates communication between a **UI process** and a **Service process**.

---

## 📦 Project Structure

```text
NANOMSG_IPC/
├── ipc_adapter/            # IPC shared library (.so)
│   ├── ipc_adapter.cpp     # Adapter implementation
│   ├── ipc_client.cpp      # nanomsg client logic
│   ├── ipc_client.hpp
│   ├── ipc_common.hpp      # Shared constants/config/macros used in IPC
│   ├── ipc_interface.hpp   # Abstract interfaces for callback
│   ├── ipc_types.hpp       # Shared data structures and enums
│   └── CMakeLists.txt
├── service/                # Backend process
│   ├── service_main.cpp    # Contains logic and nanomsg server
│   └── CMakeLists.txt
├── ui/                     # Frontend process
│   ├── main.cpp            # Calls into libipc_adapter.so
│   ├── lib/                # Folder for .so libraries
│   └── CMakeLists.txt
├── nanomsg-1.2.1/          # Source for nanomsg (external dependency)
├── CMakeLists.txt          # Top-level build configuration
└── README.md
```

---

## 📎 Interface Consistency
⚠️ Important: The interfaces/ headers used by the UI must remain consistent with the corresponding internal headers used by the ipc_adapter library.
- Although the ipc_interface.hpp file is duplicated (one in ui/interfaces/, one in ipc_adapter/), both must declare the same callback types and function signatures.
- This ensures that the UI can safely call into the shared libipc_adapter.so and the function pointers resolve correctly at runtime.

---

## 🔌 IPC Architecture Overview

```text
     [ UI Process ]
           │
           │  calls functions in
           ▼
  ┌──────────────────────────────┐
  │      libipc_adapter.so       │  ◄── Shared library used by UI
  │  (wraps nanomsg socket APIs) │
  └──────────────────────────────┘
           │
           │  dynamically links to
           ▼
       [ libnanomsg.so ]
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

---

## 🧪 Build Instructions (Linux)
- Build the nanomsg library as a shared object (libnanomsg.so).
- Build the ipc_adapter shared library (libipc_adapter.so).
- Copy both libraries into the ui/lib/ directory.
- Ensure the UI executable links against these libraries at runtime.

---

## 💡 What is nanomsg?
nanomsg is a high-performance messaging library that provides several scalable communication patterns, including:
- REQ/REP (request-reply)
- PUB/SUB (publish-subscribe)
- BUS, PUSH/PULL, etc.
It simplifies inter-process or even inter-machine messaging by abstracting low-level socket management. It's well-suited for IPC scenarios in embedded, Linux, or distributed environments.

---

## ⚖️ Compared to Traditional IPC (e.g., raw sockets, pipes)

| Feature         | nanomsg                              | Raw Sockets / Pipes             |
|----------------|---------------------------------------|---------------------------------|
| Message Framing| ✅ Yes                                | ❌ Manual (bytes/length)        |
| Multi-pattern  | ✅ Built-in (REQ/REP, PUB/SUB, etc.)  | ❌ Needs custom logic           |
| Cross-platform | ✅ Yes                                | ⚠️ OS-dependent quirks          |
| Ease of Use    | ✅ High                               | ❌ Low-level and verbose        |
| Scalability    | ✅ Built-in patterns                  | ❌ Requires extra code          |

