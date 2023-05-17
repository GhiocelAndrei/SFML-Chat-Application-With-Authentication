#include "ClientHelp.h"

Client::Client(std::string userId)
{
    logl("Chat Client Started");
    clientUserId = userId;
}

void Client::Connect(const char *address, unsigned short port)
{
    if (socket.connect(address, port) != sf::Socket::Done)
    {
        logl("Could not connect to the server\n");
    }
    else
    {
        isConnected = true;
        logl("Connected to the server\n");
    }
}

void Client::ReceivePackets(sf::TcpSocket *socket)
{
    while (true)
    {
        if (socket->receive(last_packet) == sf::Socket::Done)
        {
            std::string received_string;
            std::string sender_username;
            last_packet >> received_string >> sender_username;
            logl("From " << sender_username << " : " << received_string);
        }

        std::this_thread::sleep_for((std::chrono::milliseconds)250);
    }
}

void Client::SendPacket(sf::Packet &packet)
{
    if (packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done)
    {
        logl("Could not send packet");
    }
}

void Client::Run()
{
    std::thread reception_thred(&Client::ReceivePackets, this, &socket);

    std::this_thread::sleep_for((std::chrono::milliseconds)300);

    std::string first_packet_input = "UserId:" + clientUserId;
    sf::Packet first_packet;
    first_packet << first_packet_input;

    SendPacket(first_packet);

    while (true)
    {
        if (isConnected)
        {
            std::string user_input;
            std::getline(std::cin, user_input);

            if (user_input.length() < 1)
                continue;

            sf::Packet reply_packet;
            reply_packet << user_input;

            SendPacket(reply_packet);
        }
    }
}
