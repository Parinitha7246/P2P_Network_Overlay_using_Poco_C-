// // // #include "Node.hpp"
// // // #include <Poco/Net/SocketAddress.h>
// // // #include <Poco/Net/StreamSocket.h>
// // // #include <iostream>

// // // using namespace Poco::Net;

// // // Node::Node(const std::string& host, int port)
// // //     : _host(host), _port(port), _socket() {}

// // // void Node::start() {
// // //     try {
// // //         SocketAddress addr(_host, _port);
// // //         _socket.connect(addr);
// // //         std::cout << "Connected to " << _host << ":" << _port << std::endl;
// // //     } catch (const Poco::Exception& ex) {
// // //         std::cerr << "Connection failed: " << ex.displayText() << std::endl;
// // //     }
// // // }

// // //-------------------------------DAY 1------------------------------------------------
// // #include "Node.hpp"
// // #include <Poco/Net/SocketAddress.h>
// // #include <Poco/Net/StreamSocket.h>
// // #include <Poco/Net/ServerSocket.h>
// // #include <Poco/Net/SocketStream.h>
// // #include <iostream>

// // using namespace Poco::Net;

// // Node::Node(const std::string& host, int port)
// //     : _host(host), _port(port) {}

// // void Node::start() {
// //     try {
// //         SocketAddress addr(_host, _port);
// //         StreamSocket socket;
// //         socket.connect(addr);
// //         std::cout << "Connected to " << _host << ":" << _port << std::endl;

// //         SocketStream stream(socket);
// //         stream << "Hello from peer!" << std::endl;

// //     } catch (const Poco::Exception& ex) {
// //         std::cerr << "Connection failed: " << ex.displayText() << std::endl;
// //     }
// // }

// // void Node::listen() {
// //     try {
// //         ServerSocket server(_port);
// //         std::cout << "Listening for peers on port " << _port << "..." << std::endl;

// //         while (true) {
// //             StreamSocket peer = server.acceptConnection();
// //             SocketAddress addr = peer.peerAddress();
// //             std::cout << "Peer connected: " << addr.toString() << std::endl;

// //             // Optional: read message from peer
// //             Poco::Net::SocketStream stream(peer);
// //             std::string msg;
// //             std::getline(stream, msg);
// //             std::cout << "Message from peer: " << msg << std::endl;
// //         }

// //     } catch (const Poco::Exception& ex) {
// //         std::cerr << "Server failed: " << ex.displayText() << std::endl;
// //     }
// // }

// //----------------------------------------------DAY 2----------------------------------

// #include "Node.hpp"
// #include <Poco/Net/SocketAddress.h>
// #include <Poco/Net/StreamSocket.h>
// #include <Poco/Net/ServerSocket.h>
// #include <Poco/Net/SocketStream.h>
// #include <iostream>
// #include <algorithm>

// using namespace Poco::Net;

// Node::Node(const std::string& host, int port)
//     : _host(host), _port(port) {}

// void Node::start() {
//     try {
//         SocketAddress addr(_host, _port);
//         StreamSocket socket;
//         socket.connect(addr);
//         std::cout << "Connected to " << _host << ":" << _port << std::endl;

//         SocketStream stream(socket);
//         stream << "Hello from peer!" << std::endl;

//     } catch (const Poco::Exception& ex) {
//         std::cerr << "Connection failed: " << ex.displayText() << std::endl;
//     }
// }

// void Node::addPeer(const std::string& address) {
//     std::lock_guard<std::mutex> lock(_mutex);
//     _peerList.push_back(address);
//     std::cout << "[+] Peer added: " << address << "\n";
//     std::cout << "    Current peers: " << _peerList.size() << "\n";
// }

// void Node::removePeer(const std::string& address) {
//     std::lock_guard<std::mutex> lock(_mutex);
//     _peerList.erase(std::remove(_peerList.begin(), _peerList.end(), address), _peerList.end());
//     std::cout << "[-] Peer removed: " << address << "\n";
//     std::cout << "    Current peers: " << _peerList.size() << "\n";
// }

// void Node::listen() {
//     try {
//         ServerSocket server(_port);
//         std::cout << "Listening for peers on port " << _port << "..." << std::endl;

//         while (true) {
//             StreamSocket peer = server.acceptConnection();
//             SocketAddress addr = peer.peerAddress();
//             std::string peerAddrStr = addr.toString();

//             std::cout << "Peer connected: " << peerAddrStr << std::endl;
//             addPeer(peerAddrStr);

//             SocketStream stream(peer);
//             std::string msg;
//             std::getline(stream, msg);
//             std::cout << "Message from peer: " << msg << std::endl;

//             peer.close();
//             removePeer(peerAddrStr);
//         }

//     } catch (const Poco::Exception& ex) {
//         std::cerr << "Server failed: " << ex.displayText() << std::endl;
//     }
// }

// -------------------------------------------------------DAY 3----------------------------------------------

#include "Node.hpp"
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketStream.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace Poco::Net;

const std::string AUTH_TOKEN = "letmein123";

Node::Node(const std::string& host, int port)
    : _host(host), _port(port) {}

void Node::start() {
    const int maxRetries = 5;
    int attempt = 0;

    while (attempt < maxRetries) {
        try {
            SocketAddress addr(_host, _port);
            StreamSocket socket;
            socket.connect(addr);
            std::cout << "✅ Connected to " << _host << ":" << _port << " on attempt " << (attempt + 1) << "\n";

            SocketStream stream(socket);

            // 🔐 Send authentication token
            stream << "AUTH:" << AUTH_TOKEN << std::endl;

            // 🟡 JOIN command
            std::cout << "Enter your name: ";
            std::string name;
            std::getline(std::cin, name);
            stream << "JOIN:" << name << std::endl;

            std::string message;
            while (true) {
                std::cout << "Enter message (or type 'exit'): ";
                std::getline(std::cin, message);

                if (message == "exit") {
                    stream << "EXIT:" << name << std::endl;
                    break;
                }

                stream << "MSG:" << message << std::endl;
            }

            std::cout << "Disconnected from server.\n";
            break;

        } catch (const Poco::Exception& ex) {
            attempt++;
            std::cerr << "Connection failed (attempt " << attempt << "): " << ex.displayText() << std::endl;

            if (attempt < maxRetries) {
                std::cout << "Retrying in 1 second...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                std::cerr << "All connection attempts failed. Exiting.\n";
            }
        }
    }
}

void Node::addPeer(const std::string& address) {
    std::lock_guard<std::mutex> lock(_mutex);
    _peerList.push_back(address);
    std::cout << "[+] Peer added: " << address << "\n";
    std::cout << "    Current peers: " << _peerList.size() << "\n";
}

void Node::removePeer(const std::string& address) {
    std::lock_guard<std::mutex> lock(_mutex);
    _peerList.erase(std::remove(_peerList.begin(), _peerList.end(), address), _peerList.end());
    std::cout << "[-] Peer removed: " << address << "\n";
    std::cout << "    Current peers: " << _peerList.size() << "\n";
}

void Node::listen() {
    try {
        ServerSocket server(_port);
        std::cout << "Listening for peers on port " << _port << "..." << std::endl;

        while (true) {
            StreamSocket peer = server.acceptConnection();
            SocketAddress addr = peer.peerAddress();
            std::string peerAddrStr = addr.toString();

            SocketStream stream(peer);

            // 🔐 Expect auth token first
            std::string authMsg;
            std::getline(stream, authMsg);

            if (authMsg.rfind("AUTH:", 0) != 0) {
                std::cout << "❌ Invalid format from " << peerAddrStr << ". Connection closed.\n";
                peer.close();
                continue;
            }

            std::string token = authMsg.substr(5);
            if (token != AUTH_TOKEN) {
                std::cout << "❌ Unauthorized peer " << peerAddrStr << ". Token: " << token << "\n";
                peer.close();
                continue;
            }

            std::cout << "✅ Authorized peer: " << peerAddrStr << std::endl;
            addPeer(peerAddrStr);

            std::string msg;
            while (std::getline(stream, msg)) {
                if (msg.empty()) continue;

                if (msg.rfind("JOIN:", 0) == 0) {
                    std::string name = msg.substr(5);
                    std::cout << "[JOIN] " << name << " (" << peerAddrStr << ") joined the network.\n";
                } else if (msg.rfind("MSG:", 0) == 0) {
                    std::string actualMsg = msg.substr(4);
                    std::cout << "[" << peerAddrStr << "] " << actualMsg << std::endl;
                } else if (msg.rfind("EXIT:", 0) == 0) {
                    std::string name = msg.substr(5);
                    std::cout << "[EXIT] " << name << " (" << peerAddrStr << ") left the network.\n";
                    break;
                } else {
                    std::cout << "[UNKNOWN] " << peerAddrStr << ": " << msg << std::endl;
                }
            }

            peer.close();
            removePeer(peerAddrStr);
        }

    } catch (const Poco::Exception& ex) {
        std::cerr << "Server failed: " << ex.displayText() << std::endl;
    }
} 