#include "ServerHelp.h"

Server::Server(unsigned short port) : listen_port(port)
{
    logl("Chat Server Started");

    if (listener.listen(listen_port) != sf::Socket::Done)
    {
      logl("Could not listen");
    }
}

void Server::ConnectClients(std::vector<sf::TcpSocket *> *client_array)
{
    while (true)
    {
        sf::TcpSocket *new_client = new sf::TcpSocket();
        if (listener.accept(*new_client) == sf::Socket::Done)
        {
            new_client->setBlocking(false);
            client_array->push_back(new_client);
            logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << client_array->size());
        }
        else
        {
            logl("Server listener error, restart the server");
            delete (new_client);
            break;
        }
    }
}

void Server::DisconnectClient(sf::TcpSocket *socket_pointer, size_t position)
{
    logl("Client " << socket_pointer->getRemoteAddress() << ":" << socket_pointer->getRemotePort() << " disconnected, removing");
    socket_pointer->disconnect();
    delete (socket_pointer);
    client_array.erase(client_array.begin() + position);
}

void Server::BroadcastPacket(sf::Packet &packet, sf::IpAddress exclude_address, unsigned short port)
{
    for (size_t iterator = 0; iterator < client_array.size(); iterator++)
    {
        sf::TcpSocket *client = client_array[iterator];
        if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port)
        {
            if (client->send(packet) != sf::Socket::Done)
            {
                logl("Could not send packet on broadcast");
            }
        }
    }
}

void Server::ReceivePacket(sf::TcpSocket *client, size_t iterator)
{
    sf::Packet packet;
    if (client->receive(packet) == sf::Socket::Disconnected)
    {
        DisconnectClient(client, iterator);
        return;
    }

    if (packet.getDataSize() > 0)
    {
        std::string received_message;
        packet >> received_message;
        packet.clear();

        std::string first_packet_beginning = "UserId:";
    
        if(received_message.find(first_packet_beginning) == 0 && 
            client_list.contains(client->getRemoteAddress().toString(), client->getRemotePort()) == 0)
        {
            std::string userId = received_message.substr(first_packet_beginning.length());
            client_list.insert(client->getRemoteAddress().toString(), client->getRemotePort(), userId);
        }
        else
        {
            std::string userId = client_list.get(client->getRemoteAddress().toString(), client->getRemotePort());

            packet << received_message << userId;
            BroadcastPacket(packet, client->getRemoteAddress(), client->getRemotePort());

            
            logl(userId<< ": '" << received_message << "'");
        }
    }
}

void Server::ManagePackets()
{
    while (true)
    {
        for (size_t iterator = 0; iterator < client_array.size(); iterator++)
        {
            ReceivePacket(client_array[iterator], iterator);
        }

        std::this_thread::sleep_for((std::chrono::milliseconds)250);
    }
}

void Server::Run()
{
    std::thread connetion_thread(&Server::ConnectClients, this, &client_array);

    ManagePackets();
}
