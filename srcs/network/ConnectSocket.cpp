#include "ConnectSocket.hpp"

ConnectSocket::ConnectSocket(int domain, int service, int protocol, int port, u_long interface): 
	ASocket(domain, service, protocol, port, interface) {
		_connection = connectToNetwork(_socket, _address);
		testConnection(_connection);
	}

int ConnectSocket::connectToNetwork(int socket, struct sockaddr_in address) {
	return connect(socket, (struct sockaddr *)&address, sizeof(address));
}

ConnectSocket::~ConnectSocket(void) {}
