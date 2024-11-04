#include "Server.hpp"

Server::Server(){}
Server::Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog) {
	_listenSocket = new ListenSocket(domain, service, protocol, config.getPort(), interface, backlog);
	std::cout << config.getPort()<< " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}
Server::Server(ServerConfig config) {
	_listenSocket = new ListenSocket(AF_INET, SOCK_STREAM, 0, config.getPort(), INADDR_ANY, 20);
	std::cout << config.getPort()<< " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}

Server::Server(const Server &other){
	*this = other;
}
Server &Server::operator=(const Server &rhs){
	*this = rhs;
	return *this;
}
Server::~Server(void) {
	close(_listenSocket->getSocket());
	delete _listenSocket;
}

ListenSocket* Server::getListenSocket(void) const {
	return _listenSocket;
}

std::vector<int> Server::getActiveConnections(void) const {
	return _activeConnections;
}

Client Server::listenNewConnections(void) {
	struct sockaddr_in address = _listenSocket->getAddress();
	socklen_t socketLength = static_cast<socklen_t>(sizeof(address));
	int newClientSocket = accept(_listenSocket->getSocket(), (struct sockaddr *)&address, &socketLength);
	if (newClientSocket < 0) {
		perror("error: select(): ");
		Client newClient(newClientSocket, *this);
		return newClient;
	}
	else {
		Client newClient(newClientSocket, *this);
		_activeConnections.push_back(newClientSocket);
		std::cout << "New socket on fd: " << newClientSocket << std::endl;
		return newClient;
	}
}

void Server::writeSocket(Client &client) {
	int written = write(client.getSock(), client.getWriteBuffer(), client.getWriteBufferSize());
	if (written < 0) {
		closeConnection(client);
		return ;
	}
	client.updateLastActiveTime();
	client.clearWriteBuffer(written);
}

// void Server::checkIdleClient(Client &client) {
// 	time_t now = std::time(NULL);
// 	if (it.getLastActiveTime() + IDLE_TIMEOUT < now) {
// 		closeConnection(Client);
// 		--it;
// 	}
// }

void Server::readSocket(Client &client) {
	int sock = client.getSock();
	size_t received = BUFFER_SIZE;
	memset(_buffer, 0, BUFFER_SIZE);
	received = read(sock, _buffer, BUFFER_SIZE);
	if (received <= 0) {
		closeConnection(client);
		return;
	}
	client.updateLastActiveTime();
	client.appendReadBuffer(&_buffer, received);
	requestToResponseProcess(client, _config); //Leo's part
}

void Server::closeConnection(Client &client) {
	client.kill();
	int sock = client.getSock();
	close(sock);
	std::vector<int>::iterator it_1 = find(_activeConnections.begin(), _activeConnections.end(), sock);
    if (it_1 != _activeConnections.end())
        _activeConnections.erase(it_1);
	std::cout << "closed connection on socket " << socket << std::endl;
}
