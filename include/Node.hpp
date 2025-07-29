// // #pragma once

// // #include <string>
// // #include <Poco/Net/StreamSocket.h>
// // #include <Poco/Net/SocketAddress.h>

// // class Node {
// // public:
// //     Node(const std::string& host, int port);
// //     void start();
// // private:
// //     std::string _host;
// //     int _port;
// //     Poco::Net::StreamSocket _socket;
// // };

// //------------------------------------------DAY 1------------------------------------
// #pragma once

// #include <string>
// #include <Poco/Net/StreamSocket.h>
// #include <Poco/Net/ServerSocket.h>
// #include <Poco/Net/SocketAddress.h>

// class Node {
// public:
//     Node(const std::string& host, int port);
//     void start();       // Client node tries to connect
//     void listen();      // Server node listens for peers
// private:
//     std::string _host;
//     int _port;
// };

//-------------------------------------------DAY 2----------------------------------------

#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SocketAddress.h>

class Node {
public:
    Node(const std::string& host, int port);
    void start();   // Acts as client
    void listen();  // Acts as server

private:
    std::string _host;
    int _port;

    std::vector<std::string> _peerList;
    std::mutex _mutex;

    void addPeer(const std::string& address);
    void removePeer(const std::string& address);
};
