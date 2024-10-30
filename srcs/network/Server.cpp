#include "Server.hpp"

Server::Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog) {
	_listenSocket = new ListenSocket(domain, service, protocol, config.getPort(), interface, backlog);
	//_max_fd = _listenSocket->getSocket();
	std::cout << ServerConfig->getName() << " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}
Server::Server(ServerConfig config) {
	_listenSocket = new ListenSocket(AF_INET, SOCK_STREAM, 0, config.getPort(), INADDR_ANY, 20);
	//_max_fd = _listenSocket->getSocket();
	std::cout << ServerConfig->getName() << " listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}

Server::~Server(void) {
	close(_listenSocket->getSocket());
	delete _listenSocket;
}

void Server::listenNewConnections(void) {
	if (FD_ISSET(_listenSocket->getSocket(), &_readFds)) {
		struct sockaddr_in address = _listenSocket->getAddress();
		socklen_t socketLength = static_cast<socklen_t>(sizeof(address));
		int newClientSocket = accept(_listenSocket->getSocket(), (struct sockaddr *)&address, &socketLength);
		if (newClientSocket < 0)
			perror("error: select(): ");
		else {
			FD_SET(newClientSocket, &_readFds);
			Client newClient(newClientSocket);
			_activeConnections.push_back(newClient);
			if (newClientSocket > _max_fd)
				_max_fd = newClientSocket;
			std::cout << "New socket on fd: " << newClientSocket << std::endl;
		}
	}
}

void Server::processWriteQueue(void) {
	Client client;
	int queueSize = _writeQueue.size();
	for (int i=0; i < queueSize; ++i) {
		client = _writeQueue.front();
		_writeQueue.pop();
		FD_SET(client.getSock(), &_writeFds);
	 	checkSockets();
		if (FD_ISSET(sock.first, &_writeFds)) { //always check the socket is ready for writing
			writeSocket(sock.first, sock.second); //!
			FD_CLR(sock.first, &_writeFds);
		}
		else
			removeConnection(sock.first);
			//_writeQueue.push(sock); //Socket not ready for writing, try again? Try counter?
	}
}

void Server::writeSocket(Client client) {
	int written = write(client.getSock(), client.getWriteBuffer(), client.getWriteBufferSize());
	if (written < 0) {
		removeConnection(client);
		return ;
	}
	client.updateLastActiveTime();
	client.clearWriteBuffer(written);
}

ListenSocket* Server::getListenSocket(void) const {
	return _listenSocket;
}

void Server::checkIdleClient(Client client) {
	time_t now = std::time(NULL);
	if (it.getLastActiveTime() + IDLE_TIMEOUT < now) {
		removeConnection(Client);
		--it;
	}
}

void Server::readSocket(Client client) {
	size_t received = BUFFER_SIZE;
	memset(_buffer, 0, BUFFER_SIZE);
	received = read(sock, _buffer, BUFFER_SIZE);
	if (received =< 0) {
		removeConnection(sock);
		return;
	}
	client.updateLastActiveTime();
	client.append(_buffer, received);
	//sendResponse(sock, requestToResponseProcess(_rawClientReq, _config));
	requestToResponseProcess(client)
}

void Server::removeConnection(int sock) {
	int sock = client.getSock();
	close(sock);
	FD_CLR(socket, &_writeFds);//
	FD_CLR(socket, &_readFds);//
	std::vector<Client>::iterator it_1 = std::find(_activeConnections.begin(), _activeConnections.end(), client);
    if (it_1 != _activeConnections.end()) {
        _activeConnections.erase(it_1);
    }
	std::cout << "Removed connection on socket " << socket << std::endl;
}

void Server::sendResponse(int sock, std::string response) {
	_writeQueue.push(std::pair<int, std::string>(sock, response));
}


refactoring:

std::vector<char> instead of string when read()ing client data

Since a client msg can be fragmented, every open connection should have its buffer char vector

Select() does a snapshot of the fds state.

Just a single queue is enough, std::queue<Operation>

Operation:
	Client
	action_type: read or write

if Client NULL, then it's the listenSocket (action_type == read);

Operations manager:
	std::queue<Operation> _queue;
	Server server_0 = Server(ServerConfig, &queue)

	every server has got the address of the queue. Every server can add an operation to the queue.
	The queue rotates endlessly.
	An operation contains:
		&server
		&client
		int operation_type (read, write, listen)
	
	select will contain all sockets, allowing for a processing of all servers' sockets