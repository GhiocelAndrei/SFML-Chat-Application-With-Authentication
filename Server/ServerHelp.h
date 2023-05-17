#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <string.h>
#include <unordered_map>
#include <tuple>
#include <SFML/Network.hpp>

#define MAX_RAW_DATA 256 // Max bytes supported on Raw Data mode

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

struct PairHash {
    template<typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

class ClientList {
public:
    std::unordered_map<std::pair<std::string, unsigned short>, std::string, PairHash> dictionary;

    ClientList() : dictionary() {}

    void insert(const std::string& key1, unsigned short key2, const std::string& value) {
        dictionary[std::make_pair(key1, key2)] = value;
    }

    std::string& get(const std::string& key1, unsigned short key2) {
        return dictionary[std::make_pair(key1, key2)];
    }

    bool contains(const std::string& key1, unsigned short key2) {
        return dictionary.count(std::make_pair(key1, key2)) > 0;
    }
};

class Server
{
    sf::TcpListener listener;
    std::vector<sf::TcpSocket *> client_array;

    unsigned short listen_port;

    std::unordered_map<std::string, std::string> clientId_list;
    ClientList client_list;
public:
    Server(unsigned short port);
    void ConnectClients(std::vector<sf::TcpSocket *> *client_array);
    void DisconnectClient(sf::TcpSocket *socket_pointer, size_t position);

    void ReceivePacket(sf::TcpSocket *client, size_t iterator);

    void BroadcastPacket(sf::Packet &packet, sf::IpAddress exclude_address, unsigned short port);

    void ManagePackets();
    void Run();
};
