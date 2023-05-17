# SFML-Chat-Application-With-Authentication

## Description

This is a network-based Chat Application that enables real-time communication between multiple clients. It leverages the Transmission Control Protocol (TCP) to facilitate reliable and efficient communication.
The application consists of two main components: the server and the client. The server acts as a centralized entity that receives messages from clients and broadcasts the message to the entire network. Each client connects to the server to send and receive messages to other users.

## Features

#### Real-time communication between multiple clients

 Using TCP it allows for efficient communication between clients using a server.
 The server-side accepts/disconnects client connections, receives packets from clients, processes the received messages and broadcasts them to other clients.
 The client-side receives packets from the server and prints the received messages along with the sender's username and it sends packets containing user input to the server, then to be broadcasted to the entire network.
 
#### Authentication system

 It allows users to register, login, recover passwords, and exit the application. User data is stored in a file called "users.txt".
 
## Usage
  #### To use the SFML Chat Application, follow these steps:

  #### 1. Clone the repository to your local machine using the command:
    git clone https://github.com/GhiocelAndrei/SFML-Chat-Application-With-Authentication.git

  #### 2. Compile the server and client source files using the command:
    make

  #### 3. Run the server and the client(s) in separate terminal windows:
    ./server 
    ./client
