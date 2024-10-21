#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include "Client.hpp"


Client::Client(int domain, int service, int protocol, int port, u_long interface, std::string name) {
    _socket = new ConnectSocket(domain, service, protocol, port, interface);
    _name = name;
    _msgCount = 0;
    std::cout << _name << " connected to server successfully" << std::endl;
}

Client::Client(int port, std::string name) {
    _socket = new ConnectSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY);
    _name = name;
    _msgCount = 0;
    std::cout << _name << " connected to server successfully" << std::endl;
}

Client::Client(int port) {
    _socket = new ConnectSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY);
    _name = makeName();
    _msgCount = 0;
    std::cout << _name << " connected to server successfully" << std::endl;
}

Client::~Client(void) {
    delete _socket;
}

std::string Client::makeName(void) {
    std::string name = "";
    char c;
    srand((int)time(0));
    for (int i=0; i < 6; ++i) {
        c = rand() % 26 + 'A';
        name += c;
    }
    return name;
}

void Client::talk(int n_xchange) {
    std::string msg = _name + " sending message number ";
    std::string response;
    while (n_xchange--) {
        sendMsg(msg + std::to_string(++_msgCount));
        response = receiveMsg();
        std::cout << "CLIENT:" << std::endl << msg + std::to_string(_msgCount) << std::endl;
        std::cout << "SERVER:" << std::endl << response << std::endl;
    }
}

void Client::sendMsg(std::string msg) {
    if (write(_socket->getSocket(), msg.c_str(), msg.size()) < 0) {
        perror("Client write() error:");
    };
}

std::string Client::receiveMsg(void) {
    memset(_buffer, 0, BUFFER_SIZE);
    int bytes_received = read(_socket->getSocket(), _buffer, BUFFER_SIZE);
    if (bytes_received < 0) {
        perror("Client read() error:");
    }
    return std::string(_buffer, bytes_received);
}
