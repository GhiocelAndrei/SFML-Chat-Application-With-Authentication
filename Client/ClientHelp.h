#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class Client{
    sf::TcpSocket socket;
    sf::Packet last_packet;

    bool isConnected = false;
    std::string clientUserId;
public:
    Client(std::string userId);
    // Delete move constructor and move assignment operator
    Client(const Client&) = default;
    Client& operator=(const Client&) = default;
    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;
    
    void Connect(const char *address, unsigned short port);
    void ReceivePackets(sf::TcpSocket *socket);
    void SendPacket(sf::Packet &packet);
    void Run();
};
