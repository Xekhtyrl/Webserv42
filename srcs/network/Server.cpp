#include "Server.hpp"

Server::Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog) {
	_listenSocket = new ListenSocket(domain, service, protocol, config.getPort(), interface, backlog);
	std::cout << ServerConfig->getName() << " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}
Server::Server(ServerConfig config) {
	_listenSocket = new ListenSocket(AF_INET, SOCK_STREAM, 0, config.getPort(), INADDR_ANY, 20);
	std::cout << ServerConfig->getName() << " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
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
std::queue<int> Server::getClosedConnections(void) const {
	std::vector<int> tmp = _closedConnections;
	_closedConnections.clear();
	return tmp;
}

Client Server::listenNewConnections(void) {
	struct sockaddr_in address = _listenSocket->getAddress();
	socklen_t socketLength = static_cast<socklen_t>(sizeof(address));
	int newClientSocket = accept(_listenSocket->getSocket(), (struct sockaddr *)&address, &socketLength);
	if (newClientSocket < 0) {
		perror("error: select(): ");
		return NULL;
	}
	else {
		Client newClient(newClientSocket);
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
	size_t received = BUFFER_SIZE;
	memset(_buffer, 0, BUFFER_SIZE);
	received = read(sock, _buffer, BUFFER_SIZE);
	if (received =< 0) {
		closeConnection(sock);
		return;
	}
	client.updateLastActiveTime();
	client.append(_buffer, received);
	requestToResponseProcess(client);
}

void Server::closeConnection(Client &client) {
	client.kill();
	int sock = Client.getSock();
	close(sock);
	std::vector<Client>::iterator it_1 = std::find(_activeConnections.begin(), _activeConnections.end(), client);
    if (it_1 != _activeConnections.end())
        _activeConnections.erase(it_1);
	std::cout << "closed connection on socket " << socket << std::endl;
}
