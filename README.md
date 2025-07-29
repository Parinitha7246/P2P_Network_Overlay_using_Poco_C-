

**Name:** Parinitha B  
**Task Number:** 5 (C++)

**University:** [Sahyadri College of Engineering and Management]  

---

# 🔗 P2P Network Overlay using Poco C++

## 📌 Project Summary

This project implements a **Peer-to-Peer (P2P) Network Overlay** in C++ using the **Poco C++ Libraries**. It enables nodes to connect, authenticate, exchange structured messages, and dynamically join or leave the overlay network, maintaining integrity and robustness.

---

## ⚙️ Tech Stack

- **Language:** C++
- **Libraries:** Poco C++ Libraries
- **Build System:** CMake
- **Platform:** Windows 10 (tested with MSVC + vcpkg)

---

## 🧠 Features

- ✅ Dynamic node discovery and registration  
- ✅ Authentication with token validation  
- ✅ Structured messaging protocol (JOIN, MSG, EXIT)  
- ✅ Peer tracking and retry logic  
- ✅ Clean removal of disconnected peers  

---

## 📁 Project Structure

```
p2p-overlay/
├── include/
│   └── Node.hpp             # Node class interface
├── src/
│   ├── Node.cpp             # Node class implementation
│   ├── main_server.cpp      # Entry point for server
│   └── main_client.cpp      # Entry point for client
├── CMakeLists.txt
├── build/                   # CMake build output
├── README.md                # Project documentation
└── docs/
    └── design_notes.md      # Architectural overview
```

---

## 🛠️ Installation Instructions

### 🔗 1. Prerequisites

- Visual Studio with C++ Development Tools  
- [vcpkg](https://github.com/microsoft/vcpkg) (for installing Poco)  
- Git (optional)

---

### 📦 2. Install Poco C++ via vcpkg

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install poco
```

This installs all required Poco networking libraries.

---

### 🛠️ 3. Build the Project

```bash
git clone <your-repo>
cd p2p-overlay
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release
```

✅ Replace `"C:/path/to/vcpkg"` with the actual path where you cloned vcpkg.

---

## ▶️ How to Run

### 🖥️ Start the Server

```bash
.\Release\p2p_server.exe
```

* The server starts and listens on **port 9000** for peer connections.

---

### 💻 Start a Client (in a new terminal)

```bash
.\Release\p2p_client.exe
```

You will be prompted to:

* Enter your **name**
* Type messages in a loop
* Exit by typing `exit`

---

## 💬 Message Protocol Format

All messages follow a clear, structured format:

| Type    | Format          | Description                       |
| ------- | --------------- | --------------------------------- |
| Auth    | `AUTH:<token>`  | Authenticate peer to join         |
| Join    | `JOIN:<name>`   | Notify server of joining          |
| Message | `MSG:<message>` | Normal message sent to server     |
| Exit    | `EXIT:<name>`   | Notify disconnection from network |

---

## 🔐 Security & Error Handling

* ✅ Only peers with the correct token (`letmein123`) are authorized
* ✅ Server verifies authentication before accepting communication
* ✅ Retry logic: clients retry 5 times if connection fails
* ✅ Graceful exit using `EXIT:` message
* ✅ Mutex locks for thread-safe peer management

---

## 🧪 Testing Scenarios

| Test Case                             | Status  |
| ------------------------------------- | ------  |
| Single client join and leave          | ✅ Done |
| Multiple clients connect sequentially | ✅ Done |
| Invalid token access denied           | ✅ Done |
| Structured message exchange           | ✅ Done |
| Peer disconnects handled              | ✅ Done |
| Retry logic on network failure        | ✅ Done |

---

## 📚 Sample Output

### ✅ Server Console

```
Listening for peers on port 9000...
✅ Authorized peer: 127.0.0.1:53020
[+] Peer added: 127.0.0.1:53020
[JOIN] alice (127.0.0.1:53020) joined the network.
[127.0.0.1:53020] hi
[127.0.0.1:53020] hello
[EXIT] alice (127.0.0.1:53020) left the network.
[-] Peer removed: 127.0.0.1:53020
```

### ✅ Client Console

```
✅ Connected to 127.0.0.1:9000 on attempt 1
Enter your name: alice
Enter message (or type 'exit'): hi
Enter message (or type 'exit'): hello
Enter message (or type 'exit'): exit
Disconnected from server.
```

---

## ✨ Future Scope

* 🔄 Add **threaded message handling** for concurrent peer connections
* 📡 Enable **broadcast messaging** to all peers
* 🔐 Implement **TLS encryption** for secure communication
* 🔗 Enable **client-to-client direct messaging**
* 📁 Use **JSON or XML** for structured data exchange

---

## ✅ Submission Details

* **File Name:** `ParinithaB_Sahyadri College Of Engineering and Management_C++_Task 5`
* Includes: Code, README, `docs/` and `build/` directory
---

