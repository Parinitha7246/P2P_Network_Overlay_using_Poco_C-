# 🧠 P2P Overlay Design Notes

## 📌 Project Overview

This document explains the design architecture and flow of the **P2P Network Overlay** built using **C++ and Poco Libraries**.

---

## ⚙️ Architecture Components

### 1. **Node (Core Unit)**  
Each node in the overlay can act as both:
- A **client** (initiating connection to another node)
- A **server** (listening for new peer connections)

It supports:
- Secure authentication via token
- Structured communication
- Peer lifecycle management (join, message, exit)

---

## 🧱 Core Files

| File                | Description                                  |
|---------------------|----------------------------------------------|
| `Node.hpp`          | Declares the Node class with peer management |
| `Node.cpp`          | Implements networking logic using Poco       |
| `main_server.cpp`   | Entry point for running in server mode       |
| `main_client.cpp`   | Entry point for running in client mode       |

---

## 🧵 Communication Protocol

All communication follows a **tagged text protocol**:

| Tag   | Purpose                         |
|-------|----------------------------------|
| `AUTH:<token>` | Authentication (first step) |
| `JOIN:<name>`  | Identify the peer after auth |
| `MSG:<text>`   | Message sent to server       |
| `EXIT:<name>`  | Clean disconnection          |

Example:
```
AUTH:letmein123
JOIN:alice
MSG:hello
EXIT:alice
```

---

## 🔐 Security

- Each connecting node must send a correct token (`letmein123`) before any communication.
- Invalid or missing tokens result in immediate disconnection.

---

## 🔁 Retry Logic

- Clients try to connect to the server up to **5 times** with a **1-second delay** between attempts if the connection fails.
- This increases resilience in case the server is not up.

---

## 🔄 Peer Management

- When a peer connects successfully, it is **added to the peer list**.
- When a peer disconnects, it is **safely removed**.
- A `std::mutex` lock is used to ensure **thread-safe access** to the peer list.

---

## 📦 Node Behavior Flow

### ✅ Server (Listening Mode)
1. Listens on port `9000`
2. Accepts incoming connections
3. Authenticates the peer
4. Handles JOIN, MSG, EXIT
5. Removes peer on disconnect

### ✅ Client (Connecting Mode)
1. Connects to server IP and port
2. Sends token and JOIN name
3. Sends messages in loop
4. Exits on command

---

## 🧪 Tested Scenarios

| Test Scenario                       | Status |
|------------------------------------|--------|
| Single peer connection             | ✅     |
| Message exchange after auth        | ✅     |
| Invalid token handling             | ✅     |
| Retry on connection failure        | ✅     |
| Peer disconnection cleanup         | ✅     |
| Multiple clients sequentially      | ✅     |

---

## 🚀 Future Improvements

- Add multithreaded support for **handling multiple clients in parallel**
- Use JSON-based structured messages for extensibility
- Implement P2P messaging without centralized server
- Add UI client (maybe using React or Qt)
- Encrypt communication using TLS/SSL

---

## 🏁 Conclusion

This project serves as a foundational implementation of a **basic P2P network overlay** using modern C++ and Poco libraries. It introduces authentication, message exchange, and robust peer tracking — and lays the groundwork for future enhancements such as concurrent