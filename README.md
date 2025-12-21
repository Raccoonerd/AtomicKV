# AtomicKV

**AtomicKV** is a high-performance, multithreaded key-value storage written in modern C++ (C++20). It is designed to handle multiple concurrent client connections efficently using asynchronous I/O and thread-safe architecture.

## 🚀 Features
* **Asynchrounous I/O:** Built on **Boost.Asio** using the Procator pattern for non-blocking network operations.
* **Multithreading:** Utilizes a thread pool to distribute workload across all avialable CPU cores.
* **Thread-Safety:** Implements `std::shared_mutex` to allow multiple concurrent readers (GET) while ensuring exclusive access for writers (SET/REMOVE).
* **Zero-Copy Parsing:** Uses `std::string_view` to parse incoming commands without unnecesarry memory allocations.
* **Logging:** Integrated **Boost.Log** with rotation strategies and severity levels (Console & File output).
* **Memory Management:** wide use of smart pointers (`std::shared_ptr`, `std::enable_shared_from_this`) for automatic resource management.

## 🛠️ Tech Stack
* **Language:** C++20
* **Build System:** CMake (3.15+)
* **Libraries:**
    * Boost.Asio (Networking)
    * Boost.Log (Logging)
    * Boost.Thread (Threading support)

## 🏗️ Architecture

1. **Server:** Initializes the `io_context` and accepts incoming TCP connections (`acceptor`).
2. **Session:** Represents a single client connection. It handles reading, writing and parsing data asynchrounously. Uses `shared_from_this` to keep the connection alive during async operations.
3. **Parser:** A stateless component that converts raw byte streams into structured `Command` objects using `std::string_view`.
4. **KVStore:** The core. A thread-safe wrapper around `std::unordered_map`.

## 📦 Installation & Build

### Requirements
* C++ compiler supporting C++17/20 (GCC, Clang, MSVC)
* CMake 3.15 or newer
* Boost Libraries (system, thread, log, filesystem)

### Build Steps

```bash
# 1. Clone the repository
git clone https://github.com/Raccoonerd/AtomicKV.git
cd AtomicKV

# 2. Create a build directory
mkdir build && cd build

# 3. Configure and Build
# using ninja for faster building
cmake -G Ninja ..
ninja
```

## 💻 Usage

Start the server (it will automatically detect avialable CPU cores and spawn threads):
```bash
./AtomicKV
```
Connect using any TCP client (eg. `telnet` or `netcat`):
```bash
nc localhost 12345
```

### Supported Commands

1. **SET -> Store a value**
```
SET my_key My value

OK
```
2. **GET -> Read a value**
```
GET my_key

My value
```
3. **REMOVE -> Delete a key**
```
REMOVE my_key

REMOVED
```

## 📂 Project Structure

```
AtomicKV/
├── CMakeLists.txt
├── include/
│   ├── KVStore.hpp
│   ├── Logger.hpp
│   ├── Parser.hpp
│   ├── Server.hpp
│   └── Session.hpp
└── src/
    ├── KVStore.cpp
    ├── Logger.cpp
    ├── main.cpp
    ├── Parser.cpp
    ├── Server.cpp
    └── Session.cpp
```

## 🔮 Future Roadmap
* [ ] Rework structure
* [ ] Solid storage (Save/Load from file).
* [ ] Add configuration file for server.
* [ ] Add more commands (eg. GET_LIST)

## 📄 License
This project is open-source and avialable under the MIT License.
