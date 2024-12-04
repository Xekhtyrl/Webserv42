#pragma once

#include "ASocket.hpp"

class ASocket;

class ConnectSocket : public ASocket {
	public:
		ConnectSocket(int domain, int service, int protocol, int port, u_long interface);
		int connectToNetwork(int socket, struct sockaddr_in address) ;
		~ConnectSocket(void);
};
