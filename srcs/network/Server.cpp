#include "Server.hpp"

// Server::Server(ServerConfig config, int domain, int service, int protocol, u_long interface, int backlog) {
// 	_listenSocket = new ListenSocket(domain, service, protocol, config.getPort(), interface, backlog);
// 	_buffer = (char*)calloc(BUFFER_SIZE + 1, 1);
// 	_config = config;
// 	std::cout << config.getPort()<< " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
// }
Server::Server(ServerConfig config) {
	_listenSocket = new ListenSocket(AF_INET, SOCK_STREAM, 0, config.getPort(), INADDR_ANY, 20);
	_buffer = (char*)calloc(BUFFER_SIZE + 1, 1);
	_config = config;
	std::cout << "Host:" << config.getHost()<< " listening to new connections on Port:" << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}

Server::~Server(void) {
	close(_listenSocket->getSocket());
	delete _listenSocket;
	delete _buffer;
}

ListenSocket* Server::getListenSocket(void) const {
	return _listenSocket;
}

std::vector<int> Server::getActiveConnections(void) const {
	return _activeConnections;
}

Client* Server::listenNewConnections(void) {
	struct sockaddr_in address = _listenSocket->getAddress();
	socklen_t socketLength = static_cast<socklen_t>(sizeof(address));
	int newClientSocket = accept(_listenSocket->getSocket(), (struct sockaddr *)&address, &socketLength);
	if (newClientSocket < 0) {
		perror("error: select(): ");
		return NULL;
	}
	else {
		Client* newClient = new Client(newClientSocket, this);
		_activeConnections.push_back(newClientSocket);
		std::cout << "New socket on fd: " << newClientSocket << std::endl;
		return newClient;
	}
}

void Server::writeSocket(Client *client) {
	int written = write(client->getSock(), vecToStr(client->getWriteBufferVect()).c_str(), client->getWriteBufferSize());
	if (written < 0) {
		closeConnection(client);
		return ;
	}
	if (VERBOSE) 
		printHeader(client->getWriteBufferVect(), written);
	client->clearWriteBuffer(written);
}

void Server::readSocket(Client *client) {
	int sock = client->getSock();
	int received = BUFFER_SIZE;
	memset(_buffer, 0, BUFFER_SIZE + 1);
	received = read(sock, _buffer, BUFFER_SIZE);
	if (received <= 0) {
		if (received < 0)
			std::cout << "read() error" << std::endl;
		closeConnection(client);
		return;
	}
	else {

	}
	client->appendReadBuffer(&_buffer, received);
	if (VERBOSE)
		printHeader(client->getReadBuffer(), received);
	requestToResponseProcess(client, _config); //Leo's part
}

void Server::closeConnection(Client *client) {
	client->kill();
	int sock = client->getSock();
	close(sock);
	std::vector<int>::iterator it_1 = find(_activeConnections.begin(), _activeConnections.end(), sock);
    if (it_1 != _activeConnections.end()) {
        _activeConnections.erase(it_1);
	}
	std::cout << "closed connection on socket " << sock << std::endl;
}

void Server::printHeader(std::vector<unsigned char> buffer, int max) const {
	std::cout << std::endl;
	for(int i=0; i < max; ++i) {
		if (buffer[i] == '\n' && i + 1 < max && buffer[i + 1] == '\r')
			max = i;
	}
	std::cout.write(reinterpret_cast<const char*>(&buffer[0]), max);
	std::cout << std::endl;
}
