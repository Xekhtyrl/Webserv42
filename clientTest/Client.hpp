#pragma once

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000000
#endif

#include "../srcs/network/ConnectSocket.hpp"
#include <iostream>

class Client {
	public:
		Client(int domain, int service, int protocol, int port, u_long interface, std::string name);
		Client(int port, std::string name);
		Client(int port);
		Client(void);
		~Client(void);

		std::string makeName(void);
		void talk(int n_xchange);
		void sendMsg(std::string msg);
		std::string receiveMsg(void);

	private:
		ConnectSocket* _socket;
		char _buffer[BUFFER_SIZE];
		std::string _name;
		int _msgCount;
		
};
